#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>

class Semaphore {
public:
	Semaphore(int value) :count{ value } {};
	void wait();
	void signal();
private:
	int count;
	std::mutex mutex;
	std::condition_variable conditionVariable;
};

class CommandQueue {
	struct SyncSemaphore
	{
		Semaphore* sem;
		bool inUse;
	};

	struct CommandBase
	{
		virtual void call() = 0;
		virtual void signal() {};
		virtual ~CommandBase() {};
	};

	struct SyncCommand: public CommandBase
	{
		SyncSemaphore* syncSem;
		virtual void signal() override {
			syncSem->sem->signal();
		}
	};

	enum
	{
		COMMAND_MEM_SIZE_KB = 256,
		COMMAND_MEN_SIZE = COMMAND_MEM_SIZE_KB * 1024,
		SYNC_SEMAPHORES = 8
	};

	uint8_t* command_mem;
	uint32_t readPtr;
	uint32_t writePtr;
	uint32_t deallocPtr;
	SyncSemaphore sync_sems[SYNC_SEMAPHORES];
	std::mutex* mutex;
	Semaphore* sync;

	template <class T>
	T* allocate() {

		uint32_t alloc_size = ((sizeof(T) + 8 - 1) & ~(8 - 1)) + 8;

	tryagain:
		if (writePtr < deallocPtr) {
			if ((deallocPtr - writePtr) <= alloc_size) {
				// no more space for new alloc
				if (dealloc_one()) {
					goto tryagain;
				}
				return NULL;
			}
		}
		else if (writePtr >= deallocPtr) {
			// muse larger than one alloc and end flag(uint32_t)
			if ((COMMAND_MEN_SIZE - writePtr) < alloc_size + sizeof(uint32_t)) {
				if (deallocPtr == 0) {
					if (dealloc_one()) {
						goto tryagian;
					}
					return NULL;
				}

				assert(COMMAND_MEN_SIZE - writePtr > = 8);

				// there is some space at head, move write prt to head
				uint32_t* p = (uint32_t*)&command_mem[writePtr];
				*p = 0;                                                                      // tell us where is the end (for read)[end flag]
				writePtr = 0;
				goto tryagain;
			}
		}

		uint32_t size = (sizeof(T) + 8 - 1)&~(8 - 1);
		uint32_t *p = (uint32_t*)&command_mem[writePtr];
		*p = (size << 1) | 1;
		writePtr += 8;
		T* cmd = new(&command_mem[writePtr]) T;
		writePtr += size;
		return cmd;
	}

	template <class T>
	T* allocateAndLock() {
		lock(); 
		T* ret;
		while ((ret = allocate<T>()) == NULL) {
			unlock();
			// unlock and sleep a little while
			waitForFlush();
			// try again
			lock();
		}
		return ret;
	}

	void lock();
	void unlock();
	void waitForFlush();
	
	bool dealloc_one();
	CommandQueue(bool p_sync);
	~CommandQueue();
};
