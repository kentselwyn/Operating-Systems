# Weekly Review 1

## 1. Definitions and Short Answers  - Week 1  

1. What is **batch processing**?  What are its advantages? Disadvantages?

> Batch processing is an earlier system where batches of jobs of the same type were processed one at a time. Users submit jobs - in forms of program and data on punch cards. A human operator schedules these jobs, while the OS loads and runs one job at a time.  
> \
> Advantages:  
> - Simple  
> - Requires less memory because at most only one job can be handled at any given time  
> - Less stress on processor when idle  
> - Repeated jobs are done fast without user interaaction  
> - Can assign a specific time for the batch jobs  
> Disadvantages:  
> - Not interactive  
> - Runs only one job at a time  
> - CPU is often idle, I/O speed takes much longer than CPU speed  


2. What is **multiprogramming**?  What disadvantage of batch processing does it address?

> In a mainframe, multiprogramming allows several jobs to be loaded into the memory, and CPU is **multiplexed** among jobs. If one job gets occupied with I/O, then CPU can be assigned to another loaded job.  
> \
> Multiprogramming mainly reduces the CPU idle time of batch processing. The CPU no longer needs to wait for I/O jobs to proceed into the next job.  

3. Compare **multiprogramming** and **multitasking** in terms of number of users, number of jobs running, and need for support features. (Textbook page 23)

> Number of users:  
> Multiprogramming allows only one user while multitasking supports multiple users.  
> \
> Number of jobs running:  
> Both has only one job running. Multiprogramming only switches job when the running job is occupied by I/O. On the other hand, multitasking executes multiple processes by switching among them frequently.  
> \
> Need for support features:  
> Multiprogramming: file system (storage management) support, resource protection, as well as process synchronization and communication.  
> Multitasking: memory management (virtual memory), CPU scheduling, file system (storage management) support, resource protection, as well as process synchronization and communication.  

4. What is an **instruction set architecture** (ISA)?  How is it different from a CPU or a processor?

> Instruction Set Architecture, ISA in short, is part of the abstract model of a computer that defines how the CPU is controlled by the software. ISA acts as an interface between the hardware and the software, specifying what the processor is capable of doing as well as how it gets done. A CPU and a processor are both hardwares, but ISA is a set of rules.  

5. What are reasons for the trend from single processor to multiprocessor architectures?

> The trend of switching from single processor to multiprocessor is all due to the power wall. There is no way of increasing the clock rate of a single processor without paying additional cost in power to dissipate the heat from a single high clock rate processor. Multiprocessor can achieve the same performance with much lower power.  

6. What makes tightly coupled multiprocessors difficult to scale to a large number of processors?

> In a tightly-coupled multiprocessor system, multiple processors share the same memory modules. Hence, with more processor sharing the same memory, more memory conflict arises.  

7. What are examples of **real-time systems**?  How do they differ from **high-performance** systems?

> Real-time systems are systems that are especially designed to meet some predefined timing constraints. High-performance systems are designed generally to perform high workloads with no predefined timing constraints.  

8. What are examples of **hard real-time** vs **soft real-time** systems?

> Soft real-time systems have timing constraints that are undesirable to miss, but not critical. For example: multimedia streaming.  
> \
> Hard real-time systems have timing constraints that results in fundamental failure if unsatisfied. For example: nuclear power plant controller, flight or auto control, anti-lock brakes.  
 
## 2. EdSim51 and 8051 - Week 1

9. What is an assembler?

> An assembler is a software that takes in a low-level programming language (example: Assembly) and converts them into machine language in binary. The mapping is one-to-one according to the ISA in use. 

10. Given the sample assembly program:

	```asm
	ORG  0000H
	MOV  90H, #24H
	END
	```

- What is a **directive** in this assembly program, and how is it different from an instruction?

>`ORG 0000H` and `END` are both assembler directives. These instructions are not converted into machine code and mainly serves as a symbol to the assembler.  

- What is an **instruction**?  What does the assembler do to an instruction?

> An instruction is a single task that the CPU will need to perform. An assembler converts an instruction to a machine code that will be decoded by the CPU and its corresponding behavior will be executed.

- What is an **opcode** in the above example?  An **operand**?

> `MOV` is an opcode while `90H` and `#24H` are operands.  

11. What does `90H` refer to?  What does `#24H` refer to?  Why is there a `#` in front of `24H` but not in front of `90H`?

> `90H` refers to the register in the address `0x90`.  
> `#24H` refers to an immediate with the value `0x24`.  
> The symbol `#` refers to an immediate identifier and is placed in front of a number to identify them as an immediate.  

12. What is a **NOP**? and how do you pronounce it?

> NOP, pronounced 'no-op', is short for no operation. When encountered, the CPU performs nothing.  

13. Why is 8051 called a **Harvard architecture**?  How is it different from a **von Neumann architecture**?  

> A Harvard architecture uses a separate physical memory address for instructions and data. Therefore, an instruction can be executed in a single cycle.  
> \
> A Von Neumann architecture uses the same physical memory address for instructions and data. Two clock cycles are required to execute a single instruction.  
> \
> The 8051 uses separate physical memory address for instructions and data. Hence, it is a Harvard architecture.  

14. What is a **PC** in a processor?  What are the ways PC value can change?

> A PC, short for Program Counter, is a register that points to the instruction memory address of the instruction to be executed. A PC can change when the instruction has been fetched, or a jump instruction has been executed.  

15. How many bytes is 8051’s **code memory**?  How many bits are needed to represent the code address?

> 8051 has 64 KBytes code memory. The address is 16-bit in length.  

16. What is **DPTR** in 8051?  How is it related to **DPL** and **DPH**?

> DPTR, short for data pointer, is a pointer to the starting address of data. Different from other regsters, it is 16-bit in length. DPL, short for data pointer low, and DPH, short for data pointer high, contains the lower and higher address of the pointed data memory address, respectively.  

17. How big is the **IDATA memory** in 8051?

> 256 Bytes. But 128 Bytes are reserved for special function registers (SFR).  

18. What is a **special-function register** (SFR)?

> A special-function register, abbreviated as SFR, is a register that not only stores a value (like any other registers), but also has a defined side effect. For example: the port P1 is a special function register with address `90H` and storing values will result in turning on/off the LED segments.  

19. What is the meaning of **simplex**, **half-duplex**, and **full-duplex** communication?  Which one is the UART (serial port)?

> Simplex communication refers to an one-way communication.  
> \
> Half-duplex communication refers to a communication scheme that only goes one-way at a time, but communication are supported in both ways.  
> \
> Full-duplex communication refers to a communication scheme that supports two-way communication occurring at the same time.  
> \
> UART in 8051 is full-duplex.
  

20.  if `#24H` refers to hex 24 integer value (“immediate”) in Intel assembly, why `#FFH` does not refer to hex FF integer value?  Name two ways to express `0xFF` in Intel assembly syntax.

> The syntax only allows that the `#` identifier is only followed with numbers (`0`, `1`, `2`, `3`, ..., `9`). Unless, it is regarded as a label.  
> Alternatives: `#0FFH` and `#255`.  

21. What is the meaning of `MOV A, 17`  in 8051 assembly, and how is it different from `MOV A, #17`?  What about  `MOV A, 17H`?  `MOV A, #17H` ?

> `MOV A, 17` assigns the value of register `A` with the value of register `17`, synonymous with `A = *((char*)17)`.  
> `MOV A, #17` assigns the value of register `A` with the value `17`, synonymous with `A = 17`.  
> `MOV A, 17H` assigns the value of register `A` with the value of register `0x17`, synonymous with `A = *((char*)0x17)`.  
> `MOV A, #17H` assigns the value of register `A` with the value `0x17`, synonymous with `A = 0x17`.  

22. What is a **general-purpose input/output (GPIO) port**?  What are they called on 8051?

> A general-purpose input/output (GPIO) port is a group of GPIO pins (usually in eight pins) arranged and controlled as a group. They are called the I/O ports.  
> \
> The GPIO in 8051 are `P0`, `P1`, `P2`, and `P3` with direct addresses `80H`, `90H`, `A0H`, and `BOH`, respectively.  

23. Why do you have to write a **0 bit** to **turn on** an LED segment?  Why write a **1 bit** to **turn off**?

> Although counter-intuitive to a programmer, the implementation is to avoid power being drawn from the processor immediately. Alternatively, a separate power source is supplied. Therefore, a `0` in the special function register connects the current onto the ground. Hence, a voltage difference causes the LED segment to turn on.  

24. What is an “**immediate**” operand?

> Immediate operand refers to an operand in forms of a constant value (begins with a `#` followed by a number).

25. What is a "**direct**" operand?

> A direct operand refers to an operand in forms of a register address.  

26. How do you pronounce “UART”?  What is another more descriptive term for **UART**?

> Universal Asynchronous Receiver/Transmitter, shortened as UART and pronounced 'You-Art', is a serial port.  