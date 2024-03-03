# Weekly Review 7  

# 1. Definitions and Short Answers - CPU Scheduling  

1. What are **four cases** when a **preemptive CPU scheduler** can take control?  

> A preemptive CPU scheduler can take control when:  
> 1. A process switches from the running state to the waiting state (the process is waiting for an event or is blocked by an I/O operation)  
> 2. A process switches from the running state to the ready state (the event is interrupted by an ISR)  
> 3. A process switches from the waiting state to the ready state (the event or the I/O operation the process is waiting for completes, the process returns to the ready queue)  
> 4. A process terminates   

2. What is the difference between a **scheduler** and a **dispatcher**?  

> The scheduler is responsible for making decisions about which process or thread should run next based on the given scheduling policies, while the dispatcher is responsible for the actual context switching and managing the execution environment of processes and threads.  

3. What are the **two cases** when a **non-preemptive CPU scheduler** can take control?  

> A non-preemptive CPU scheduler can take control when:  
> 1. A process switches from the running state to the waiting state (the process is waiting for an event or is blocked by an I/O)  
> 2. A process terminates  
> 3. (Optional) A process yields control  

4. What kind of problem can be caused by preemptive scheduling that is not a problem for nonpreemptive?  

> Preemptive scheduling may cause race condition, which is the inconsistent state of shared data as a result of context switching before data modification is complete. One process can overwrite the other process' changes.  

5. Does a **kernel** have to be designed to be preemptive in order to support preemptive scheduling of **user processes**?  Or can a non-preemptive kernel also support preemptive scheduling of user processes?  

> A non-preemptive can support preemptive scheduling of user processes, unless they are requesting a service in the kernel.  

6. What is the definition of CPU utilization?  

> CPU utilization is a scheduling metric that measures the percentage of the time CPU is not idle.  

- What is its range?  

> It lies between 0% to 100%.  

- What is a practical utilization level?  

> In practice, 40% is a light utilization and 90% is a heavy utilization.  

- What level is considered heavy utilization?

> 90% is considered heavy utilization.  

7. What is the definition of **throughput**?  

> Throughput is the number of processes completed in every time unit.  

8. What is the difference between **turnaround time** and **response time**?  

> Turnaround time is the time taken by a process from its submission to completion, while response time is the time taken by a process from its submission to the time when first response is produced.  

9. What is the definition of **waiting time**?  

> Waiting time is the time a process spends in the ready queue.  

10. A scheduling may have the objectives to maximize or minimize which of the following criteria?  
- CPU utilization (**Maximize**)  
- Throughput (**Maximize**)
- Turnaround time (**Minimize**)  
- Response time (**Minimize**)   
- Waiting time (**Minimize**)    

11. How does First-Come-First-Serve (FCFS) algorithm schedule processes?  
- What is an advantage with FCFS?  

> Simple, implemented by a simple First-In-First-Out (FIFO) queue.  

- What are the two disadvantages?  

> - CPU-bound processes and IO-bound processes do not mix well. Processes with short CPU bursts (IO-bound processes) wait for a long time taken by processes with long CPU bursts (CPU-bound processes).  
> - Effectively non-preemptive, not suitable for interactive systems.  

12. Consider the Shortest-Job First (SJF) algorithm:  
- What does "shortest job" refer to?  Does it refer to the job's total length? SJF is optimal for what criterion?  

> Shortest job refers to the process with minimum next CPU burst. The Shortest-Job First (SJF) algorithm is optimal for minimum waiting time.  

- Why can't true SJF be implemented?  How can it be approximated in practice?  

> Since to find the length of the next CPU burst is an undecidable problem, SJF cannot be truly implemented. However, in practice it is predicted the exponential moving average with respect to its CPU burst history.  

- What is the difference between preemptive and non-preemptive versions of SFJ?  

> Preemptive SJF can switch out the current process if a new arriving process has shorter next CPU burst. Meanwhile, the non-preemptive SFJ runs the chosen process until completion, even if a new process arrives with a shorter next CPU burst.  

13. Given a job mix:  

|Process|Burst Time|Arrival Time|  
| :-: | :-: | :-: |
| P1		| 7		| 0		|  
| P2		| 4		| 2		|  
| P3		| 1		| 4		|  
| P4		| 4		| 5		|  
 
- Draw the Gantt chart for preemptive SJF

| t	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|10	|11	|12	|13	|14	|15	|  
|:-:|:-:|:-:|	:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|  
|  P1	|R	|R	|W|W|W|W|W|W|W|W|W|R|R|R|R	|R	|  
|  P2	|	|	|R	|R	|W|R	|R	|	|	|	|	|	|	|	|	|	|  
|  P3	|	|	|	|	|R	|	|	|	|	|	|	|	|	|	|	|	|  
|  P4	|	|	|	|	|	|W|W|R	|R	|R	|R	|	|	|	|	|	|  


- What are the **response times** of P1, P2, P3, and P4?

> The response times of processes P1, P2, P3, and P4 are 0, 0, 0, and 2, respectively.  

- What is the **total waiting time** of the four processes?

> The waiting times of processes P1, P2, P3, and P4 are 9, 1, 0, and 2, respectively. Hence, the total waiting time of the four processes is 12.  

- What is the **average waiting time**? 

> The average waiting time is 3.  

- Draw the Gantt chart for nonpreemptive SJF

| t	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|10	|11	|12	|13	|14	|15	|  
|:-:|:-:|:-:|	:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|  
|  P1	|R	|R	|R	|R	|R	|R	|R	|	|	|	|	|	|	|	|	|	|  
|  P2	|	|	|W|W|W|W|W|W|R|R	|R	|R	|	|	|	|	|  
|  P3	|	|	|	|	|W|W|W|R	|	|	|	|	|	|	|	|	|  
|  P4	|	|	|	|	|	|W|W|W|W|W|W|W|R|R|R	|R	|  
 
- What are the **response times** of P1, P2, P3, and P4?  

> The response times of processes P1, P2, P3, and P4 are 0, 6, 3, and 7, respectively.  

- What is the **total waiting time** of the four processes?  

> The waiting times of processes P1, P2, P3, and P4 are 0, 6, 3, and 7, respectively. Hence, the total waiting time of the four processes is 16.  

- What is the **average waiting time**?  

> The average waiting time is 4.  

14. Consider round robin (RR) scheduling

- Does it assume preemption or no preemption?  

> Round Robin scheduling assumes preemption.  

- How does RR algorithm schedule tasks?

> The round robin algorithm schedules the tasks in a way that the processes take turns on a regular time period.  

- What is the effect of a **long time quantum**?  It becomes similar to which other scheduling policy?  

> A round robin algorithm with a long time quantum (or time slice) performs context switch less frequently. It is somewhat similar to  First-Come-First-Serve (FCFS) algorithm.  

- What is the effect of a **short time quantum**?  

> A round robin algorithm with a short time quantum (or time slice) performs context switch more frequently. However, the more frequent the context switch, the more effort is wasted in performing the context switch instead of some useful work.  

15. Given the job mix and a time quantum of 4,

|Process|Burst Time|Arrival Time|  
| :-: | :-: | :-: |
| P1		| 6		| 0		|  
| P2		| 3		| 1		|  
| P3		| 3		| 2		|  

- Draw the Gantt chart for Round Robin scheduling  

| t	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|10	|11	|12	|
|:-:|:-:|:-:|	:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|  P1	|R	|R	|R	|R	|W|W|W|W|W|W|R|R|	|
|  P2	|	|W|W|W|R|R	|R	|	|	|	|	|	|	|
|  P3	|	|	|W|W|W|W|W|R|R	|R	|	|	|	|
|  P4	|	|	|	|	|	|	|	|	|	|	|	|	|	|
 
- What are the response times of P1, P2, and P3?

> The response times of processes P1, P2, and P3 are 0, 3, and 5, respectively.  

- What is the total waiting time of the three processes?

> The waiting times of processes P1, P2, and P3 are 6, 3, and 5, respectively. Hence, the total waiting time is 14.  

16. Most scheduling algorithms can be expressed as a combination of priority-scheduling and preemption (or not).  What is the priority scheme and preemption option for the following algorithms?  
- FCFS  

> Equal priority and no preemption.  

- SJF  

> Priority is defined to be the inverse of the next CPU burst, and can be either preemptive or non-preemptive.  

17. What is the meaning of **starvation**?  What can cause starvation, and what is a possible solution?  

> A process is said to be starving if the process is consistently denied access to the resources it needs to execute, causing it to wait indefinitely or significantly longer than expected.  
> \
> An unfair scheduling policy may cause a process to starve. A possible solution is aging, which is to increase the priority of processes as time progresses.  

18. What is the difference between **multilevel queue scheduling** and **multilevel feedback queue scheduling**?  

> In multilevel queue scheduling, the ready queue is partitioned into separate queues. Processes stay in their queue and do not move between queues.  
>\
> In multilevel feedback queue scheduling, the ready queue is also partitioned into separate queues, but processes can move between queues (aging can be implemented as moving between queues). I/O-bound and interactive processes (with short CPU burst) stay in the higher priority queues, while CPU-bound processes stay in the lower priority queues.  

19. What is the scope of contention for  
- User-level (many-to-one and many-to-many) thread scheduling?  

> The scope of contention for a user-level thread scheduling is within the process (Process-Contention Scope or PCS).  

- (one-to-one) kernel thread scheduling?  

> The scope of contention for kernel thread scheduling is among all the kernel threads in the system (System-Contention Scope or SCS).  

20. For multiiprocessor scheduling, what is asymmetric vs. symmetric multiprocessing?  

> Asymmetric multiprocessing is the scheme where a (master) processor performs the scheduling of processes centrally and all the other (slave) processor executes the user code as instructed. The master processor could become a bottleneck.  
> \
> Symmetric multiprocessing (abbreviated as SMP) is the scheme where every processor schedules itself. There are two options of implementations:  
> - Each processor has its own private queue,  
> - All processors share a ready queue, but require synchronization to allow this.  

- Which one does scheduling centrally on one processor, and which one lets each processor schedule its own processes?  

> Assymetric multiprocessing does the scheduling centrally on one master processor. Meanwhile, the symmetric multiprocessing lets the processor schedule its own processes.  

- What are two scheduling options in SMP, and which option needs additional mechanisms?  Which one is more common?  

> The are two options of implementations:  
> - Each processor has its own private queue  
> - All processors share a ready queue, but require synchronization to allow this  
> \
> The latter is a more common approach.  

21. What are two ways two interpret "load balanced"?  

> There are two ways to interpret 'load balanced':  
> - Every private queue has equal number of threads 
> - All queues have an equal distribution of thread priorities.  

22. What are two kinds of migration during load balancing?  

> There are two kinds of migration during load balancing:  
> - Pull migration: idle CPU pulls waiting process from busy CPU  
> - Push migration: Budy CPU pushes waiting process to a less busy or idle CPU  

23. What is **processor affinity** of a process?  

> Process affinity is the closeness between a process and the processor (specifically, the cache contents of the processor). It is costly to invalidate and repopulate the cache when moving a process into another processor, especially in a non-uniform memory architecture (NUMA).  

24. What are two kinds of affinity policies an OS can set on process migration?  

> The two kinds of affinity policies on process migration include:  
> 1. Soft affinity: the operating system will try to keep process on the same processor  
> 2. Hard affinity: the operating system allows process to migrate but only strictly onto a subset of processors.  

25. In a NUMA, what are the processors with **high processor affinity** for a process?  

> In a non-uniform memory architecture (NUMA), processors with memory allocated to the the memory of the process have high processor affinity for the process.  

26. What is the difference between **heterogeneous multiprocessing (HMP)** and **asymmetric multiprocessing**?

> Heterogeneous multiprocessing mixes high-performance (with higher power consumption) and low-power (with low-performance) multiprocessors with varying architecture and processing power. It is primarily invented with the motivation to improve power efficiency especially in mobile devices.  
> \
> Meanwhile, asymmetric multiprocessing involves only one type of core identical in terms of architecture and processing power, and assigns one core with the role of 'master' and others with the role of 'slave'. The master core is responsible for managing the system and running the operating system, while slave cores execute user codes.  

27. What is a difference between how a **soft real time system** and a **hard real time system** in terms of treatment of real-time tasks?  

> Soft real time system is a best-effort system that provides preferences but not guarantee in scheduling real-time processes. In this type of system, missing a deadline is undesirable but not critical.  
> \
> Hard real time system, on the other hand, guaranteees in meeting deadline once the task is accepted. In this type of system, missing a deadline leads to fundamental failure.  

28. What does **event latency** refer to?  From the time an event occurs to?  

> Event latency is the amount of time from the occurrence of the event to the (start) time when the event is serviced. Event latency encompasses the delay between any event and the system's response to that event, which may include both hardware-generated and software-generated events.  

29. The **interrupt latency**  
- Is defined to be the amount of time from an arrival of interrupt to?  

> Interrupt latency is the amount of time from the arrival of an interrupt to the start time of ISR execution.  

- for real-time systems, it is not enough to just minimize the interrupt latency but it must also be?  

> The interrupt latency must be bounded.  
> \
> Bounded interrupt latency allows for predictable and reproducible behaviors because it ensuress that system can respond to interrupts within known and acceptable time limits. Furthermore, bounded interupt latency also prevents starvation from occurring to low-priority processes.  

30. The **dispatch latency**  
- Is defined to be the amount of time for the dispatcher to?  

> Dispatch latency is the amount of time for the dispatcher to switch between processes.  

- Is best minimized through?  

> The dispatch latency is best minized through preemptive kernel.  

- Dispatch latency is further decomposed into **conflicts** and **dispatch** times. The conflicts time consists of time due to?  

> The conflict time involves the preemption of any running process in kernel mode and the release of the resources by low-priority process so high-priority can access them. Meanwhile, the dispatch time involves the procedure of context switching.  

31. What is the difference between **online scheduling** and **offline scheduling**?  

> Online scheduling is performing schedulability analysis and the actual scheduling at runtime or dynamically. It requires an admission control that can accept or reject tasks based on the ability to meeting the timing constraints.  
> \
> Meanwhile, offline scheduling assumes that the workload is known before runtime and does the schedulability analysis and the actual scheduling before running. The operating system just dispatches processes with respect to the given schedule.  

- Do both need to do schedulability analysis?  

> Yes, both the online and offline scheduling require schedulability analysis.  

- What does admission control mean?  

> Admission control is a mechanism used by online scheduling to accept or reject tasks based on the ability to meeting the timing constraints.  

- What happens when an online scheduler is asked to schedule another real-time task but won't be able to guarantee meeting its timing constraints?  

>The online scheduler, though the admission control, will reject the given real-time task.  


32. How is a periodic task defined? It can have up to four variables. What are they?  

> Periodic task is a task that is recurring in a regular intervals. It is characterized by four variables:  
> 1. Period (`p`): the time interval between successive releases or activations of the task.  
> 2. Deadline (`d`): the maximum amount of time within the period in which the task must complete its execution after being released.  
> 3. Execution time (`t`): the amount of CPU time required to complete one instance or iteration of the task.  
> 4. Offset or Phase or Release Time (`phi`): the time delay or shift between the start of a task's period and its first release.  

33. What can an aperiodic task be?  Can it repeat?  if so, what would be some condition?  

> Aperiodic task is non-recurring, but it may repeat but not before some minimum separation.  

34. In **rate monotonic** (RM) scheduling,  
- Are the tasks periodic or aperiodic?  

> The tasks in rate monotonic (RM) scheduling is periodic.  

- What is the deadline defined to be?  

> Deadline in rate monotonic scheduling is defined to be the end of the task's period.  

- Is rate monotonic preemptive or not?  

> Rate monotonic assumes preemption. 

- Is rate monotonic fixed or dynamic priority?  

> Rate monotonic assumes fixed priority.  

- How does rate monotonic define the priority of a task?  

> Rate monotonic defines the priority of a task based on the length of every task period.  

- Does the rate-monotonic priority of a task depend on the task's execution time?  

> The priority in rate monotonic does not depend on the task's execution time.  

35. In earliest deadline first (EDF) scheduling,  
- Can the tasks be periodic? aperiodic?  

> Tasks can be periodic or aperiodic.  

- Is EDF preemptive or nonpreemptive?  

> Earliest deadline first (EDF) also assumes preemption.  

- Is EDF static priority or dynamic priority?  

> Earliest deadline first has dynamic priority. The priority of a process increases as it approaches its deadline.  

- How does EDF define the priority of a task?  

> The priority defined by earliest deadline first is the inverse of time to deadline.  

36. What is the schedulability condition for rate monotonic?  Is it a necessary or a sufficient condition or both?   

> The sufficient condition for the schedulability condition for rate monotonic is that the utilization `<= ln(2)`.  

37. What is the schedulability condition for EDF?  Is it a necessary or sufficient condition or both?  

> The (both necessary and sufficient condition) for the schedulability condition for earliest deadline first is that the utilization `<= 100%`.  