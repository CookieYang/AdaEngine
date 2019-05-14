#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>

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

	CommandQueue(bool p_sync);
	~CommandQueue()
};
