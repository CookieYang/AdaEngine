#include "CommandQueue.h"
#include <memory>

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
	if (deallocPtr == writePtr) {
		return false;
	}

	uint32_t size = *(uint32_t*)&command_mem[deallocPtr];
	if (size == 0) {
		deallocPtr = 0;
		goto tryagain;
	}

	if (size & 1) {
		return false;
	}

	deallocPtr += (size >> 1) + 8;
	return true;
}