# Weekly Review 3

## 1. Definitions and Short Answers  - Week 3  

1. A shell can implement all of the commands the it supports, as opposed to relying on external programs that are not part of the shells. What are the advantages and disadvantages?  

> Advantages:  
> - Self-contained  
> - Efficient per command  
> \
> Disadvantages:  
> - Not scalable. It requires modification when modifying existing commands or adding new commands  

2. Does the UNIX-style shell (such as bash, csh, etc.) implement all of the commands that it can execute? Why is it a good idea?  

> No, the UNIX-style shell might have some built-in commands. For the other commands, it checks for the syntax correctness and invokes an executable corresponding to the command.  
> \
> Advantages:  
> - Smaller shell  
> - Very expandable and maintainable  
> \
> Disadvantages:  
> - Heavier weight per command   

3. Does the shell (GUI, CLI, etc.) run in user mode or kernel mode? Why?  

> Shells run in user mode.   

4. What is the purpose of a **system call**?  

> A system call is a request to the operating system to ask for services that cannot be completed in the user mode (for example: process control, file management, device management, system setting, and communication).  

5. Why doesn't a system call instruction take the target address of the routine, unlike a jump or call instruction? How does it indicate **what service to request**?  

> The address of a system call subroutine is intentionally hidden from users in the user mode to protect the operating system and its resources. A system call service can be identified by its syscall number.  

6. What are ways **parameters** can be passed to a system call?  

> Parameters can be passed to a system call by storing them into registers, a table in the memory, or stack, depending on the defined behavior by the calling convention.  

7. Are the functions in standard-I/O library `stdio.h` all system calls? For example, is `printf()` a system call? If not, how does it perform I/O operation? What actual system call does a `printf()` call?  

> No, not every function in the `stdio.h` is a syscall, for instance: `printf()` is **NOT** a system call. `printf()` does some string formatting before passing the the resulting string onto a `write()` system call.  

8. Do all **system calls** execute in kernel mode?  

> Yes

9. How are the functions in the **POSIX API** related to **system calls**?  

> The POSIX API provides a set of functions and constants that programmers can use to interact with the operating system. It provides a high-level abstraction and standardization, making it easier for developers to write a portable code, and it is built on top of system calls.  

10. Why would an application programmer prefer programming using an API than making system calls directly?  

> An API provides an abstraction of the low-level implementations with system calls with a much efficient implementation than a hand-written code. Hence, a programmer can produce a cleaner and maintainable code by using an API.  

11. Do all `stdio.h` functions make **one or more system calls** in their implementation? Why or why not?  

> No, for example: `printf()` alone does not directly make a system call. The output is buffered and the actual system call to write that data to the standard I/O console will occur when the buffer is full, `fflush()` is called, or the program exits normally.  

12. Does MS-DOS **create a new process** to run a user program? What happens to the shell when the user program is running and when it exits?  

> No. In MS-DOS, there is no created process. When the user chooses to run a program, the invoked user program overwrites the shell in the single memory space, but partially leaves the operating system kernel in memory. When it exists, the user program leaves the memory and the shell is reloaded back.  

13. At what point does FreeBSD **start the shell**? Is there just one kind of shell?  

> FreeBSD invokes the shell upon user login. The invoked shell could any UNIX-variant shell of the user's choice.  

14. How does a shell on FreeBSD **start a process**? What does the shell do when the process is executing?  

> The shell executes `fork()` to clone itself and create a process, and in the resulting shell clone calls `exec()` to load the program into process. The shell waits for the process to terminate or continues with the user's commands.  

15. What are the purposes of **system programs**?  

> System program is a layer of computer programs on top of system calls, for the purpose of:  
>
> - Convenience for program development and execution, and  
> - Defining most of the users' view of the operating system.  

16. What is the difference between **policy** and **mechanism**? What is the principle of separation between policy and mechanism?  

> Policy defines what needs to be done (the activities to perform).  
> Mechanism defines the steps on how to do it (the implementation details to enforce the policy).  
> \
> Principle of separation of policy and mechanism is a design principle to achieve flexibility. In other words, adopting a certain mechanism should not restrict existing policies. The idea behind this concept is to have the least amount of implementation changes if we decide to change the way a particular feature is used.  

17. MS-DOS has a simple structure consisting of BIOS and DOS device drivers, resident system program, and application program. What are the advantages and disadvantages of this minimal structure?  

> MS-DOS is a single-tasking OS with a simple structure:   
> - The shell is invoked when booting,   
> - The program is loaded into memory when invoked, overwriting all but the kernel,   
> - When exited, the shell is reloaded  
> \
> Advantages:  
> - Straight-forward and simple   
> - Uses minimal memory space  
> \
> Disadvantages:  
> - Unsafe (programs can reside in memory for as long as they like),  
> - Difficult to enhance, not maintainable

18. Do **system programs** in UNIX including shells, compilers, and interpreters run in kernel mode or user mode?  

> They run in user mode.  

19. Is traditional UNIX a **two-layer** or **N-layer** structure? What are its pros and cons?  

> The traditional UNIX is a two-layered structure or also called **monolithic structure**.  
> \
> Pros: A program crash in the user mode does not crash the operating system itself  
> Cons: Difficult to scale complexity and not maintainable  

20. In an N-layered OS structure, what layer **hardware**? User interface? What is the dependency between a lower and an upper layer?  

> The lowest layer, layer 0, is the hardware, while the highest layer, layer (N - 1), is the user interface.  
> The lower is independent of the upper layer, while the upper layer can use services only of the lower layers.  

21. What are the advantages of layered approach? What is a successful example? What are disadvantages compared to the 2-layer, tightly coupled structure?  

> The advantages of the layered approach:  
> - Better debugging experience  
> - Easy maintenance  
> \  
> One succesful example is the TCP/IP Protocol Stack (Application, Transport, Network, Link, and Physical layers)  
> \  
> The disadvantages of the layered approach:  
> - Less efficient, more overhead from layer-to-layer  
> - Difficulty of defining layers  

22. What is the key idea with **microkernels** compared to **monolithic** kernels?  

> Microkernels move as many functionalities to the user mode, and, therefore, reduces the probability of crashing in the kernel mode. 
> The functionalities moved to the user mode will communicate through message passing.  

23. Which of the following functions of a microkernel is done in kernel mode? In user mode?  

	- Network driver (User mode)  
	- Device driver (User mode)  
	- Graphic driver (User mode)  
	- Interprocess communication (Kernel mode)  
	- CPU scheduling (Kernel mode)  
	- Memory management (Kernel mode)  
	- File system (User mode)  
	- Application programming (User mode)  

24. How can a microkernel run an OS service in **user mode** while also **protecting** the rest of the system?  

> The OS services (file system, device drivers, etc.) run in user mode in their own separate address space. Thus, crashing does not affect any other processes. They are also running on a special user mode, the kernel defined-user program mode. In another word, the user cannot freely modify these processes. Furthermore, these services can communicate through inter-process communication (via the kernel mode).  

25. How does a modular OS divide its functionality? What are the advantages of this organization?  

> A modular OS partitions the services (or functionalities) into loadable kernel modules (LKM). The kernel of such OS will consist of the core component and an LKM interface (that supports loading and unloading the LKM-s).  
> \
> The advantages of such approaches are:  
> - Loading in modules as needed, no need for recompilation  
> - Lower overhead compared to message passing (requiring mode switch)  

26. What are **loadable kernel modules** (LKM)? Do they run in the same **address space** as the kernel or different?  

> Loadable kernel modules (LKM) are the binaries of an OS services that can be loaded into memory when needed. They, too, run in kernel mode in the same address space as the kernel.  

27. How would you characterize Linux and Solaris (monolithic, microkernel, combined LKM, or hardcoded services in the kernel)?  

> Linux and Solaris are hybrid systems of both monolithic and modular for dynamic loading.  

28. Is Darwin a monolithic or microkernel? What are the advantages of kexts in this context?  

>Darwin is a system with Mach microkernel and BSD Unix (POSIX). Darwin's kexts act like loadable kernel modules.  

29. What is the purpose of the BSD UNIX subsystem in Darwin?  

> The BSD (POSIX) UNIX subsystem is responsible for CLI, file system, and networking processes.  

30. Why does Android replace glibc with Bionic?  

> The glibc in Android is replaced by Bionic because it was much heavier than Bionic. Furthermore, Bionic bypasses the GNU Public License imposed on glibc.  

31. Since Android uses Linux kernel, does it mean it can also run executable programs for desktop and laptop LINUX? Why or why not?  

> No, most executable programs reside in the glibc (GNU C Library), which was replaced by Bionic. Hence, most of the executable programs that run in the desktop or laptop LINUX might not be compatible in Android.  

32. What is a **core dump** file? How is it different from a **log file**?  

> A core dump is a file consisting of a copy of the memory content created by the OS when a user program crashes.  
> A log file is a file consisting of error information.  

33. What is a **crash dump**? How is it different from a **core dump**?  

> A crash dump is a core dump created by the OS when the operating system itself crashes.  

## 2. EdSim51 and 8051 - Week 3  

1. What is the interrupt vector (address of ISR) of UART on 8051?  

> `0023H`  

2. To use UART interrupt on the 8051, why is it it necessary to lay out the code memory this way:  

	```asm
		ORG 0H
		JMP Main
		ORG  23H
		JMP Serial_ISR
	Main:
		...
	Serial_ISR:
		...
	```

> The code memory is laid out particularly that way since the interrupt vector of the UART interrupt begins at `23H`. `ORG 23H`specifies to the assembler to place the successive instructions (in this case, a jump instruction `JMP Serial_ISR`) in the code memory address `23H`.  

3. The UART uses Timer-1 to generate its timing.  What do the following bit registers do?
	a. `TR1`(starts running the timer for Timer 1)   
	b. `ET1`(enables timer interrupts from Timer 1)   
	c. `TF1` (interrupt signal from Timer 1 when it overflows)  
	
4. What is SDCC?  

> SDCC (Small Device C Compiler) is an open source, free, cross-platform compiler.  

5. What is the size (in terms of bits or bytes) of the following types in SDCC? and are they signed or unsigned?  
	a. `bit` (one bit, unsigned)  
	b. `char` (one byte, signed)  
	c. `int` (two bytes, signed)  
	d. `long` (four bytes, signed)  
	e. `float` (four bytes, signed)  
	

6. What does SDCC do if you invoke it with the following arguments?  
	a. `sdcc file.c` (compiles to assembly, assembles, links and produces a file in Intel hex executabe (`.ihx`))  
	b. `sdcc -S file.c` (compiles to assembly (`.asm`), but not assemble and link)  
	c. `sdcc -c file.c` (compiles to assembly and assembles, but not link, produces relocatable object file (`.rel`))  
	d. `sdcc file.rel -o file.ihx` (links `file.rel` and produces `file.ihx`)  
	
7. Why does `main` in `.c` file get translated into `_main` in the `.asm` file?  

> Compilers add an additional underscore in front of function names to avoid naming conflicts. Otherwise, the assemblers might mistake function names as an instruction or opcode.  

8. The `.asm` output from SDCC is different from Intel assembly syntax and therefore cannot be loaded directly into EdSim51 and run. So what file generated by SDCC (or related tools) in order to run on EdSim51?  

> The SDCC can produce `.ihx` or `.hex` files, which can be loaded in EdSim1.  
> \
> For `.ihx` files, another command `packihx main.ihx > main.hex` is needed before loading it into SDCC.  
> For `.hex` files, it can be immediately loaded into SDCC.  

9. In SDCC's `<8051.h>` header file, how is the GPIO port  `P1` declared so that it refers to the special-function register at memory address `90H`?  

> ```c
> __sfr __at (0x90) P1;
> ```

10. Why does SDCC require that you declare an ISR with the `__interrupt` keyword and a number such as `(4)` as in

	```c
	void Serial_ISR(void) __interrupt(4) {
	   ...
	}
	```

> The `__interrupt` keyword and the number `(4)` is an identifier for the compiler to refer it to the UART ISR.  
> By this, the compiler understands the semantics and use `reti` to return from the interrupt instead of the `ret` used in a normal function call.  
 
11. What is on the stack when an ISR is invoked?  

> The current state (including registers, etc.) of the current process will be saved by being pushed into the stack. When the ISR finishes, the state of the interrupted process will be restored by popping the saved registers in the stack.  

12. Why do we NOT recommend calling a function such as `DisplayLED(char num)` from within the ISR?  

> Both calling and returning from a function involves pushing and popping registers (that need to be saved) into the stack and thus may increase the duration of ISR. This is undesirable because some ISR are time-critical; ISR should be designed to be as short as possible.  

13. By observing SDCC's assembly output for the ISR that calls a function (slides 24 and 26), what is the purpose of all the `push` (`bits`, `acc`, `b`, `dpl`, `dph`, `0+7`, `0+6`, … `psw`) instructions and all the corresponding `pop` instructions before the `reti` instruction?

> These `push` and `pop` instructions are to save and restore the (possibly) used registers and special function registers (SFR) before and after proceeding with the ISR.  

14. What is the purpose of calling `main()` in the function definition  

	```c
	void _sdcc_gsinit_startup(void) { main(); }
	```

> The purpose of the function definition is to jump out of the reset ISR handler to `main` upon startup.  

15. What happens if you don't define the following routines to empty when compiling and linking with SDCC?  

	```c
	void _mcs51_genRAMCLEAR(void) {}
	void _mcs51_genXINIT(void) {}
	void _mcs51_genXRAMCLEAR(void) {}
	```

> The library versions of these functions be called and the memories of RAM, External Memory, and External Memory (if any is available) will be initialized to 0.  

16. What clock frequency should be used when running the UART at 4800 baud?  

> `11.0592` MHz

17. How do you define a lookup table in SDCC to put data into CODE memory for mapping digits (0-9) to the LED segment to light up?  

> ```asm
> LEDdata:	DB 0C0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H
> ```

18. On slide 21, the _sdcc_gsinit_startup() function contains inlined assembly code
	```
	__asm
	    mov sp, #0x57
	__endasm;
	```
	Can it be rewritten as C? How?

> ```c
> SP = 0x57;
> ```

## 3. Short Assembly Programs  

1. Try running the C program on slide 11. Make sure it compiles using the command on slide 15 and load the `.ihx` file into EdSim (with the load button)  

> Resulting Assembly code in EdSim51:  
> ```asm
> ORG 0000H
>	MOV 90H,#24H
>	RET
>	END
> ```

2. Try running the two-file example (`LEDtest0.c`, `LEDseg.c`) shown on slide 16, compile and link with the commands on the slide, and load into EdSi51 to run.  

> Resulting Assembly code in EdSim51:  
> ```asm
> ORG 0000H
>	MOV R7,#00H
>	CJNE R7,#0AH,00H
>	JNC 0CH
>	MOV 82H,R7
>	PUSH 07H
>	LCALL 001DH
>	POP 07H
>	INC R7
>	SJMP 0EFH
>	RET
>	MOV A,82H
>	MOV DPTR, #0024H
>	MOVC A,@A+DPTR
>	MOV 82H,A
>	RET
>	LCALL 0014H
>	MOV 90H,82H
>	RET
>	PUSH 0F9H
>	MUL AB
>	ANL C,/99H
>	MOV 82H,C
>	MOV R0,A
>	SJMP 90H
>	END
> ```

3.  Try running the Serial Echo example on slide 18.  

> Resulting Assembly code in EdSim51:  
> ```asm
> ORG 0000H
>	MOV 89H,#20H
>	MOV 8DH,#0FAH
>	MOV 98H,#50H
>	SETB 8EH
>	JNB 98H,0FDH
>	MOV R7,99H
>	CLR 98H
>	MOV 99H,R7
>	JBC 99H,0F4H
>	SJMP 0FBH
>	END
> ```

4. Try running rhe Polling UART example on slide 19.  

> Resulting Assembly code in EdSim51:  
> ```asm
> ORG 0000H
>	MOV 89H,#20H
>	MOV 8DH,#0FAH
>	MOV 98H,#50H
>	SETB 8EH
>	JNB 98H,0FDH
>	MOV R7,99H
>	CLR 98H
>	MOV A,R7
>	ADD A,#0D0H
>	MOV 82H,A
>	LCALL 0025H
>	SJMP 0EFH
>	MOV A,82H
> 	MOV DPTR, #002CH
>	MOVC A,@A+DPTR
>	MOV 82H,A
>	RET
>	LCALL 001CH
>	MOV 90H,82H
>	RET
>	PUSH 0F9H
>	MUL AB
>	ANL C,/99H
>	MOV 82H,C
>	MOV R0,A
>	SJMP 90H
>	END
> ```

5. Try running the intrLED.c example on slide 20. What is the difference between the use of `Main()` in previous examples and `main()` in this example?  

> Resulting Assembly code in EdSim51:  
> ```asm
> ORG 0000H
>	LJMP 0029H
>	RETI
> ORG 000BH
>	RETI
> ORG 0013H
>	RETI
> ORG 001BH
>	RETI
> ORG 0023H
>	LJMP 004EH
>	LJMP 0045H
>	MOV 81H,#20H
>	LCALL 00B9H
>	MOV A,82H
>	JZ 03H
>	LJMP 0026H
>	LJMP 0026H
>	MOV 89H,#20H
>	MOV 8DH,#0FAH
>	MOV 98H,#50H
>	SETB 8EH
>	RET
>	LCALL 0039H
>	SETB 0AFH
>	SETB 0ACH
>	SJMP 0FEH
>	PUSH 20H
>	PUSH 0E0H
>	PUSH 0F0H
>	PUSH 82H
>	PUSH 83H
>	PUSH 07H
>	PUSH 06H
>	PUSH 05H
>	PUSH 04H
>	PUSH 03H
>	PUSH 02H
>	PUSH 01H
>	PUSH 00H
>	PUSH 0D0H
>	MOV 0D0H,#00H
>	JBC 99H,02H
>	SJMP 00H
>	JNB 98H,0EH
>	MOV 08H,99H
>	CLR 98H
>	MOV A,08H
>	ADD A,#0D0H
>	MOV 82H,A
>	LCALL 00B2H
>	POP 0D0H
>	POP 00H
>	POP 01H
>	POP 02H
>	POP 03H
>	POP 04H
>	POP 05H
>	POP 06H
>	POP 07H
>	POP 83H
>	POP 82H
>	POP 0F0H
>	POP 0E0H
>	POP 20H
>	RETI
>	MOV 81H,#57H
>	LJMP 0045H
>	RET
>	RET
>	RET
>	MOV A,82H
>	MOV DPTR, #00BDH
>	MOVC A,@A+DPTR
>	MOV 82H,A
>	RET
>	LCALL 00A9H
>	MOV 90H,82H
>	RET
>	MOV 82H,#00H
>	RET
>	PUSH 0F9H
>	MUL AB
>	ANL C,/99H
>	MOV 82H,C
>	MOV R0,A
>	SJMP 90H
>	END
> ```
> \
> When using `main()` like in this example, we would need to override some of the library functions: 
> ```c
> void _mcs51_gsinit_startup(void);
> void _mcs51_genRAMCLEAR(void);
> void _mcs51_genXINIT(void);
> void _mcs51_genXRAMCLEAR(void);
> ```
