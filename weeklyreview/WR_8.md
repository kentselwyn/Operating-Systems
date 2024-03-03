# Weekly Review 8  

## 1. Definitions and Short Answers  

1. In the version of producer-consumer code that uses both `in`/`out` and `count`, race conditions could occur.  

```python
// Producer
while (1) {
    nextItem = getItem();
    while (count==BUFSIZE) ;
    buffer[in] = nextItem;
    in = (in+1) % BUFSIZE;
    count++;
}


// Consumer
while (1) {
    while(count==0) ;
    item = buffer[out];
    out = (out+1) % BUFSIZE;
    count--;
}
```

- Give one example where one process' update is lost due to overwriting by the other process, assuming preemptive scheduling.  

> Suppose the machine is a RISC architecture, where the update on `count` is implemented by:  
> ```asm
> la $4, mem
> lw $10, ($4)
> addi $10, $10, 1
> sw $10, ($4)
> ```
> Also, suppose that the value of `count` is currently `5`.  
>\
> Assume that the `Producer` executes `count++` up to `addi $10, $10, 1` and preemption occurs. Now the temporary variable stored in `Producer` is the value `6`, but the `count` in the memory still retains the value `5`. On the `Consumer` procedure, it executes `count--` and saves the new value `4` into the memory. When a preemption happens, the `Producer` continues to execute `sw $10, ($4)` and saves the value `6` into the memory, overwriting the change by the `Consumer`.  

- Explain how the race condition causes incorrect results.  

> Race condition in the example causes memory inconsistency of the variable `count`. The `Consumer` assumes that it will get the newest value of `count` unaware that a preemption happens before `Producer` renews its value.  

- Where can you convert into critical sections to eliminate the race condition?  

> The `count++` in the `Producer` function and `count--` in the `Consumer` function should both be critical sections.  

2. What are the three requirements of a **critical section**?  

> 1. Mutual Exclusion: at most one process in critical section at any given time  
> 2. Progress: if there is no process occupying the critical section and some processes wish to enter the critical section, one process must be able to enter the critical section.  
> 3. Bounded Waiting: there should a maximum number of times other processes are allowed to enter the critical section after a process has requested to enter the critical section.  

3. Of the two **software solutions** to the critical section problem, why do they work, and what are their assumptions?  
- Non-preemptive scheduling  

> 	This solution assumes that no process yields in the middle of their critical section. If no preemption occurs, then:  
> 	+ Mutual Exclusion: At any given time, only at most one process can enter their critical section.  
> 	+ Progress: The running process always enters the critical section as long as it does not yield control before it.  
> 	+ Bounded Waiting: Essentially, the running process has no waiting time.  

- Preemptive scheduling - using Peterson's Solution  

> This solution assumes preemption and no hardware support.  
> + Mutual Exclusion: When both processes wishes to enter the critical section, they set `flag[0] == 1 == flag[1]`, but relies on `turn` to decide who enters the critical section. Since `turn` can only be `0` or `1`, only at most one process can enter the critical section at any given time.  
> + Progress: The `while`-loop of a process will break out if the other process is not in the critical section. Hence, there must be a process that enters the critical section when the two processes request access.  
> + Bounded Waiting: After the first process finishes execution, it always sets its `flag` into `False`, breaking the `while`-loop of the other process. Hence, the other process is guaranteed to run after at most one process when requesting to enter the critical section.  

4. If you perform **non-preemptive scheduling**, can there be a race condition?  On a single-threaded uniprocessor?  On a multiprocessor?  Why or why not?  

> In a non-preemptive scheduling, there will be a race condition if and only if there is a yield control to other processes in some critical section. This occurs for the same reason why preemption should not occur in the middle of any critical section: inconsistent memory content.  

5. Consider Peterson' solution,  
- Does it need to **temporarily disable interrupts** in the critical section?  

> It does not require disabling interrupts in the critical section.  

- Does it work on processors with **two hardware threads**? With what kind of assumptions? When can it fail when the assumptions don't hold?  

> The Peterson's solution for two processes can work with two hardware threads (or virtual processors) assuming that the compiler or CPU does not alter the ordering of the instructions (usually done for optimization). When the CPU executes the out-of-order instructions, then the values stored in the memory will be out-of-order and may cause data incoherency. This happens because the compiler or CPU is not aware of the shared memory region because it was simply defined in the user mode.  

6. What does a **memory-barrier** instruction do?  How can it be used as part of a synchronization primitive?  

> Memory barrier is a hardware or software mechanism used to ensure the proper ordering or synchronization of memory operations among multiple threads or processes in a multi-core processor.   

7. Why is it inefficient to **disable interrupts** on a **multiprocessor**?  

> Multiprocessors are developed for improved responsiveness and promote parallelism. Disabling interrupts affects all the processors and hence:  
> - Loss of Concurrency: the processor that is performing interrupt-driven activities cannot perform other useful work while interrupts are disabled.  
> - Reduced Responsiveness: Interrupts are essential for handling time-critical events, such as hardware device signalling, timer interrupts, etc.  

8. When atomic test-and-set is called as a C function, does it return true or false when you **successfully acquired the lock**?  What is the lock value after?  

> The test-and-set returns `False` when it successfully acquires the `lock`. The `lock` value is set to `True` nevertheless the `lock` is acquired or not.  

9. How can **atomic compare-and-swap** be used to implement a lock?  What **additional information** can such a locking data type provide that is otherwise not available in atomic test-and-set?  

> Atomic compare-and-swap (abbreviated as CAS) is a generalization of atomic test-and-swap. The lock can encode an information about the owner of the lock, for example: process ID.  

10. Can an atomic variable replace a critical section in general?  In what case may it fail, if any?  

> An atomic cannot replace a critical section in general. For instance, consider the case in which more than a single consumer is waiting for the shared variable `count`, implemented as a atomic variable. When `count` is updated to `1`, both consumers unblock and both attempts to enter the critical section. Hence, the mutual exclusion property is not satisfied.  

11. How do you pronounce "Dijkstra"?  

> It is pronounced 'Dike-struh'.  

12. After declaring a semaphore `S`,
- What does `wait(S)` do?  Under what condition would it block, and under what condition would it not block?  What is its effect on `S`'s value upon returning?  What causes `wait(S)` to unblock?  

> ```python
> wait(S):
> 	while(S <= 0);
> 	S--;
> ```
> Assuming a busy-wait implementation of the semaphore `S`, where `S` is the number of remaining resources, `wait(S)` blocks if there are no available resources available. When resources is available, `wait(S)` unblocks, reserves a resource, and returns.   

- What does `signal(S)` do?  Does it ever block?  If so, under what condition, or if not, why not?  What is its effect on `S`'s value upon returning?  

> `signal(S)` blocks if the `S` is currently under update by other processes. Upon returning, the `S` is incremented by 1, essentially returning one instance of resources to the resources pool.  

13. What does the **value of semaphore** `S` represent when it is positive?  When it is negative?  When it is 0?  

> When `S` is positive, then `S` resources is available. When `S` is zero, then no resources is available. Otherwise, if `S is negative, then there are `-S` number of processes waiting for resources.  

14. How can a mutex be implemented using a semaphore?  

> A mutex can be implemented by setting the initial value of semaphore `S` to `1`. A mutex is a special case of semaphore whose value can only be `0` or `1` (binary).  

15. How can **barrier synchronization** be implemented using a semaphore?  If a process P1 needs to execute A before Process P2 executes B, how can the code of the two processes be written?  Explain how the waiting process can be unblocked even though the semaphore's value is initialized to 0.  

> A barrier synchronization can be implemented by setting the initial value of semaphore `S` to `0`.  
>\
> Assuming `S` is initialized as `0`. If a process P1 needs to execute A before Process P2 executes B,  
> Process P1:  
> ```python 
> # Some code
> # A
> signal(S)
> # Some code
> ```
>Process P2:  
> ```python
> # Some code
> wait(S)
> # B
> # Some code
> ```
> When P1 calls `signal(S)`, the value of `S` is incremented by `1`. Hence, process P2 can unblock once P1 has called `signal(S)` regardless of the initial value `0` of `S`.  

16. Is it always more efficient to use non-busy-wait semaphores?  When is it more efficient to use busy-wait semaphores, if ever?  

> To use busy-wait semaphore or non-busy-wait semaphore is all up to the length of the critical section.  
> If the critical section is short (a few instructions in length), then it is better to use busy-wait semaphores as it produces less overhead for multiprocessors.  
> Otherwise, if the critical section is long, then it is better to use non-busy-wait semaphores. Polling for too long prohibits the CPU from doing useful work. It is much better to pay some multiprocessor overhead to maintain the queue.  

17. In the classical bounded-buffer problem of n-buffers, it declares three semaphores

```c
semaphore mutex = 1;
semaphore full = 0;
semaphore empty = n;
```

- What is the purpose of the semaphore `mutex`? What resource does it protect?  

> `mutex` is a binary semaphore. Its purpose is to protect and enforce the mutual exclusive access to the shared buffer.  

- What is the purpose of the semaphore `full`?  

> `full` is a counting semaphore, initialized to `0`. Its purpose is to count the number of occupied space in the buffer.  

18. Continuing with the classical bounded-buffer problem, Producer's code looks like infinite loop with body:

```c
produce next item;
wait(___);
wait(___);
enqueue next item;
signal(___);
signal(___);
```

Consumer's code looks like infinite loop with body:  

```c
wait(___);
wait(___);
dequene the next item;
signal(___);
signal(___);
```

Fill in the blanks above with the proper semaphores.  Explain why they need to go in those places.  

> Producer:  
> ```c
> produce next item;
> wait(empty);
> wait(mutex);
> // enqueue next item;
> signal(mutex);
> signal(full);
> ```
> \
> Consumer:  
> ```c
> wait(full);
> wait(mutex);
> dequene the next item;
> signal(mutex);
> signal(empty);
> ```

19. In the Readers-Writers classical synchronization problem, two semaphores `rw_mutex` and `mutex` are declared, in addition to an `int readcount=0;`
- What is the purpose of `semaphore rw_mutex;`?  Why is it initialized to `1`?  

> `rw_mutex` is a binary semaphore whose purpose is to enforce that only multiple readers or one writer with no reader can access the buffer at any givem time. It is initialized to `1`, which refers to the fact that no writer and no reader is currently writing into or reading from the buffer; the value `0` means that either a writer is writing into the buffer or some readers are reading from the buffer.  

- What is the purpose of the semaphore named `mutex` in the code?  Why is it initialized to `1` and use a separate `int readcount = 0;` instead of using a counting semaphore to keep track of the number of readers?  

> `mutex` is also a binary semaphore whose purpose is to protect and enforce the mutual exclusion to the variable `readcount`, which is the number of current reader in the buffer. It is initialized to `1`, which refers to that no processes are modifying the variable `readcount`. The value `0` means that a process is currently modifying the variable `readcount`.   
> \
> The primary use of `readcount` is to track the number of current readers, while a counting semaphore is used for different synchronization scenarios and may not be the most suitable choice for this specific problem.  
> \
> Furthermore, the comparison of the value `readcount` after each increment or decrement must also be unaffected by other process. This cannot be achieved by a counting semaphore unless there are such an extensive architecture support to do so.  

20. Continuing with the Readers-Writers classical synchronization problem, fill in the blanks below with the proper semaphores (`rw_mutex`, `mutex`):  

```python
Writer():
    while (TRUE):
        wait(____)
        code for writing
        signal(___)
Reader():
    while (TRUE):
        wait(___)
        readcount += 1
     if (readcount == 1):
        wait(___)
     signal(___)
     code to read data
     wait(___)
     readcount -= 1
     if (readcount == 0):
        signal(___)
     signal(___)
```

> ```python
> Writer():
>     while (TRUE):
>         wait(rw_mutex)
>         code for writing
>         signal(rw_mutex)
> 
> Reader():
>     while (TRUE):
>         wait(mutex)
>         readcount += 1
>      if (readcount == 1):
>         wait(rw_mutex)
>      signal(mutex)
>      code to read data
>      wait(mutex)
>      readcount -= 1
>      if (readcount == 0):
>         signal(rw_mutex)
>      signal(mutex)
> ```

21. In the Dining Philosophers problem, if the code for each philosopher is written as the following infinite loop that make use of an array of

```c
 semaphores chopstick[5] = {1, 1, 1, 1, 1};
do {
    wait(chopstick[i]);

    wait(chopStick[(i + 1) % 5]);

    eat rice;
    signal (chopstick[i]);
 
    signal (chopstick[ (i + 1) % 5] );
    think;
} while (TRUE);

```
 
- Explain a situation where a deadlock can occur.    

> For instance, every philosopher gets context switched after they execute `wait(chopstick[i])`. Now, every philosopher is holding a chopstick and no one can proceed to eating because they can never get the other chopstick.  

- Explain a situation where a philosopher might starve.  

> For instance, one philosopher never returns the two chopstick that they have taken. The two neighbors of the philosopher will never get to eat. Hence, the two neighbors have starvation.  

- What is the difference between deadlock and starvation?  

> Deadlock is the situation in which two or more processes are unable to proceed with their execution because each is waiting for the other to release a resource or lock (thus, forming a vicious cycle).   
> \
> Meanwhile, starvation is the situation in which a particular process or thread is unable to make progress or access a resource it needs, even though it is actively competing for that resource. It may occur to unfair process scheduling.  
> \
> In deadlock, a number of processes (in the vicious cycle) cannot proceed with their execution. Meanwhile, in starvation, only the starving process cannot proceed with their execution while the other processes can execute.  



