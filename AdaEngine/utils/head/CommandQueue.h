#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include "SimpleType.h"
#include "Engine.h"

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
#define _COMMA_SEP_LIST_4(ITEM) \
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
#define _SEMIC_SEP_LIST_4(ITEM) \
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

#define ARG(N) p##N
#define PARAM(N) P##N p##N
#define TYPE_PARAM(N) class P##N
#define PARAM_DECL(N) typename GetSimpleTypeT<P##N>::type_t p##N     // I don't know the means and "#define PARAM_DECL(N) P##N p##N" also works

#define DECL_CMD(N)\
template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)> \
struct Command##N : public CommandBase { 	\
	T* instance;																\
	M method;																\
	SEMIC_SEP_LIST(PARAM_DECL, N);							\
	virtual void call() {													\
		(instance->*method)(COMMA_SEP_LIST(ARG, N)); \
	}																				\
};

#define DECL_CMD_RET(N)																								 \
template <class T, class M, COMMA_SEP_LIST(TYPE_PARAM, N) COMMA(N) class R> \
struct CommandRet##N : public SyncCommand {															 \
	R* ret;																															\
	T* instance;																													\
	M method;																													\
	SEMIC_SEP_LIST(PARAM_DECL, N);																				\
	virtual void call(){																											\
		*ret = (instance->*method)(COMMA_SEP_LIST(ARG, N));										\
	}																																	\
};

#define DECL_CMD_SYNC(N)																							\
template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)>				\
struct CommandSync##N: public SyncCommand{															\
	T* instance;																													\
	M method;																													\
	SEMIC_SEP_LIST(PARAM_DECL, N);																				\
	virtual void call(){																											\
		(instance->*method)(COMMA_SEP_LIST(ARG, N));													\
	}																																	\
};

#define TYPE_ARG(N) P##N
#define CMD_TYPE(N) Command##N<T, M COMMA(N) COMMA_SEP_LIST(TYPE_ARG, N)>
#define CMD_ASSIGN_PARAM(N) cmd->p##N = p##N
#define DECL_PUSH(N)																									\
template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)>            \
void push(T* p_instance, M p_method COMMA(N) COMMA_SEP_LIST(PARAM, N)){    \
	CMD_TYPE(N)* cmd = allocateAndLock<CMD_TYPE(N)>();										\
	cmd->instance = p_instance;																						\
	cmd->method = p_method;																						\
	SEMIC_SEP_LIST(CMD_ASSIGN_PARAM, N);																\
	unlock();																														\
	if(sync) sync->signal();																									\
};

#define CMD_RET_TYPE(N) CommandRet##N<T, M, COMMA_SEP_LIST(TYPE_ARG, N) COMMA(N) R>

#define DECL_PUSH_AND_RET(N)                                                                                  \
template <class T, class M, COMMA_SEP_LIST(TYPE_PARAM, N) COMMA(N) class R> \
void pushAndRet(T* p_instance, M p_method, COMMA_SEP_LIST(PARAM, N) COMMA(N) R* r_ret){  \
	SyncSemaphore *ss = allocSyncSem();																							    \
	CMD_RET_TYPE(N)* cmd = allocateAndLock<CMD_RET_TYPE(N)>();												\
	cmd->instance = p_instance;																												\
	cmd->method = p_method;																												\
	SEMIC_SEP_LIST(CMD_ASSIGN_PARAM, N);																						\
	cmd->ret = r_ret;																																	\
	cmd->syncSem = ss;																															\
	unlock();																																				\
	if(sync) sync->signal();																															\
	ss->sem->wait();																																	\
	ss->inUse = false;																																\
};

#define CMD_SYNC_TYPE(N) CommandSync##N<T, M COMMA(N) COMMA_SEP_LIST(TYPE_ARG, N)> 
#define DECL_PUSH_AND_SYNC(N)																											\
template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)>											\
void pushAndSync(T* p_instance, M p_method COMMA(N) COMMA_SEP_LIST(PARAM, N)){					\
	SyncSemaphore* ss = allocSyncSem();																									\
	CMD_SYNC_TYPE(N)* cmd = allocateAndLock<CMD_SYNC_TYPE(N)>();												\
	cmd->instance = p_instance;																													\
	cmd->method = p_method;																													\
	SEMIC_SEP_LIST(CMD_ASSIGN_PARAM, N);																							\
	cmd->syncSem = ss;																																\
	unlock();																																					\
	if(sync) sync->signal();																																\
	ss->sem->wait();																																		\
	ss->inUse = false;																																	\
};

class Semaphore {
public:
	Semaphore(int value) :count{ value } {};
	void wait();
	void signal();
private:
	int count;
	std::mutex innerMutex;
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

	DECL_CMD(0)
	SPACE_SEP_LIST(DECL_CMD, 10)

	DECL_CMD_RET(0)
	SPACE_SEP_LIST(DECL_CMD_RET, 10)

	DECL_CMD_SYNC(0)
	SPACE_SEP_LIST(DECL_CMD_SYNC, 10)


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
						goto tryagain;
					}
					return NULL;
				}

				assert(((COMMAND_MEN_SIZE - writePtr) >= 8));

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
			waitForFlush();                   // no space to push cmd , wait
			// try again
			lock();
		}
		return ret;
	}

	void lock();
	void unlock();
	void waitForFlush();
	bool flushOne(bool bLock = true);
	SyncSemaphore* allocSyncSem();
	bool dealloc_one();

public:
		/* NORMAL PUSH COMMANDS */
		DECL_PUSH(0)
		SPACE_SEP_LIST(DECL_PUSH, 10)

		/* PUSH AND RET COMMANDS */
		DECL_PUSH_AND_RET(0)
		SPACE_SEP_LIST(DECL_PUSH_AND_RET, 10)

		/* PUSH AND RET SYNC COMMANDS*/
		DECL_PUSH_AND_SYNC(0)
		SPACE_SEP_LIST(DECL_PUSH_AND_SYNC, 10)

	void waitAndFlushOne() {
		assert(sync != nullptr);
		sync->wait();                               // wait for cmd
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

#undef ARG
#undef PARAM
#undef TYPE_PARAM
#undef PARAM_DECL
#undef DECL_CMD
#undef DECL_CMD_RET
#undef DECL_CMD_SYNC
#undef TYPE_ARG
#undef CMD_TYPE
#undef CMD_ASSIGN_PARAM
#undef DECL_PUSH
#undef CMD_RET_TYPE
#undef DECL_PUSH_AND_RET
#undef CMD_SYNC_TYPE
#undef DECL_CMD_SYNC
