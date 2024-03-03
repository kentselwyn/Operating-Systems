#ifndef __PREEMPTIVE_H__
#define __PREEMPTIVE_H__

#define MAXTHREADS 4  // Excluding the scheduler (takes no thread)
typedef char ThreadID;
typedef void (*FunctionPtr)(void);

// C preprocessors API
#define CNAME(S) _ ## S
#define LABEL(label) label ## $

// Semaphore API
#define SemaphoreCreate(S, n) S = n; 

#define SemaphoreWaitBody(S, label) \
        __asm \
                        PUSH ACC \
                LABEL(label): \
                        MOV A, CNAME(S) \
                        JZ LABEL(label) \
                        JB ACC.7, LABEL(label) \
                        DEC CNAME(S) \
                        POP ACC \
        __endasm; \

#define SemaphoreWait(S) \
        SemaphoreWaitBody(S, __COUNTER__) \

#define SemaphoreSignal(S) \
        __asm \
                INC CNAME(S) \
        __endasm; \

ThreadID ThreadCreate(FunctionPtr);
void ThreadYield(void);
void ThreadExit(void);
void myTimer0Handler(void);

#endif