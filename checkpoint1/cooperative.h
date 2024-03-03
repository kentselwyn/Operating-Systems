#ifndef __COOPERATIVE_H__
#define __COOPERATIVE_H__

#define MAXTHREADS 4  // Excluding the scheduler (takes no thread)
typedef char ThreadID;
typedef void (*FunctionPtr)(void);

ThreadID ThreadCreate(FunctionPtr);
void ThreadYield(void);
void ThreadExit(void);

#endif