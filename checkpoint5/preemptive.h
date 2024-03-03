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

#define SemaphoreWaitBody(S, label_0, label_1) \
        __asm \
                        CLR _EA \
                        MOV A, CNAME(S) \
                        JNB ACC.7, LABEL(label_1) \
                LABEL(label_0): \
                        SETB _EA \
                        LCALL _ThreadYield \
                        CLR _EA \
                        MOV A, CNAME(S) \
                        JZ LABEL(label_0) \
                        JB ACC.7, LABEL(label_0) \
                LABEL(label_1): \
                        JZ LABEL(label_0) \
                        DEC CNAME(S) \
                        SETB _EA \
        __endasm; \

#define SemaphoreWait(S) \
        SemaphoreWaitBody(S, __COUNTER__, __COUNTER__)

#define SemaphoreSignal(S) \
        __asm \
                INC CNAME(S) \
        __endasm;

ThreadID ThreadCreate(FunctionPtr);
void ThreadYield(void);
void ThreadExit(void);
void myTimer0Handler(void);

#endif