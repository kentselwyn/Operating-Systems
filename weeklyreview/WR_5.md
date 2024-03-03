# Weekly Review 5  

## 1. Definitions and Short Answers  - Week 5  

1. What is a **thread**? What comprises the state of a thread, and what does a thread share with other threads in the same process?  

> A thread is a fundamental unit of CPU utilization; less strictly speaking, a thread is a lightweight process, though loosely defined. It has its own thread ID, program counter, register set, and stack, but shares the same code section, data section, opened file handles, and signals with other threads of the same process.   

2. For a server, why is it not a good idea to create a separate process to service each request?  

> A context switch between processes is more resource intensive than switching threads. A thread also permits sharing the code and resources with other threads. This property can be leveraged to optimize the server's performance since requests are often repetitive or identical with other requests.  

3. What is the difference between **concurrent** and **parallel execution**?  Can you have concurrency without parallelism?  Can you have parallelism without concurrency?  

> A concurrent execution is the concept of managing and execution of multiple active (has ready, running, or waiting state) tasks or processes in a way that gives the illusion of simultaneous execution. These tasks may not necessarily be executing in the same time but are interleaved in such a way that they appear so. Concurrency can be achieved on both single-core and multi-core processors.  
> \
> A parallel execution is the genuine simultaneous execution of multiple tasks or processes on multiple CPU cores or processors. Parallel execution requires hardware support with multiple CPU cores or multiple processors.  
> \
> Concurrency execution can be achieved without parallel execution, but parallel execution cannot be achieve without concurrency execution.  

4. On a uniprocessor, do threads run concurrently? in parallel? What about on a multicore processor?  Under what conditions do threads run in parallel or concurrently but not in parallel?  

> On a uniprocessor, threads can run concurrently, but not in parallel. On the other hand, on a multi-core processor, threads can both run in parallel and concurrently. Threads can run concurrently but not in parallel if they operate on a uniprocessor that supports time-sharing.  
> \
> Threads can run in parallel if the operating system schedules them on multiple cores.  

5. What is **data parallelism**?  Give an example and explain why.  

> Data parallelism is a parallel computing technique where a single task or operation is divided into multiple identical subtasks that operate on different pieces of data simultaneously. In data parallelism, the same operation of function is applied to multiple data elements or data sets in parallel, speeding up computaiton and improving overall throughput.  
> \
> One example is a matrix multiplication operation:  
> Assume we have matrices A, B, and C, where `A * B = C`.  
> Then, `C[i][j] = sum(A[i][k] * B[k][j]) for k = 0 to (K - 1)`  
> Each element `C[i][j]` is computed independently based on the values in matrices A and B, each operating on different data.  

6. What is **task parallelism**?  Give an example and explain why.  

> Task parallelism is a parallel computing paradigm in which a problem is decomposed into multiple tasks that are executed simultaneously, with each task typically performing a different operation or computation. Unlike data parallelism, where the same operation is applied to multiple data elements concurreently, task parallelism focuses on executing different tasks concurrently to improve thoughput and efficiency.  
> \
> One example is the server that serves a variety of requests, like HTTP, FTP, cloud drive, or streaming. Each thread handles a different client request independently.  

7. What is the difference between **user threads** and **kernel threads**? Do both have to make system calls to create and join threads?  

> User threads are threads that are managed by user-level thread library, these threads are invisible to the operating system. These libraries do not need system calls to create and join threads.  
> \
> Kernel threads are threads that are managed and scheduled by the operating system itself. A system call is needed to create, schedule, and join.  

8. Do **user threads** need operating system support?  

> User thread libraries do not necessarily require operating system support.  

9. Is it true that **kernel threads** always run in kernel mode?  

> No, although in the processes of creating, scheduled, and joining a kernel thread are completed in the kernel mode, it can run in user mode.  

10. What is the difference between kernel threads and hardware threads?  

> Kernel thread is a software-defined thread managed by the operating system, while hardware threads refer to the physical or logical execution units available on a CPU. 
> \
> Hardware threads can refer to the number of physical cores in multi-core processors and the number of logical cores in a hyper-threaded processor. They are responsible for executing instructions and can run both user threads and kernel threads, and provide the foundation for parallel execution in a CPU by allowing multiple threads to run simultaneously on different cores or logical cores. Hardware threads share some hardware resources, such as caches and execution units, with other heardware threads.  

11. What are advantages with user threads over kernel threads?  What is a disadvantage on a single-threaded kernel?  

> Advantages of user threads:  
> - Commonly fast to create and manage  
> - The user threads can be implemented using a portable user-level thread libraries  
> - Can easily support cooperative multithreading  
> Disadvantages of user threads:  
> - User threads cannot fully benefit from multi-core processors  
> - If a user thread performs a blocking operation, all other user threads within the same process will also be blocked  
> - Limited capabilities that can be achieved in kernel mode   

12. What are the three main ways of mapping user threads to kernel threads?  

> One-to-one  
> Each user thread maps to a kernel thread, the kernel is involved in managing threads.  
> Advantage: More concurrency than sharing a single kernel thread  
> Disavantage: Higher overhead (every new thread requires initializing a kernel thread)  
> \
> Many-to-one  
> Many user-level threads map to one kernel thread. Default implementation for single-threaded operating system.  
> Advantage: Thread management is performed in user mode (more efficient)  
> Disadvantages: If a user thread makes a blocking system call, the whole process blocks, and cannot run multiple such threads in parallel on multiprocessors.   
> \
> Many-to-many  
> Many user threads map to many kernel threads. 
> Advantages: Threads mapped onto different kernel can run in parallel on a multiprocessor. If a user thread blocks on a call, the kernel can schedule another kernel thread for other threads of that process.  

- If the kernel is not multithreaded, which model can it support? Can it support one-to-one and why or why not?  
	
>	 It can only support the many-to-one model.  
>	 \
>	 To implement the one-to-one model effectively, the kernel must be capble of creating and managing kernel threads. The kernel needs to support operations like creating, scheduling threads for execution, context switching between threads, and providing synchronization primitives for thread coordination.  
>	 \
>	 However, in a single-threaded kernel, the kernel executes one task or operation at a time and does not have the built-in capabilities to create and manage multiple kernel threads. It lacks the essential infrastructure needed to support the one-to-one threading model.  

- Can many-to-one support simultaneous execution of user threads and a blocking system call made by one of its threads? Why or why not?  
	
>	 No, the many-to-one model does not support simultaneous execution of user threads because all user threads are managed by only one single kernel thread, which is responsible for executing the user threads one at a time, sequentially. This model also blocks the remaining user threads when any user thread performs a blocking system call, as the kernel thread is preoccupied with the system call.  

- Do kernel threads run in parallel?  Can a uniprocessor run an OS with multiple kernel threads?  If so, what would be a benefit and for which model?  

>	 Kernel threads run in parallel if they are on a multi-core processor system. A uniprocessor can run an operating system with multiple kernel threads using multitasking. 

13. How is **two-level** thread model different from a many-to-many model?  

> Two-level thread model is a mixture between a many-to-many model and an one-to-one model. This model allows a user thread to be bound to a kernel thread.  

14. Are threads created using `fork()` like regular processes?  

> No, threads are not spawned through calling `fork()` (which has a parent-child relationship). They are created through an API interface and does not inherit the state of its caller.  

15. Are most threads packages (`Pthreads`, `Python threads`, `Java threads`) **preemptive** or **cooperative**?  

> Most thread packages use preemptive threading.

16. What is a problem that can happen with cooperative threads but not with preemptive threads?  

> A thread may not yield (due to many reasons: bug in its program or malicious activities) to the thread managers and hogs all the CPU resources to itself.  

17. To implement preemptive threads at user level (on a UNIX-like system), what is the mechanism for the user code to get the effect similar to a timer-interrupt for context switching?  Why can't you use the timer interrupt directly as processes do?  

> User level thread libraries use signals to simulate a timer-like callback. To achieve this, the thread manager needs to call `signal()` to register a callback on system events (in this case, a timer). The operating system will call the registered signal when it encounters the event (timer).  
> \
> A timer interrupt cannot be used because the thread manager and library are operating in the user mode. Hence, such interrupts are invisible to them.  

18. What is done by **synchronous threading** that is usually not done by asynchronous threading?  

> In synchronous threading, the thread creator waits for the created threads to finish and join (to release its resources).  

19. Does the "P" in `Pthreads` mean "Python" threads?  

> The 'P' in `Pthreads` is POSIX.  

20. What does it mean to spawn a thread?  

> To spawn a thread is to create a thread to run a given function, instead of cloning the creator's thread like what a `fork()` does to a process.  

21. What is the purpose of calling `pthreads_join()` on a created thread?  

> `pthreads_join()` blocks the caller and waits for the created thread (specified by the `threadId` argument) to terminate and release its resources.  

22. Does `pthread_create()` make a clone of the current thread, similar to `fork()` cloning the current process?  

> No, it does not create a copy of the current thread.  

23. Why would you call `pthread_detach()` on a thread instead of calling `pthread_join()` on it?  

> Sometimes it is desirable to run the threads independently without the need to wait for it to complete or clean up its resources explicitly.  

24. In a Python generator, if you have a statement of `c = yield`, where does the yield expression get its value from?  

> `c = yield` assigns the variable `c` with the value `val` from the generator function `g.send(val)`.  

25. How do you write the producer-consumer example in Python using generators in a **push style** vs. in **pull style**?  

> Pull-style: the consumer pulling from the producer  
> ```python
> def Producer():
> 	import string
> 	for i in string.ascii_uppercase:
> 		yield i
> 
> # The consumer as main
> if __name__ == '__main__':
> 	g = Producer()
> 	for c in g:
> 		print('Consume', c)
> ```
> Push-style: the producer pushing to the consumer  
> ```python
> def Consumer():
> 	while True:
> 		c = yield
> 		print('Consumer', c)
> 
> # The producer as main
> if __name__ == '__main__':
> 	g = Consumer()
> next(g)
> 	for i in string.ascii_uppercase:  
> 		g.send(i)
> ```

26. What are two ways a thread can **exit voluntarily**?  

> 1. Implicit return: the thread voluntarily exits when it returns from the function it was assigned.  
> 2. Explicit return: the thread voluntarily exits when it calls the thread-exit function.  

27. What are the main reasons to use a **thread pool** as opposed to directly creating threads?  

> - Reusing an existing and unused thread is much faster than creating an entire new thread.  
> - Allows the number of the threads to be bounded under the pool size.  

28. In OpenMP, how are threads created?  

> ```c
> #pragma omp parallel
> ```
> Creates as many threads as the number of cores.  

29. Does OpenMP support the semantics of synchronous or asynchronous threads? What type of parallelism is it called?  

> OpenMP supports both synchronous and (some limited) asynchronous threads. This parallelism method is called fork-join parallelism. OpenMP allows the programmer to annotate possible parallel regions and optimize them. The compiler parallelizes these code and make threads as well as taking care of its synchronization. Although the compiler places synchronization barriers before and after parallel constructs, it can be removed using `nowait`.   

30. Do all threads of a process get duplicated by `fork()`, or what would `fork()` do?  

> This depends on implementation.  
> \
> POSIX `fork()` duplicates only the thread that calls `fork()`, but warns that `fork()` must only be called from a single-threaded process. Solaris `fork()` duplicates all threads. Meanwhile, other implementations have two versions of `fork()`.  

31. If you use `signal()` to register a callback, which thread or threads would get the signal?  

> This depends on implementation.  
> \
> Single-threaded: system calls the registered callback function.  
> Multi-threaded:  
> - The signal is delivered only to the thread that is applicable.  
> - The signal is delivered to every thread in the process.  
> - The signal is delivered only to certain threads in the process.  
> - The signal is delivered only to a specifically assigned thread to receive all signals for the process.  

32. When `pthread_cancel()` is called on a thread `t`, is `t` terminated immediately or in what way?  

> `pthread_cancel()` is a deferred cancellation by default. The cancellation is merely a suggestion to terminate. The thread `t` periodically checks if it should be terminated and gets the chance to clean up before termination.  
> \
> Furthermore, threads can enable or disable cancellation and gets to decide cancellation point by calling `pthread_testcancel()`, where the cancellation only occurs when thread reaches the cancellation point and the cleanup handler is invoked.   

33. What is **thread-local storage (TLS)** and how is it different from **local variables**?  

> The thread-local storage is the global variable defined within a thread but not shared with other threads. It is somewhat like a static data exclusive to a thread. As opposed to local variables which are visible only during a single function invocation, thread-local storage is visible across function invocations.  

34. How are **scheduler activations** used with the user-thread scheduler?  

> The association between a user-level thread and a kernel-level thread is known as a scheduler activation.  
> \
> When a program creates user threads, these threads are managed by a user-thread scheduler, which operates at the user level.  
> \
> When a user-level thread is scheduled for execution on a specific processor core, the user-thread scheduler activates the corresponding scheduler activation, which causes the associated kernel thread to execute on that core.  
> \
> When a user thread needs to wait for an event or perform a blocking call, the kernel performs an upcall to the user thread scheduler, the kernel can allocate another kernel thread to execute some other user thread.  
> \
> After unblocking, the kernel performs another upcall to the user thread scheduler to schedule for the freed up kernel thread.  

35. How does Linux `clone()` create processes and threads?  

> Linux `clone(flag)` creates a process by copying all of its resources if there is no sharing flag (`CLONE_FS`, `CLONE_VM`, `CLONE_SIGHAND`, and `CLONE_FILES`) set. Meanwhile, it will create a thread if all sharing flags are set.  

## 2. Thread Exercises  

QuickSort is a popular algorithm for sorting.  Even though its worst-case runtime complexity is quadratic time, its average complexity is `O(nlog(n))`, and in practice it is very fast because it is in-place sorting (i.e., does not need a temporary buffer).  Also, as a divide-and-conquer algorithm, it does most of the work in the “divide” stage and no work in the “conquer” stage. This makes it nice for parallelizing, because after forking, there is no dependency after joining.  

The following is a Python 3 implementation of Quicksort.  

```python
def Partition(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if (A[j] <= x):
            i = i + 1
            A[i], A[j] = A[j], A[i]
    A[i+1], A[r] = A[r], A[i+1]
    return i + 1

def QuickSort(A, p, r):
    if p < r:
        q = Partition(A, p, r)
        QuickSort(A, p, q-1)
        QuickSort(A, q+1, r)

if __name__ == '__main__':
    LEN = 10
    L = list(range(LEN))
    import random
    random.shuffle(L)
    QuickSort(L, 0, len(L)-1)
    if L == list(range(LEN)):
        print("successfully sorted")
    else:
        print("sort failed: %s" % L)
```

36. Convert `quicksort.py` to C and call it `quicksort.c`

Content of `quicksort.c`.  

```c
#include <stdio.h>
#include <stdlib.h>

int *A;

int partition(int l, int r)
{
    int pivot_value = A[r - 1];
    int pivot_position = l - 1;

    for(int i = l; i < (r - 1); ++i)
    {
        if(A[i] <= pivot_value)
        {
            ++pivot_position;

            int temp = A[pivot_position];
            A[pivot_position] = A[i];
            A[i] = temp;
        }
    }

    int temp = A[pivot_position + 1];
    A[pivot_position + 1] = A[r - 1];
    A[r - 1] = temp;

    return (pivot_position + 1);
}

void quicksort(int l, int r)
{
    if(l < r)
    {
        int pivot_position = partition(l, r);

        quicksort(l, pivot_position);
        quicksort(pivot_position + 1, r);
    }
}

int main()
{
    FILE *fh = fopen("randomInt.txt", "r");
    
    int len; fscanf(fh, "%d", &len);

    A = calloc(len, sizeof(int));
    for(int i = 0; i < len; ++i) {fscanf(fh, "%d", &A[i]);}

    fclose(fh);

    /* int len = 10;
    int arr[] = {9, 0, 8, 1, 7, 2, 6, 3, 5, 4};
    A = arr; */

    quicksort(0, len);
    for(int i = 0; i < len; ++i) {if(A[i] != i) {fprintf(stderr, "Bug: A[%d] =%d\n", i, A[i]); return 1;}}
    
    printf("ALL ACCEPTED!\n");

    return 0;
}
```

37. Convert `quicksort.py` to threaded version (name it `qsortTh.py`) using Python’s threading package. Good places to convert to threads is one of the recursive calls in `QuickSort`, since the two work on two disjoint parts of the array and are therefore independent of each other.  

Content of `qsortTh.py`:  

```python
from sys import stderr
import threading

LEN = 0
A = []
CUR_THREAD = 0
MAX_THREAD = 0

def partition(l, r):
    global A
    pivot_value = A[r - 1]
    pivot_position = l - 1

    for i in range(l, r - 1):
        if (A[i] <= pivot_value):
            pivot_position += 1
            A[pivot_position], A[i] = A[i], A[pivot_position]
    
    A[pivot_position + 1], A[r - 1] = A[r - 1], A[pivot_position + 1]

    return (pivot_position + 1)

def quicksort(l, r):
    global A, CUR_THREAD, MAX_THREAD
    if (l < r):
        pivot_position = partition(l, r)

        l_thread, r_thread = -1, -1
        if (CUR_THREAD < MAX_THREAD):
            ++CUR_THREAD
            l_thread = threading.Thread(target = quicksort, args = (l, pivot_position))
            l_thread.start()
        else:
            quicksort(l, pivot_position)
        if (CUR_THREAD < MAX_THREAD):
            ++CUR_THREAD
            r_thread = threading.Thread(target = quicksort, args = (pivot_position + 1, r))
            r_thread.start()
        else:
            quicksort(pivot_position + 1, r)

        if(l_thread != -1):
            --CUR_THREAD
            l_thread.join()
        if(r_thread != -1):
            --CUR_THREAD
            r_thread.join()
        
if __name__ == '__main__':
    
    with open('../c/randomInt.txt') as fh:
        LEN  = int(fh.readline())
        A = [*map(int, fh.readlines())]

    quicksort(0, LEN)

    for i, v in enumerate(A):
        if(i != v):
            stderr.write(f'Bug A[{i}] = {v}')
            exit(1)
    
    print('ALL ACCEPTED!')
```

38. Convert `qsortTh.py` from to C (and name it `qsortTh.c`) using Pthreads. Note that the idea is similar to the Python version but slightly different.  

Content of `qsortTh.c`:  

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 200

int *A;

int partition(int l, int r)
{
    int pivot_value = A[r - 1];
    int pivot_position = l - 1;

    for(int i = l; i < (r - 1); ++i)
    {
        if(A[i] <= pivot_value)
        {
            ++pivot_position;

            int temp = A[pivot_position];
            A[pivot_position] = A[i];
            A[i] = temp;
        }
    }

    int temp = A[pivot_position + 1];
    A[pivot_position + 1] = A[r - 1];
    A[r - 1] = temp;

    return (pivot_position + 1);
}

void *quicksort(void *arg)
{
    int l = ((int*)arg)[0], r = ((int*)arg)[1];
    if(l < r)
    {
        int pivot_position = partition(l, r);

        pthread_t l_thread, r_thread;

        int l_arg[2] = {l, pivot_position};
        int l_err = pthread_create(&l_thread, NULL, quicksort, (void*)l_arg);
        if(l_err != 0)
        {
            fprintf(stderr, "Thread creation unsuccessful\n"); exit(1);
        }
        int r_arg[2] = {pivot_position + 1, r};
        int r_err = pthread_create(&r_thread, NULL, quicksort, (void*)r_arg);
        if(r_err != 0)
        {
            fprintf(stderr, "Thread creation unsuccessful\n"); exit(1);
        }

        pthread_join(l_thread, NULL);
        pthread_join(r_thread, NULL);
    }
}

int main()
{
    FILE *fh = fopen("randomInt.txt", "r");
    
    int len; fscanf(fh, "%d", &len);

    A = calloc(len, sizeof(int));
    for(int i = 0; i < len; ++i) {fscanf(fh, "%d", &A[i]);}

    fclose(fh);

    int initial_arg[2] = {0, len};
    quicksort(initial_arg);

    for(int i = 0; i < len; ++i) {if(A[i] != i) {fprintf(stderr, "Bug: A[%d] = %d\n", i, A[i]); return 1;}}
    printf("ALL ACCEPTED!\n");

    return 0;
}
```

## 3. Performance Analysis  


Present a table of runtime that you measured using the time command for running
```
$ time python3 quicksort.py 
$ time python3 qsortTh.py 
$ time ./quicksort 
$ time ./qsortTh 
```

> LEN = 2000
> ```
> > Measure-command {.\quicksort}
> > TotalMilliseconds : 40.4284
> > Measure-command {.\quicksortTh}  
> > TotalMilliseconds : 397.2645  
> > Measure-command {python3 quicksort.py}
> > TotalMilliseconds : 89.7614
> > Measure-command {python3 quicksortTh.py}
> > TotalMilliseconds : 85.3875
> ```

Is the threaded version faster or slower than the unthreaded version in C?  in Python Explain why in each case.  

> For Quick Sort written in C programming language, the threaded version performs poorer than the original one. This might be the case because the workload involved in the creation of thread is relatively larger than the workload involved in merely performing the Quick Sort algorithm itself.  
> \
> However, for Quick Sort written in Python programming language, the workload involved in the creation of thread is relatively lighter than the workload involved in merely performing the Quick Sort algorithm itself. Hence, the thraded version performs better than the original one.   

