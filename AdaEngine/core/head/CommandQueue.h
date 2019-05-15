#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>

#define COMMA(N) _COMMA_##N
#define _COMMA_0
#define _COMMA_1 ,
#define _COMMA_2 ,
#define _COMMA_3 ,
#define _COMMA_4 ,
#define _COMMA_5 ,
#define _COMMA_6 ,
#define _COMMA_7 ,
#define _COMMA_8 ,
#define _COMMA_9 ,
#define _COMMA_10 ,

#define COMMA_SEP_LIST(ITEM, LENGTH) _COMMA_SEP_LIST_##LENGTH(ITEM)
#define _COMMA_SEP_LIST_10(ITEM) \
_COMMA_SEP_LIST_9(ITEM) \
, ITEM(10)
#define _COMMA_SEP_LIST_9(ITEM) \
_COMMA_SEP_LIST_8(ITEM) \
, ITEM(9)
#define _COMMA_SEP_LIST_8(ITEM) \
_COMMA_SEP_LIST_7(ITEM) \
, ITEM(8)
#define _COMMA_SEP_LIST_7(ITEM) \
_COMMA_SEP_LIST_6(ITEM) \
, ITEM(7)
#define _COMMA_SEP_LIST_6(ITEM) \
_COMMA_SEP_LIST_5(ITEM) \
, ITEM(6)
#define _COMMA_SEP_LIST_5(ITEM) \
_COMMA_SEP_LIST_4(ITEM) \
, ITEM(5)
#define _COMMA_SEP_LIST_4ITEM) \
_COMMA_SEP_LIST_3(ITEM) \
, ITEM(4)
#define _COMMA_SEP_LIST_3(ITEM) \
_COMMA_SEP_LIST_2(ITEM) \
, ITEM(3)
#define _COMMA_SEP_LIST_2(ITEM) \
_COMMA_SEP_LIST_1(ITEM) \
, ITEM(2)
#define _COMMA_SEP_LIST_1(ITEM) \
_COMMA_SEP_LIST_0(ITEM) \
 ITEM(1)
#define _COMMA_SEP_LIST_0(ITEM)

#define SEMIC_SEP_LIST(ITEM, LENGTH) _SEMIC_SEP_LIST_##LENGTH(ITEM)
#define _SEMIC_SEP_LIST_10(ITEM) \
_SEMIC_SEP_LIST_9(ITEM);\
 ITEM(10)
#define _SEMIC_SEP_LIST_9(ITEM) \
_SEMIC_SEP_LIST_8(ITEM); \
 ITEM(9)
#define _SEMIC_SEP_LIST_8(ITEM) \
_SEMIC_SEP_LIST_7(ITEM); \
 ITEM(8)
#define _SEMIC_SEP_LIST_7(ITEM) \
_SEMIC_SEP_LIST_6(ITEM); \
 ITEM(7)
#define _SEMIC_SEP_LIST_6(ITEM) \
_SEMIC_SEP_LIST_5(ITEM); \
 ITEM(6)
#define _SEMIC_SEP_LIST_5(ITEM) \
_SEMIC_SEP_LIST_4(ITEM); \
 ITEM(5)
#define _SEMIC_SEP_LIST_4ITEM) \
_SEMIC_SEP_LIST_3(ITEM); \
 ITEM(4)
#define _SEMIC_SEP_LIST_3(ITEM) \
_SEMIC_SEP_LIST_2(ITEM); \
 ITEM(3)
#define _SEMIC_SEP_LIST_2(ITEM) \
_SEMIC_SEP_LIST_1(ITEM); \
 ITEM(2)
#define _SEMIC_SEP_LIST_1(ITEM) \
_SEMIC_SEP_LIST_0(ITEM) \
 ITEM(1)
#define _SEMIC_SEP_LIST_0(ITEM)

#define SPACE_SEP_LIST(ITEM, LENGTH) _SPACE_SEP_LIST_##LENGTH(ITEM)
#define _SPACE_SEP_LIST_10(ITEM) \
	_SPACE_SEP_LIST_9(ITEM)      \
	ITEM(10)
#define _SPACE_SEP_LIST_9(ITEM) \
	_SPACE_SEP_LIST_8(ITEM)     \
	ITEM(9)
#define _SPACE_SEP_LIST_8(ITEM) \
	_SPACE_SEP_LIST_7(ITEM)     \
	ITEM(8)
#define _SPACE_SEP_LIST_7(ITEM) \
	_SPACE_SEP_LIST_6(ITEM)     \
	ITEM(7)
#define _SPACE_SEP_LIST_6(ITEM) \
	_SPACE_SEP_LIST_5(ITEM)     \
	ITEM(6)
#define _SPACE_SEP_LIST_5(ITEM) \
	_SPACE_SEP_LIST_4(ITEM)     \
	ITEM(5)
#define _SPACE_SEP_LIST_4(ITEM) \
	_SPACE_SEP_LIST_3(ITEM)     \
	ITEM(4)
#define _SPACE_SEP_LIST_3(ITEM) \
	_SPACE_SEP_LIST_2(ITEM)     \
	ITEM(3)
#define _SPACE_SEP_LIST_2(ITEM) \
	_SPACE_SEP_LIST_1(ITEM)     \
	ITEM(2)
#define _SPACE_SEP_LIST_1(ITEM) \
	_SPACE_SEP_LIST_0(ITEM)     \
	ITEM(1)
#define _SPACE_SEP_LIST_0(ITEM)

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
	bool flushOne(bool bLock = true);
	
	bool dealloc_one();

public:
	void waitAndFlushOne() {
		assert(sync != nullptr);
		sync->wait();
		flushOne();
	}

	void flushAll() {
		lock();
		while (flushOne(false)) {

		}
		unlock();
	}
	CommandQueue(bool p_sync);
	~CommandQueue();
};
