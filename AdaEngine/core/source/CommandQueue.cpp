#include "CommandQueue.h"
#include <memory>
#include <Windows.h>

void Semaphore::wait() {
	std::unique_lock<std::mutex> lock(mutex);
	if (--count < 0) {
		conditionVariable.wait(lock);
	}
}

void Semaphore::signal() {
	std::unique_lock<std::mutex> lock(mutex);
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
		sync_sems[i].sem = new Semaphore(1);
		sync_sems[i].inUse = false;
	}
	if (p_sync) {
		sync = new Semaphore(1);
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
	Sleep(1000);
}

bool CommandQueue::flushOne(bool bLock) {
	if (bLock) {
		lock();
	}
tryagain:
	if (readPtr == writePtr) {
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
	cmd->signal();                           // wait for research
	cmd->~CommandBase();
	*(uint32_t*)&command_mem[sizePtr] &= ~1;
	if (bLock) {
		unlock();
	}
	return true;
}