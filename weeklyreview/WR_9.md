# Weekly Review 9

## 1. Definitions and Short Answers  

1. Given two processes

```python
process1:
  lock(mutex1)
  lock(mutex2)
  work()
  unlock(mutex2)
  unlock(mutex1)

process2:
  lock(mutex2)
  lock(mutex1)
  work()
  unlock(mutex1)
  unlock(mutex2)
```

- Do they always deadlock?  

> There is no guarantee that a deadlock will occur. It depends whether the two processes were running concurrently or when does the preemption take place.  

- Do they sometimes deadlock?  If so, describe one such condition  

> One occasion where a deadlock will occur is when `process1` locks `mutex1` and got preempted by timer and control goes to `process2` where `mutex2` got locked.  
> \
> At this moment, both the processes enter a deadlock state since `process1` cannot obtain `mutex2` but holds `mutex1` and `process2` cannot obtain `mutex1` but holds `mutex2`.  

2. If two processes are not blocked but busy trying and keep failing to make progress, is it a deadlock?  

> No, this is a livelock. A livelock is a situation that occur in concurrent or distributed systems where two or more processes or threads are actively tryng to resolve a resource conflict or coordination issue, but their actions effectively prevent the system from making progress.  

3. What are the **four necessary conditions of a deadlock**?  

> 1. Mutual exclusion: only at most one process can use a resource at any given time.  
> 2. Hold and wait: a process holding at least one resource is waiting to acquire an additional resources held by other processes.  
> 3. No preemption of resources: a process only releases the obtained resource after it finishes itss task.  
> 4. Circular wait: there exists a set P<sub>0</sub>, P<sub>1</sub>, ..., P<sub>n</sub> of waiting processes such that P<sub>i-1</sub> is waiting for a resource that is held by P<sub>i</sub>, for all i in `[1, n]` and P<sub>n</sub> is waiting for a resource held by P<sub>0</sub>.  

4. If **mutual exclusion** is a necessary condition for a deadlock, then does it mean that:  

- If you use a mutex then you **always** have the possibility of getting a deadlock?  

> No, the use of a single mutex does not satisfy the hold and wait property since the process is not waiting for additional resources.  

- If you use a **counting semaphore** of `n > 1` then you won't get into a deadlock?   

> No, a deadlock can occur even by using a counting semaphore.  
> \
> Consider the case where there are two resources R<sub>1</sub> and R<sub>2</sub>, where they have two instances each and guarded by a counting semaphore R<sub>1</sub> and R<sub>1</sub>, respectively. Furthermore, there exists three processes P<sub>1</sub>, P<sub>2</sub>, and P<sub>3</sub>:  
> - P<sub>1</sub> is currently holding one instance of R<sub>1</sub>, but requesting one instance of R<sub>2</sub>.  
> - P<sub>2</sub> is currently holding one instance of R<sub>1</sub>, but requesting one instance of R<sub>2</sub>.  
> - P<sub>3</sub> is currently holding two instances of R<sub>2</sub>, but requesting two instances of R<sub>1</sub>.  
> It is obvious that there is a deadlock even with two coutning semaphores.  

5. If hold-and-wait is a necessary condition for a deadlock, then does it mean that  

- If you acquire multiple resources, then you always have the possibility of getting into a deadlock?  

> No, if the process is not fighting over resources with other processes, then there is no possibilty of deadlock.  

- If you acquire multiple resources but at most one at a time, then you won't get into a deadlock?  

> No. Consider the code below.  
> ```python
>process1:
>  lock(mutex1)
>  lock(mutex2)
>  work()
>  unlock(mutex2)
>  unlock(mutex1)
>
>process2:
>  lock(mutex2)
>  lock(mutex1)
>  work()
>  unlock(mutex1)
>  unlock(mutex2)
> ```
>   
> The process above is acquire one resource at a time, but when `process1` locks `mutex1` and got preempted by timer and control goes to `process2` where `mutex2` got locked.  
> \
> At this moment, both the processes enter a deadlock state since `process1` cannot obtain `mutex2` but holds `mutex1` and `process2` cannot obtain `mutex1` but holds `mutex2`.  

6. If no-preemption is a necessary condition for a deadlock, then does it mean that  
- All preemptive process (or thread) schedulers can get into deadlocks?  

> No, the preemption in 'no-preemption' refers the giving up of resource by the process. If some processes satisfy all four necessary conditions of deadlock, then a deadlock exists.   

- If a process P1 holds a mutex but is now blocked while waiting to acquire another resource, **preemption** in this case means to temporarily allow another process P2 to acquire that mutex, finish, and give the mutex back to P1?  

> True.  

7. If circular-wait is a necessary condition for a deadlock, then does it mean that whenever you have a process P1 that is waiting to acquire an instance of a resource type R1 that is currently assigned to process P2 and P2 is waiting to acquire an instance of a resource type R2 that is currently assigned to process P1, then you have a deadlock?  

> Assuming no preemption of resources, then, in this case, we have a deadlock.  

8. A resource-allocation graph (RAG) can be used to model a system for deadlock analysis.  
- Is a RAG a bipartite graph?  If so, what are the two sets of vertices and what do they represent?  

> A resource-allocation graph (RAG) have two disjoint sets of vertices: a set of processes and a set of resource types.  

- Is a RAG a directed or undirected graph?  

> A resource-allocation graph (RAG) is a directed graph.  

- How is a resource request represented in the RAG?  

> A resource request is represented by a directed edge from a process to a resource.  

- How is a resource assignment represented in the RAG?  

> A resource assignment is represented by a directed edge from a resource to a process.  

9. Give a RAG that contains **a cycle but does not have deadlock**.

> Adjacency list:  
> P<sub>1</sub>: R<sub>1</sub> (request)  
> P<sub>2</sub>: R<sub>2</sub> (request)  
> P<sub>3</sub>:  
> P<sub>4</sub>:  
> R<sub>1</sub> (two instances): P<sub>2</sub>, P<sub>3</sub> (allocated)  
> R<sub>2</sub> (two instances): P<sub>1</sub>, P<sub>4</sub> (allocated)  
> \
> Cycle: {P<sub>1</sub>, R<sub>1</sub>, P<sub>2</sub>, R<sub>2</sub>}  
> \
> There is no deadlock because P<sub>3</sub> and P<sub>4</sub> can release one instance of each R<sub>1</sub> and R<sub>2</sub>, respectively. Then, P<sub>1</sub> and P<sub>2</sub> can continue their execution.  

10. In some RAG, having a cycle means a deadlock exists. Why would this be the case?   

> If each resource type has only one instance each, then the existence of a cycle implies a deadlock.  

11. What is the meaning of **deadlock prevention**?  What is its general approach?   

> Deadlock prevention is a technique and strategy used to proactively eliminate or avoi the conditions that can lead to deadlock in a multi-threaded or multi-processor system. Its general approach is by breaking the necessary condition for deadlock, that is, breaking at least one of the mutual exclusion, hold-and-wait, no preemption, and circular wait.  

12. What is difficult about **denying mutual exclusion** as a way of achieving deadlock prevention?  

> The approach of denying mutual exclusion is limited to the nature of the shared resources. Not all resources can allow simultaneous access, for example: printers and tape drives.  

13. What are two ways of eliminating **hold-and-wait**?  

> The approach of hold-and-wait can be done by implementing some sort of atomic multi-resource allocation. There are two approaches:  
> - Allocated all requested resources before process starts. Too impractical and inflexible for most applications since the nature of resource allocation is dynamic.  
> - Process must hold no resources before the request to all resources are granted. A process must release all currently held resources if one resource cannot be allocated and enter waiting state.  

14. What are disadvantages with the two ways of eliminating hold and wait above?  

> The disadvantages of the two ways are:  
> 1. Low resource allocation, and  
> 2. Possible starvation.  

15. What are difficulties with deadlock prevention by **allowing resource preemption**?   

> This method is not generally applicable to all types of resources. Some resources allow its state to be easily saved and restored, for example: CPU registers and memory, database transactions, etc.  
> \
> However, it does not apply to printers and tape drives. Moreover, mutex locks and semaphore cannot be preempted because it protects a separate entity of resources. The resource preemption must be done with thoughtful analysis of the semantics of the resources.  

16. What is a way of breaking **circular wait** as the fourth way of deadlock prevention?  

> An approach of breaking circular wait is to impose a total ordering of all resources types and require the requests of resources to be made with an increasing order of enumeration. This way a cycle cannot exist and the fourth necessary condition cannot hold.  

17. For **deadlock avoidance** to work, what does each process have to declare?  

> To implement deadlock avoidance, each process must declare the maximum number of each required instance beforehand.  

18. Does **deadlock avoidance** ensure that the system…  
- never gets a deadlock? (**TRUE**)  
- never enters an unsafe state? (**TRUE**)  
- always stays in a safe state? (**TRUE**)  

19. What is a **claim** in a deadlock avoidance algorithm?  

> A claim in a deadlock avoidance algorithm is a priori knowledge about the maximum number of instances of each resource type that the process may need during its execution.  

20. In the **resource allocation graph** (RAG) scheme of deadlock avoidance,  
- Why does the RAG use only a claim edge but does NOT use an edge weight to indicate the max number of instances of a resource that the process may claim?  

> The resource allocation graph scheme of deadlock avoidance assumed that there exists only one instance of a resource type. Hence, there is no need for another way to state the number of instances that a process wants to claim.  

- What is the difference between a claim edge and a request edge in the resource allocation graph scheme of deadlock avoidance?  

> Both the claim edge and request edge are directed edges from a process to a resource. However, the claim edge defines that the process might request one instance of the resource in the future. On the other hand, the request edge defines that the process is currently waiting for resource.  

- When a request is granted, what happens to the request edge?  

> The request edge turns its direction, becoming an assignment edge (from a resource to a process). It defines that the one instance of such resource is allocated to the process.  

- When the resource is released, what happens to the assignment edge?  

> The assignment edge turns its direction and becomes a claim edge (not request edge).  

- What does a cycle mean? Under what condition is a request granted?  

> A cycle in a resource allocation graph scheme of deadlock avoidance means that the system will enter an unsafe state if some requests is granted permission. A request is granted only if converting request edge to assignment edge does not result in a cycle in the graph.  

21. To use the Banker's algorithm for deadlock avoidance,  
- Banker's algorithm uses the Safety Algorithm to find a safety sequence. If such a sequence is found, is it a necessary condition or a sufficient condition that the system is in a safe state?  

> If a safety sequence is found (sufficient), then the system is in a safe state (necessary).  

- What are variables `m` and `n`?  

> `m` is the number of distinct resource types, and `n` is the number of processes.  

- What do `Available[j]` and `Work[j]` represent?  

> Assuming `j` lies in `[0, m - 1]`, `Available[j]` refers to the number of existing instances of resource `j`, and `Work[j]` refers to the number of instances of resource `j` that is not allocated yet.  

- What does the variable `int Max[n][m]` represent?  Where does this matrix get its values from?  

> Assuming `i` lies in `[0, n - 1]` and `j` lies in `[0, m - 1]`, `Max[i]` is a vector of `m` numbers, with each value indexed by `j` describing the maximum number of instances of Resource<sub>j</sub> that Process<sub>i</sub> can request.  

- What does the variable `int Allocation[n][m]` represent?  

> Assuming `i` lies in `[0, n - 1]` and `j` lies in `[0, m - 1]`, `Allocation[i]` is a vector  of `m` numbers, with each value indexed by `j` describing the number of instances of Resource<sub>j</sub> allocated to Process<sub>i</sub>.  

- What is the meaning of variable `int Need[n][m]` and how does it get its values from?  

> Assuming `i` lies in `[0, n - 1]` and `j` lies in `[0, m - 1]`, `Need[i]` is a vector  of `m` numbers, with each value indexed by `j` describing the number of instances of Resource<sub>j</sub> that Process<sub>i</sub> may need to finish its task. By definition, `Need[i] = Max[i] - Allocation[i]` for all `i`.  

- In Step 3, Process P<sub>i</sub> is chosen because its worst-case requests can be fulfilled, so why is `Allocation[i][j]` added back into `Work[j]` instead of being subtracted from `Work[j]`?  

> The process P<sub>i</sub> can run and complete its task with the remaining resources. Hence, its currently allocated resource (described by `Allocation[i]`) can be returned to the operating system (described by `Work[:] += Allocation[i]`.  

22. In the Resource-Request Algorithm, which decides whether a request Request<sub>i</sub> (by process Pi, of different resource types), 
- If `Request[i][:] <= Need[i][:]`, does it mean that the request can be fulfilled?  In other words, is it a **necessary** condition or a **sufficient** for granting the request?  

> If a request is granted (sufficient), then `Request[i][:] <= Need[i][:]` (necessary).  

- If the previous condition is a necessary condition, then what additional condition is needed in order to grant the request?  

> `Request[i][:] <= Available[:]` is needed to grant the request.  

- If the request cannot be granted, what happens?  

> The process must wait due to unavailability of the resources.  

23. A **wait-for graph** is used for deadlock detection of single-instance resource types. 
- What is the wait-for graph that corresponds to the RAG below?

	Adjacency list of the resource allocation graph (RAG):    
	R<sub>1</sub>: P<sub>2</sub>  
	R<sub>2</sub>: P<sub>1</sub>  
	R<sub>3</sub>: P<sub>5</sub>  
	R<sub>4</sub>: P<sub>3</sub>  
	R<sub>5</sub>: P<sub>4</sub>  
	P<sub>1</sub>: R<sub>1</sub>  
	P<sub>2</sub>: R<sub>3</sub>, R<sub>4</sub>, R<sub>5</sub>  
	P<sub>3</sub>: R<sub>5</sub>  
	P<sub>4</sub>: R<sub>2</sub>  
	P<sub>5</sub>:  

> Adjacency list of the wait-for graph:  
> P<sub>1</sub>: P<sub>2</sub>  
> P<sub>2</sub>: P<sub>3</sub>, P<sub>4</sub>, P<sub>5</sub>  
> P<sub>3</sub>: P<sub>4</sub>  
> P<sub>4</sub>: P<sub>1</sub>  
> P<sub>5</sub>:  

- If the wait-for graph contains a cycle, does it mean there is definitely a deadlock or just possibility of a deadlock?  

> If the wait-for graph contains a cycle, there must exist a deadlock.  

- if the processes are in a deadlock, does it mean there is definitely a cycle or possibility of a cycle?  

> By circular wait (the fourth necessary condition of deadlock), there must exist a cycle.  

- What is the complexity of cycle detection?  

> Quadratic time.  
> \
> Perform a depth first search (DFS) on every single vertex. Since the time complexity of a DFS is linear time with respect to `n`, where `n` is the number of vertices, the total complexity of a cycle detection algorithm is `n * n = n`<sup>2</sup>.  

24. For deadlock detection of multi-instance resource types, an algorithm essentially the same as the Safety Algorithm is used to detect cycles.  
- How can you tell if the processes are deadlocked after running the algorithm?  

> If there exists some index `i` such that `Finish[i]` is `False`, then the system has deadlock.  

- How do you find all the processes that have the circular dependency in the deadlock?  

> All processes such that its `Finish` value is `False` are processes that have circular dependency in the deadlock.  

25. In practice, is the deadlock detection algorithm invoked on every request?  Why or why not?  

> In practice, it is not practical to invoke the deadlock detection algorithm due its high time complexity `O(mn`<sup>2</sup>`)`. It is more likely to be invoked once every few minutes or tenths of minutes.  

26. What can an OS do after it detects a deadlock?  
- Does it abort a process?  If so, what are possible considerations?  

> Either abort all deadlocked process (expensive) or abort one process at a time until the deadlock cycle is eliminated.  
> \
> In choosing which process to abort, we consider its:  
> - Priority  
> - Time of computation (previously used time and remaining time)   
> - Used resources  
> - Needed resources to complete  
> - Number of processes to be terminated  
> - Interactive (preferred) or batch (expensive) process  

- What does **roll back** mean? Can every process be rolled back? What needs to happen first before a roll back?  

> Rolling back refers to the process of undoing or reverting the progress made by one or more processes or transactions in order to break a deadlock and restore the system to a consistent state. Not all processes can be rolled back though.  
> \
> The system would need to periodically take snapshots (or save the state) of all processes to use for the next roll back. When a roll back occurs, the process is restarted back to the snapshot (or saved state).  

- Even if a system can recover from a deadlock, what problem may still happen to some unlucky process?  

> Some unlucky process will always be picked as a victim for the rollbacks, thus causing the process to starve. One solution is to consider the number of times a process had been rolled back in selecting a victim.  

## 2. Problem Set  

27. Fix the `transaction()` function to prevent deadlocks.  

```cpp
void transaction(Account from, Account to, double amount) {
   mutex lock1, lock2;
   lock1 = get_lock(from);
   lock2 = get_lock(to);
   acquire(lock1);
      acquire(lock2);
         withdraw(from, amount);
         deposit(to, amount);
      release(lock2);
   release(lock1);
}
```

> ```cpp
> void transaction(Account from, Account to, double amount)
> {
> 	mutex lock_of_locks; // lock_of_locks protects both lock1 and lock2
> 	mutex lock1, lock2;
> 
> 	acquire(lock3);
> 	acquire(lock1);
> 	acquire(lock2);
> 	release(lock3);
> 
> 	withdraw(from, amount);
> 	depost(to, amount);
> 
> 	release(lock2);
> 	release(lock1);
> }

28. Consider a system consisting of four resources of the same type that are shared by three processes, each of which needs at most two resources. Show that the system is deadlock-free.  

> By pigeonhole principle, at least one process can get two instances of the resources. Thus, when it finishes its task and releases the allocated resources, each of the two remaining processes must be able to get two instances of resources and can finish its execution. Therefore, the system is deadlock-free.  