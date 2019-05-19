#include "CommandQueue.h"
#include <memory>
#include "Engine.h"

void Semaphore::wait() {
	std::unique_lock<std::mutex> lock(innerMutex);
	if (--count < 0) {
		conditionVariable.wait(lock);
	}
}

void Semaphore::signal() {
	std::unique_lock<std::mutex> lock(innerMutex);
	if (++count <= 0) {
		conditionVariable.notify_one();
	}
}

CommandQueue::CommandQueue(bool p_sync) {
	readPtr = 0;
	writePtr = 0;
	deallocPtr = 0;
	mutex = new std::mutex;
	command_mem = (uint8_t*)malloc(COMMAND_MEN_SIZE);
	for (size_t i = 0; i < SYNC_SEMAPHORES; i++)
	{
		sync_sems[i].sem = new Semaphore(0);
		sync_sems[i].inUse = false;
	}
	if (p_sync) {
		sync = new Semaphore(0);
	}
	else {
		sync = nullptr;
	}
}

CommandQueue::~CommandQueue() {
	if (sync) {
		delete sync;
	}
	delete mutex;
	for (size_t i = 0; i < SYNC_SEMAPHORES; i++)
	{
		delete sync_sems[i].sem;
	}
	free(command_mem);
}

bool CommandQueue::dealloc_one() {
tryagain:
	// empty queue
	if (deallocPtr == writePtr) {
		return false;
	}

	// at the end of queue
	uint32_t size = *(uint32_t*)&command_mem[deallocPtr];
	if (size == 0) {
		deallocPtr = 0;
		goto tryagain;
	}

	// no empty space to release
	if (size & 1) {
		return false;
	}

	deallocPtr += (size >> 1) + 8;
	return true;
}

void CommandQueue::lock() {
	if (mutex) {
		mutex->lock();
	}
}

void CommandQueue::unlock() {
	if (mutex) {
		mutex->unlock();
	}
}

void CommandQueue::waitForFlush() {
	// sleep
	Engine::sleep(1000);
}

CommandQueue::SyncSemaphore* CommandQueue::allocSyncSem() {
	int idx = -1;
	while (true)
	{
		lock();
		for (int i = 0; i < SYNC_SEMAPHORES; i++) {
			if (!sync_sems[i].inUse) {
				sync_sems[i].inUse = true;
				idx = i;
				break;
			}
		}
		unlock();
		if (idx == -1) {
			waitForFlush();
		}
		else {
			break;
		}
	}
	return &sync_sems[idx];
}

bool CommandQueue::flushOne(bool bLock) {
	if (bLock) {
		lock();
	}
tryagain:
	if (readPtr == writePtr) {
		if (bLock) {
			unlock();
		}
		return false;
	}
	uint32_t sizePtr = readPtr;
	uint32_t size = *(uint32_t*)&command_mem[readPtr] >> 1;
	if (size == 0) {
		readPtr = 0;
		goto tryagain;
	}
	readPtr += 8;
	CommandBase* cmd = reinterpret_cast<CommandBase*>(&command_mem[readPtr]);
	readPtr += size;

	if (bLock) {
		unlock();
	}
	cmd->call();
	if (bLock) {
		lock();
	}
	cmd->signal();                           // notify cmd has got result, return to call thread and get result
	cmd->~CommandBase();
	*(uint32_t*)&command_mem[sizePtr] &= ~1;
	if (bLock) {
		unlock();
	}
	return true;
}