# Weekly Review 4  

## 1. Definitions and Short Answers  - Week 4  

1. What is the difference between a program and a process?  Which one is active and which one is passive?  

> A program is the passive executable code that resides in the hard disk. Meanwhile, a process is the active instance of a program in execution (started running but not yet finished) in the memory or the CPU.  

2. What is a **job**?  

> A job is synonymous to a process. It is adopted from the scheduling literature of job-shop scheduling.  

3. What is a **task**?  

> A task is, also, synonymous to a process. It is the user's vieew of 'a unit of work that needs to be done.' In real-time systems, a task can have a lighter weight than a process (which must satisfy soft or hard deadlines).  

4. What is the **text section** of a process's memory?  

> The text section of a process, residing in the lowest part of the memory, stores the instructions (code).  

5. What is the difference between the **data** section and **heap** section of a process's memory?  

> The data section of a process stores the global and static variables of the process. Meanwhile, the heap section of a process stores the dynamically allocated objects of the process.  

6. What is kept in the **stack** section of a process's memory?  

> The stack section of a process stores the auto local variables of functions, parameters passed into function calls, and their return addresses (activation records).  

7. Besides the content of the main memory in a process's address space, what other **state** does a process have (that is maintained by the OS)?  

> The operating system also maintains the program counter, register values, and a set of associated resources (for example: FILE handles).  

8. What are the **five states of a process** (in the textbook's terminology)?  

> The five states of a process are defined to be:  
> - New - the process is being created by the OS.  
> - Ready - the process is in memory, can be assigned to a processor, but it is not currently running.  
> - Running - the process' instructions are being executed by the processor.  
> - Waiting - the process is waiting for some event (being 'blocked'), could be due to I/O.  
> - Terminated - the process has finished execution, its space can be reclaimed.  

9. On a single processor, how many processes can be in **running** state at a time? in **ready** state? in **waiting** state?  

> In a single processor, since the processor can only execute one process at a time, only at most one process can be running state at any time. Multiple processes can be in the ready or waiting state.  

10. Why would a process enter **waiting** state?  

> A process can enter the waiting state if it gets blocked by some events (for example: waiting for I/O operations).  

11. From which three states may a process **transition to ready state**?  

> 1. A new process can be admitted by the operating system and transition to the ready state.  
> 2. A running process can transition to the ready state when interrupted by an ISR or a timer interrupt.  
> 3. A waiting process can transition to the ready state when the blocking event or I/O is completed.  

12. How can a process transition from **running to ready state** without doing any system call?  

> When a running process is interrupted by an ISR, it transitions from the running state to the ready state.  

13. In the process control block (PCB), what is the meaning of the following fields?  
- **Program counter**  

> The program counter in the PCB stores the address of the next instruction in the program to be executed.  

- **Process number**  

> The process number field in the PCB stores the unique ID assigned to the process.  

- **CPU registers**  

> The CPU Register field in the PCB stores the state of registers, which includes: accumulator, base, registers, and general purpose registers. The states of special function registers are _not_ stored in the PCB.  

- **Memory management information**  

> The memory management information field in the PCB stores the information about the memory allocated the process. This includes page tables, segment tables, etc.  

- **Accounting information**  

> The accounting information field in the PCB stores the information about the CPU time used, elapsed clock time since start, time limits of the process.  

- **I/O status information**  

> The I/O status information field in the PCB stores the information of the I/O devices allocated to the process and the list of opened files.  

14. What is a **thread of execution**?  

> A thread is the basic unit of program execution. Multiple threads may belong to one process, which cause them to share code section, data section, and OS resources. A thread has its own thread ID, program counter, register set, and a baby stack (allocated in the heap section of the process).  

15. On a single(-core) processor,  
	a. how many **processes** can be **running** at a time? (**ONE**)  
	b. how many **threads** can be **running** at a time? (**ONE**)  

16. On a multiprocessor system,   
a. how many processes can be running at a time?  

> In a multiprocessor system, the number of processes that can be running at any given time depends on both the number of processors (or cores) available and the way the system is designed and managed.  

b. how many threads can be running at a time?  

> In a multiprocessor system, the number of threads that can be running at any given time depends on both the number of processors (or cores) available and the way the system is designed and managed.  

17. What is the definition of the **degree of multiprogramming**?  Does it reflect
- the number of processors in the system? (**Maybe**)   
- the number of processes currently running, waiting, ready? (**YES**)  
- the number of threads currently running, waiting, ready?  
- the amount of main memory in the system?   
- the scheduling policy? (**Maybe**)  

18. What is the difference between an **I/O-bound** and a **CPU-bound process**?  

> An I/O-bound process is a process that spends more time performing I/O operations than computing with many short CPU bursts. Meanwhile, a CPU-bound process spends more time doing computation with fewer but longer CPU bursts.  

19. What does **context switching** mean?  

> Context switching is a procedure that a CPU performs to change from executing one process to executing another while ensuring that the tasks do not conflict.  

20. What are the possible triggers for context switch?  

> Interrupts and system calls can possibly trigger context switches.  

21. What are the steps taken by the kernel to switch from process P1 to process P2?  

> The following steps are taken:  
> - Stop executing P1  
> - Save P1's state into the PCB of P1  
> - Select P2 as the next process to run next  
> - Restore P2's state from the PCB of P2  
> - Execute P2

22. What kinds of support can hardware provide to help reduce the overhead of context switching?  

> Hardware supports can provide:  
> 1. An instruction that performs store and load for multiple registers.  
> 2. Register windows or multiple register banks.  

23. What is a pid?  

> Process identifier (pid) is a unique identifier in the form of a non-negative integer assigned to a process.  


24. In a Unix-like system, how is `fork()` used for creating a new process?  

> A `fork()` clones the current process, making it a parent process and producing a child process with an identical content in its address space. The two processes can execute concurrently after `fork()`.  

25. After `fork()` creates the child process, where in the program does the child process start running?  

> After a child process is created by a `fork()`, it starts running right after the previously invoked `fork()` instruction.  

26. What is the meaning of the return value of `fork()`?  

> The parent process will receive the process identifier (pid) of the created child process as the return value of `fork()`, while the child process will receive 0.

27. What does `exec()` do?  Does it create a new process?  Does `exec()` return?  

> `exec()` replaces the process itself with the specified program in the argument and restarts the process as a whole. It does not create a new process as it reuses the same process. `exec()` only returns -1 (with `errno`) only if an error occurs.  

28. How does a shell launch a program as a new process using `fork()` and `exec()`?  

> The shell parses the command line, extracting the program name and arguments. Then, it calls `fork()` to create a new process to create a child process for the new program. The child process then calls `exec()` to load in the new program and becomes a new program. The parent process (the shell) can either continue running the shell or `wait()` the child to finish its execution.  

29. What is **copy-on-write**?   How does it improve the efficiency of the original implementation of `fork()`?  

> Copy-on-write is a memory management technique used by modern-day OS to optimize memory usage and reduce overhead caused by copying potentially unused memory contents when creating a new process. 
> \
> When `fork()` is called, the OS does not create an extra copy of the parents memory content, but instead provide a mapping to the parent's memory content until one of the processes requires the modification (write) of its content. By then, the OS will store an extra copy on demand.  

30. How many processes are created by the following example?  Explain  
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    for (int i=0; i<3; i++) {
       fork();
    }
    return 0;
 }
```
	
> 7 processed were created.  

31. How does a process terminate voluntarily?  

> A process can terminate voluntarily using `exit(status)`, which terminates the child process and returns the exit status to the parent process when it calls `wait(child pid)`.  

32. What are three reasons a child process may be terminated?  

> A child process can be terminated by three reasons:   
> 		- Child exceeds the allocated resources quota  
> 		- The child task is no longer needed  
> 		- OS have cascaded termination policy, which terminates children processes when their parent process is terminated.  

33. What does **cascaded termination** mean?  

> Cascaded termination is a policy enforced by the operating system where if a parent process is terminated, then all of its children process must also be terminated.  

34. What is an **orphan process**?  a **zombie process**?  

> An orphan process is a child process with no living parent, i.e. the parent process was killed when the child process is created.  
> \
> A zombie process is a dead child process that died before the parents call `wait()` to recollect its process identifier (pid). The process identifier (pid) of the zombie process will be recollected once the parent process calls `wait()`.  

35. What happens if the parent of a zombie process does not call `wait()`?  

> If the parent of a zombie process does not call `wait()`, then its process identifier (pid) will always stay occupied and never be recycled.  

36. What happens on termination of the orphan processes whose parent died before it had a chance to call `wait()` on its children?  What is a solution?  

> A solution would be an ancestor process (parent of the parent process) can call `wait()` to collect orphan processes.  

37. What is the name of the "root" process in traditional UNIX, with a pid of 1?  What is the LINUX version called?  

> The root process in the traditional UNIX is called `init`, meanwhile it is called `systemd` in the LINUX environment.  

38. What is the main advantage of shared memory communication over message passing and why?  What must be performed carefully for shared memory to work consistently?  

> The main advantage of shared memory communication over message passing is that it is implemented by memory access (read and write), which is faster than going through the kernel mode via `send(msg)` and `receive(msg)` system calls, which additionally incur copying overhead. However, shared memory requires more careful user synchronization.  

39. What are some ways to ensure shared data are not written simultaneously in inconsistent ways?  

> Synchronization by locking or scheduling methods can ensure that the shared data are not written simultaneously in incosistent ways.  

40. When is shared memory not an option for two processes to communicate?  

> Shared memory is not option when the two processes do not share the same physical memory.  

41. What does it mean that message passing calls such as `send()` or `receive()` may **block**?  

> Blocking `send()` or `receive()` means that the system call will wait for the return value and temporarily halts the current flow of the process.  

42. In the pseudocode for shared memory communication, what are the purposes of variables named `in` and `out`?  Which variable is modified by consumer and which is modified by producer?  Can both the sender and receiver be modifying the same variable at the same time, assuming they can run at the same time?  

> The sender modifies the variable `in`.  
> The receiver modifies the variable `out`.  
> Both the sender and receiver cannot write into the same variable since they only write to one of the variables.  

43. What is "direct communication" (style of message passing) between two processes?  How many processes can a link be associated with?  How many links can exist between a given pair of processes?  

> The direct communication between is a style of message passing where the two ends explicitly name the other. One link of direct communication is associated with **exactly** two processes, and between a pair of processes, there exists **exactly** one direct communication link.  

44. In direct communication, how is `receive()` in asymmetric naming different from `receive()` in symmetric naming?  Can more than one sender process send messages to a given receiver process?  If so, can the receiver know the identity of the sender and how?  

> In asymmetric naming, the `receive()` system call does not need to explicitly name the sender, allowing the receiver to receive from any processes and gets the sender ID.  
> \
> Meanwhile, in symmetric naming, the `receive()` system call must explicitly name the sender.  

45. Why does direct communication have the **limited modularity** problem?  How is it solved by indirect communication?  

> The limited modularity problem arises when a name of a process changed, then the old names hardwired into the function calls requires update to function as intended.  
> \
> In the indirect communication, the mailbox determines who receives the message instead of the sender or receiver explicitly naming the other half. Hence, a name change would not affect its functionality.  

46. Does indirect communication allow one sender and multiple receivers to share the same mailbox?  

> Indirect communication allows one sender and multiple receivers. However, the implementation of the operating system can decide between many options:  
> - Allow a link to be associated with at most two processes.    
> - Allow only one process at a time to execute a `receive()` operation.  
> - Allow the system to arbitrarily select the receiver.  
> - Sender is notified who the receiver was.  

47. Is a **synchronous call** (to a function or procedure) blocking or nonblocking?  What about an asynchronous call?  

> A synchronous call is a blocking call, meanwhile an asynchronous call is a non-blocking call, requiring a separate checking operation call to check if the message receiving or sending is completed.  

48. How does a nonblocking sender/receiver know when the communication is completed (i.e., data has been sent or data is ready to be received)?  

> A nonblocking sender and receiver requires a separate checking operation call to check whether the communication is completed.  

49. What is **rendezvous communication**?  Are its sender and receiver blocking and nonblocking?  How much buffer is required, if any?  How do you pronounce "rendezvous"?  

> A rendezvous (pronounced 'ron-day-voo') communication is a communication scheme with zero buffer. It requires a blocking send and a block receive. The earlier call blocks until the other half is ready to exchange message.  

50. In bounded buffer communication, under what buffer condition does the sender block and does the receiver block?  

> In a bounded-buffer scenario:  
> - The sender blocks when the buffer is full.  
> - The receiver blocks when the buffer is empty.  

51. In infinite buffer communication, under what buffer condition does the sender block and does the receiver block?  

> In an infinite-buffer scenario:  
> - The sender never blocks.  
> - The receiver blocks when the buffer is empty.  

52. What does RPC mean?  

> Remote procedure call, abbreviated as RPC, is a mechanism that allows a program to call procedures on anotheer machine.  

53. What is a **stub function** for an RPC on the **client side**, and what does it have to do?  

> A stub function on the client side is a proxy function (or agent) on the client side that accepts and returns parameter like a normal procedure or function call. The stub function packs parameter into a message (a procedure called marshalling), then calls the operating system to send directly to the designated server and awaits for the result to return.  

54. What is a **stub function** on the **server side**, and what does it have to do?  

> A stub function on the server side is a function on the server side that receives call from the client and unpacks the encoded parameters (a procedure called demarshalling), calls the corresponding procedure, and returns the results to the caller.  

55. What do **marshaling** and **demarshaling** mean during an RPC call?  Why can't raw data be sent in their original binary representation?  What are example types that cause problems?  

> Marshalling is the procedure of the client packing the parameters into a message in a format in agreement between the client and server. In the same format, demarshalling is the procedure of the server unpacking the parameters.  
> \
> The raw data cannot be sent in their original binary representation because RPC involves communication between different processes or systems, which may use different programming languages, architectures, or data representations. Marshalling and demarshalling help bridge between these differences by converting parameters into a format that can be transmitted over the network and back into their original representation.  

56. Why do pointers cause problems when passed as parameters or returned in RPC?  

> Pointers that are either passed as parameters or returned are only meaningful within the physical memory address space. If they are sent across devices with different physical address space, they are absolutely meaningless.  

57. Can RPC always succeed?  What kind of problems can happen?  

> A remote procedure call (RPC) may fail or have duplicate execution.  
> \
> Two solutions are:  
> - At most one execution  
> &nbsp;&nbsp;A time stamp is attached to each message. The server must keep a history large enough to detect repeated messages.  
> - 	Exactly once execution  
> &nbsp;&nbsp;Server must acknowledge (ACK) to client when the RPC call is received. The client must resend each remote procedure call (RPC) periodically until the client receives an ACK from the client.  

## 2. Python Programming  

58. Write a generator for powers of 2:

> ```python
> def generator_2():
>    '''
>    Generator of power of two
>    '''
>    i = 1
>    while True:
>        yield i
>        i <<= 1
> ```

59. Write a generator for elements of a binary tree in **post-order** (i.e. left child recursively, right child recursively, root). Assume the same kind of tree representation as on the slide page 11:  

	```python
	T = (17, (12, (6, None, None), (14, None, None)), (35, (32, None, None), (40, None, None)))
	```
	
> ```python
> def postorder(T):
>    '''
>    Generator of elements in postorder of the given tree T
>    '''
>    if not T:
>        return
>    yield from postorder(T[1])
>    yield from postorder(T[2])
>    yield T[0]
> ```
	
60. Rewrite the `make_item()` generator on slide page 21 to eleminate the `for c` loop. (Hint) check out the slide page 13.  

> ```python
> def make_item():
>    '''
>    Producer make item
>    '''
>    import string
>    while True:
>        yield from string.ascii_uppercase + '\n'
> ```

61. The consumer() on slide 22 is a "pull"-style communication because the consumer asks for the next item (implicitly called by the for loop) from the generator, which does a yield of the next value.  Rewrite the `producer()` as a function and `consumer()` as a generator such that the producer "pushes" the items by calling the `send(v)` method (slide 23) to send value `v` to the consumer, which receives the value from `yield` (as an expression) and calls the `use_item()` function on each value.  In this case, `yield` just serves the purpose of "receive".

	```python
	def producer():
	    # basically the same as make_item() on slide 21, except
	    # 1. instantiate revised consumer as a generator g, and
	    # 2. call next() on g once to kickstart it
	    # 3. inside loop, yield c is replaced by a g.send(v)
	def consumer():
	    # 1. inifinite loop,
	    # 1.1  c = yield, to receive the value sent by producer,
	    # 1.2  call use_item(c), found on slide 27
	```

> ```python
> def producer():
>    '''
>    The producer of a push-style communication as a function
>    '''
>    import string
>    G = consumer(); next(G)
>    for c in string.ascii_uppercase + '\n':
>        G.send(c)
> def consumer():
>    '''
>    The consumer of a push-style communication as a generator
>    '''
>    while True:
>        c = yield
>        print(f'Consume {repr(c)}')
> ```
