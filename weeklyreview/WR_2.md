# Weekly Review 2

## 1. Definitions and Short Answers  - Week 2  

1. What is the **kernel** part of the OS?  

> The kernel part of an operating system is the core component that resides in the memory from startup to shutdown, and manages to core functionality of an OS (manages operations of memory, CPU time, I/O, etc.)  

2. What is a **system program**?  

> A system program is a software program that communicates and coordinates the activities and functions of hardware and software of a system, and also controls the operations of the hardware. System programs resides in a layer of programs above system calls, for the purpose of convenient for program development and execution. They include programs that are related to file management, command line interface, device drivers, programming language support, program loading and execution, and communications. For example: shell, loader, backup, device drivers, etc.   

3. Is a **web browser** part of an OS? Is it part of the kernel? part of system programs?  

> A web browser is not part of the OS. It can be considered as a middleware or an application program.  

4. **Middleware** is a set of software frameworks that provide additional services to what kind of users? What should be some example features?  

>A middleware is software and cloud services that provide common services and capabilities to applications and help developers and operators buld and deploy applications more efficiently.  
>\
> For example, many middlewares provide database, multimedia, cloud drive, and location services. Their services are commonly accessed through APIs.  

5. As a resource manager, what kinds of resources does an OS manage?  

> The operating system manages the CPU time, storage space, and the use of I/O devices.

6. What does an **API** stands for? What kinds of API does an OS provide?  

> API stands for application programming interface. The operating system mainly provides APIs to memory usage, I/O devices, file storage, and communication (TCP/IP connection).  

7. What is a **bootloader**? How is it related to an OS?  

> A bootloader is the initial program in CPU firmware that partially loads the OS kernel into the memory such that the kernel can eventually loads itself.  

8. How does a bootloader load an OS?  

> A bootloader, with access to device driver for storage of OS (disk, flash), copies the image of OS from storage into the memory. When the OS kernel is sufficient, the bootloader jumps to the starting point of OS, where it continues to load the remaining part of the OS.  

9. How does a CPU **send a command** to a device controller?  

> The CPU can send a command to the device controller by accessing, reading, and writing into the registers inside a device controller through a bus.  

10. From page 7 of the textbook, a **device controller** maintains some **local buffer storage** and a set of **special-purpose registers**. Where do these storage and registers reside? Are they on the CPU, main memory, cache, or outside of the CPU?  

> These registers reside in the device controller and outside of the CPU. Although so, the CPU can access, read, and write into these registers through a bus. Moreover, the device controller itself can also modify their values.  

11. What is a **device driver**? Is it hardware of software? Is it part of the OS or in an application program? What does it do?  

> A device driver is a system software part of the OS that communicates with the device controllers.  

12. What does **IRQ** stand for, and what is its purpose?  

> IRQ stands for interrupt request. An interrupt request (IRQ) is a signal sent by a device controller to notify the CPU.  

13. How does a program for 8051 know when the UART has received a byte?  

> A program can do this by checking whether the register `RI` of the UART has been set to `1`. If it is true, then the UART has received a byte.  

14. What does **ISR** stand for, and when is it invoked?  

> ISR stands for interrupt service routine. An interrupt service routine (ISR) is subroutine invoked by an interrupt request from a hardware device.  

15. What is an **interrupt vector**?  

> An interrupt vector is an address of an interrupt service routine (ISR).  

16. What is an **interrupt vector table**?  

> An interrupt vector table is an array data structure of interrupt vectors.  

17. How does a processor decide which ISR to execute when there are multiple I/O devices?  

> The processor identifies the ISR with the interrupt number, which is uniquely associated with a hardware source of ISR.  

18. How does a processor cotinue executing the user program after an ISR finishes?  

> Before transferring control to ISR through interrupt vector, the processor saves the state of the interrupted routine (address, register states, etc.). After finishing the execution of an ISR, the processor can simply recover these saved states.  

19. What is a **nested interrupt**?  

> A nested interrupt is an instance of handling interrupt in the middle of handling an interrupt.  

20. What is **interrupt chaining** from page 10 in the textbook? Why is it useful?  

> In practice, some computers have more devices than the address elements in the interrupt vector. Interrupt chaining swaps the address elements with the starting address of a link list data structure. When an interrupt is raised, the handlers on the corresponding list are called sequentially until one is found to service the request. It is a compromise between the overhead of a huge interrupt vector table and the inefficiency of dispatching to a single interrupt handler.  

21. How does the OS protect CPU time as a resource by preventing a user program from hogging the CPU without making a system call?  

> The OS protects the CPU time by utilizing timer to periodically invoke a timer interrupt to give the OS control, preventing a user program from hogging the CPU without making a system call.  

22. What are **volatile memory** and **nonvolatile memory**? What are examples of each kind?  

> Volatile memory is a memory that loses its contents upon power off. Examples include SRAM and DRAM.
> \
> Nonvolatile memory is a memory that retains its content even after power off. Examples include Flash memory, disks, and tapes.  

23. What is the purpose of a **cache**? Can a processor run without a cache?  

> Cache is a memory that contains a subset image of the contents in the main memory. A processor can run without a cache.  

24. What is **the principle of locality**? What are two kinds of locality?  

> The principle of locality is the tendency of a processor to access same set of memory locations with repetitively over a short period of time. This includes temporal locality and spatial locality.  
> \
> Temporal locality refers to the repeated use of specific data and/or resources within a relatively small duration of time.  
> \
> Spatial locality refers to the use of data elements within relatively close storage locations.  

25. What does **DMA** stand for, and why is it used?  

> DMA stands for direct memory access. Direct memory access is a technique used to allow device controller to transfer blocks of data from buffer storage to the main memory without CPU intervention, freeing the CPU from the overhead of copying data between the device and memory.  

26. What are steps in a DMA setup, transfer, and completion?  

> - Set up buffers, pointers, and counters for the I/O device.  
> - Device controller transfer an entire block (commonly 512 bytes) from the device buffer storage to the main memory, without the intervention of OS.  
> - One interrupt is generated per block upon completion
 
## 2. EdSim51 and 8051 - Week 2

27. What are the **direct addresses** of the 8051 general-purpose I/O (GPIO) ports `P0`, `P1`, `P2`, and `P3`?  

> The GPIO in 8051 are `P0`, `P1`, `P2`, and `P3` with direct addresses `80H`, `90H`, `A0H`, and `BOH`, respectively.  

28. What is the meaning of each of the following instructions in 8051?  

	- `MOV A, #1`  
	
	> The equivalent to the C operation of `A = 1;`  
	
	- `MOV A, 1`  
	
	> The equivalent to the C operation of `A = *((char*) 0x1);`  
	
	- `MOV A, R1`  
	
	> The equivalent to the C operation of `A = R1`  
	
	- `MOV A, @R1`  
	
	> The equivalent to the C operation of `A = *R1`  
	
	- `MOV R1, A`  
	
	> The equivalent to the C operation of `R1 = A;`  
	
	- `MOV R1, #1`  
	
	> The equivalent to the C operation of `R1 = 1;`  
	
	- `MOV R1, 34H`  
	
	> The equivalent to the C operation of `R1 = *((char*) 0x34);`  
	
	- `MOV @R1, A`  
	
	> The equivalent to the C operation of `*R1 = A;`  
	
	- `MOV @R1, #1`  
	
	> The equivalent to the C operation of `*R1 = 1;`  
	
	- `MOV @R1, 34H`  
	
	> The equivalent to the C operation of `*R1 = *((char*) 0x34);`  
	
	- `MOV 34H, A`  
	
	> The equivalent to the C operation of `*((char*) 0x34) = A;`  
	
	- `MOV 34H, #56H`  
	
	> The equivalent to the C operation of `*((char*) 0x34) = 0x56;`  
	
	- `MOV 34H, 56H`  
	
	> The equivalent to the C operation of `*((char*) 0x34) = *((char*) 0x56);`  

	- `MOV 34H, R1`  
	
	> The equivalent to the C operation of `*((char*) 0x34) = R1;`  
	
	- `MOV 34H, @R1`  
	
	> The equivalent to the C operation of `*((char*) 0x34) = *R1;`  

29. Are the following allowed? If not, what assembly code does the intended operation, if any?  

- `MOV R1, R2`  

> Not allowed.  
> ```asm
> MOV A, R1
> MOV R2, A
> ```

- `MOV A, A`  

> Not allowed. This is a useless operation.  

- `MOV #20, R3`  

> Not allowed. L-operand is an immediate.  

30. What is a **port latch**?  

> A port latch is a memory location that stores the logic level of an output pin. A buffer is used for input from the same pin.  

31. What does it mean that 8051 GPIO ports are **bit-addressable**?  

> In 8051, GPIO ports allow the eight bits inside a byte to be manipulated using operations in Assembly.  

32. What is the Intel Assembly notation for 'bit 3 of port P2'?  

> `P2.3`

33. What is the meaning of  

	```asm
	SETB P1.1
	CLR P2.3
	```
	and why cannot the same effect be achieved using a `MOV` instruction?  
	
> The series of instruction sets the first bit of P1 to `1` and the second bit of P2 to `3`. The same result cannot be achieved with `MOV` because it overwrites the existing values inside the port latch. On the other hand, the given series of instructions maintains the original values and modify only the bits in the operand.  

34. If you want to set individual bits of a GPIO port without using `SETB` and `CLR` instructions, what instruction can you use? (Hint) 8051 User's Guide. Table 3 on Page 1-11. What **addresing modes** should be used with these instructions? Use these instructions to implement the two bit set/clear instructions.  

> We can use `ANL`, `ORL`, `XRL` instructions to achieve this.  
> ```asm
> ;; 0b0000 0001 = 0x1
> ;; 0b0000 0010 = 0x2
> ;; 0b0000 0100 = 0x4
> ;; 0b0000 1000 = 0x8
> ;; 0b0001 0000 = 0x16
> ;; 0b0010 0000 = 0x32
> ;; 0b0100 0000 = 0x64
> ;; 0b1000 0000 = 0x128
> ;; 0b1111 1110 = 0xFE
> ;; 0b1111 1101 = 0xFD
> ;; 0b1111 1011 = 0xFB
> ;; 0b1111 0111 = 0xF7
> ;; 0b1110 1111 = 0xEF
> ;; 0b1101 1111 = 0xDF
> ;; 0b1011 1111 = 0xBF
> ;; 0b0111 1111 = 0x7F
> 
> ;; SETB Instruction Alternative
> ;; To set GPIO P1 on the lowest bit:
> ORL P1, #1H
> 
> ;; CLR Instruction Alternative
> ;; To clear GPIO P1 on the lowest bit:
> ORL P1, #0FEH
> ```
> \
> `ANL`, `ORL`, `XRL` `A`, (`Ri` or `@Ri` or `#imm` or `dir`)  
> `ANL`, `ORL`, `XRL` `dir`, (`A` or `#imm`)  

35. What is a **label** in an assembly language program?  

> A label is a symbol that represents a memory address of an instruction or data. The address given by a label is calculated during assembly.  

36. Given the sample program for setting `P3<4:3>`:  

	```asm
	Top:		SETB 	P3.4
				SETB 	P3.3
				MOV 	P1, #24H
				CLR 		P3.3
				MOV		P1, #24H
				CLR 		P3.4
				SETB 	P3.3
				MOV 	P1, #24H
				CLR 		P3.3
				MOV		P1, #24H
				SJMP	Top
	```

- Rewrite it in C.  

> ```C
> for(int i = 0; i < 4; ++i)
> {
> 		P3 = (P3 & 0xE7) | ((3 ^ i) << 3);
> 		P1 = 0x24;
> }
> ```

37. What does the following Intel 8051 assembly code do?  
	```asm
	Data1:	DB	"Hello World"
	```
	
- Does it occupy any memory? If it does, which space does it occupy?  

> It occupies the Instruction Memory (CODE).  

- What is the closest equivalent statement in C?  

> ```c
> const char Data1[] = "Hello World";
> ```

- Is the assembly version null-terminated?  

> It is not null-terminated.  

38. Given the Intel 8051 assembly code:  
	```asm
	Data2:	DB	25
	```

- How many bytes does `Data2` occupy?  

> It occupies one byte. The C equivalent is:  
> ```C
> const byte Data2[1] = {25};
> ```

- What kind of address is `Data2`? In other words, which space does it occupy and how many bytes are required?  

> It occupies one byte in the Instruction Memory (CODE).  

39. Given the Intel 8051 assembly code  

	```asm
	COUNT EQU 25
	```

- How many bytes does the code occupy in the assembled code, if any and in which memory?  

> It does not occupy any bytes.  

- What is the equivalent statement in C?  

> ```C
> #define COUNT 25
> ```


40. If you want to display the digit `7` on the seven-segment LED with the additional vertical line on the upper left instead of just an upside-down L, what value do you write to `P1`?  

> We will need to input the value `0b1101 1000 = 0xB8` into `P1`. Hence,  
> ```asm
> MOV P1, #0B8H
> ```

41. What is the advantage of using `CLR A` instruction over `MOV A, #0` instruction, which does exactly the same thing (assigning `A` = 0)? (Hint) look up how these instructions are encoded.  

> `CLR A` is encoded in one byte, while `MOV A, #0` is encoded in two bytes.  

42. What is the difference between `A` and `ACC` in 8051 assembly? Why is `PUSH ACC` legal, but `PUSH A` is not? (Similarly, `POP ACC` is legal, but `POP A` is not)  

> In 8051 Assembly language, `A` is the implied address of accumulator whereas `ACC` is the direct address of the accumulator.  
> \
> When an address is implied, it is embedded in the opcode of an instruction. For example, `MOV A, @R0` requires only one byte of object code. It is an instruction in which both the source and the destination are implied.  
> \
> On the other hand, `MOV B, @R0` requires two bytes, the destination `B` is simply a direct address just like any other address in internal RAM.  
> \
> `PUSH` and `POP` have only one addressing mode: direct. Hence, it is necessary to provide a direct address of the accumulator (`ACC`).  

43. What is the effect `PUSH` and `POP` on the stack? Explain in terms of the stack, i.e. `SP` and the memory location pointed by `SP`.  

> `PUSH`:  
> The `SP` is increased by one first and then the content of given register or memory will be stored on the stack memory location pointed by `SP`.  
> \
> `POP`:  
> The data is retrieved and written into the given register or memory, then the `SP` is decreased by one.  

44. What does `LCALL Display` do (where `Display` is a code label)? Explain in terms of the program counter `PC` and the stack.

> Upon executing `LCALL Display`, the next `PC` (current `PC` + 3) is pushed into the stack. Subsequently, the `PC` jumps to the code memory location to where the label `Display` is pointing. 

45. What does the `RET` instruction do? Does `RET` know if the subroutine was originally called by `LCALL` or `ACALL` instruction?  

> `RET` is used to return from a subroutine, generally following an `ACALL` or `LCALL`. It pops the high- and low- order bytes of the `PC` successively from the stack, decrementing `SP` by 2. Program executing continues at the popped address. `RET` will not know whether the original subroutine was called by `LCALL` or `ACALL`; it only sees an address in the stack.  

46. Assume `LEDdata` corresponds to address `0x2468`, what is the new value of `DPL` and `DPH`. Explain what the following instruction does:

	```asm
	MOV 	DPTR, #LEDdata
	```

>  The instruction loads in the code memory address pointed by the label `LEDdata` into `DPTR`. The resulting `DPH` and `DPL` are `0x24` and `0x68`, respectively.  

47. What is the meaning of the instruction 1, and describe the difference between the first and second instruction.  

	Instruction 1:
	```asm
	MOVC	A, @A+DPTR
	```
	
	Instruction 2:
	```asm
	MOV		A, @Ri
	```
	where `Ri` is either `R0` or `R1`?  
	
> Instruction 1 loads in the value of `DPTR[A]` from the code memory into `A`.  
> Instruction 2 loads in the value of `((char*)Ri)[0]` from the data memory into A.  

48. On a UART, what does `RxD` stand for? Similarly, what is `TxD`?  

> `RxD` and `TxD` stand for received data and transmitted data, respectively.  

49. How should `RxD` and `TxD` signals of one system be connected to the `RxD` and `TxD` signals of another system that it communicated with?  

> The signal wire of `RxD` of one system must be connected to the signal wire of the `TxD` of the other system, and vice-versa.  

50. On the 8051, what is the purpose of the `SBUF` special-function register? What happens when you move data to `SBUF`? Similarly, what happens if you move data from `SBUF`?  

> `SBUF` is a register that acts as a buffer for sending and receiving data through the UART. When a data is moved to `SBUF`, the data is put to be transmitted through `TxD`. On the other hand, when a data is moved from `SBUF`, the data is received through `RxD`.  

51. How does a program know when there is valid data to be read from `SBUF`?  

> A program can check whether the `RI` (receive ready) flag is set to `1`.  

52. Why is it necessary to clear `RI` but after reading from `SBUF`?  

> Definitely, the calling convention states that flags from UART interrupts must be manually cleared. Otherwise, the `RI` flag can be misinterpreted in the future.  

53. What is the meaning of the code? Rewrite this assembly code as a C statement.  

	```asm
	Here: JNB RI, Here
	```

> The code loops in the current instruction until `RI` is set to `1`.  
> It is the equivalent of the C code  
> ```C
>	while(!RI);
> // the statements for Here begins here.
> ```

54. What does **4800 baud** mean for a UART?  

> Baud rate is the rate at which signal units are transferred in the UART. Hence, 4800 baud means 4800 signals are transferred at each second.  

55. On the 8051, what is the **interrupt vector** (or the address of the ISR) for Reset?  

> `0x0000`

56. The interrupt vector for interrupt is at `03H`, leaving only 3 bytes for the interrupt vector for Reset. Why is 3 bytes sufficient?  

> A jump instruction is encoded in 2 or 3 bytes. Thus, 3 bytes are enough to accommodate a jump instruction to `_main`.  

57. The interrupt vector after `03H` is `0BH`, leaving only 8 bytes for the INT0. Why is 8 bytes sufficient?  

> If possible, the handler code can completed in less than or equals to 8 bytes. Otherwise, a jump instruction can always placed in the 8 bytes memory space.  

58. When is the `TI` flag set to `1` by the UART?  

> The `TI` flag is set to `1` when the UART is ready to transmit the next byte. Likewise, the `RI` flag is set to `1` when the UART hs successively received a byte.  

59. When the UART's ISR is invoked, is it because by `RI` or `TI` set to `1`? Can it be both?  

> The UART's ISR is invoked whenever the `RI` or `TI` or both are set to `1`.  

60. What is the purpose of the `EA` bit, which stands for 'enable all (interrupts)'?  
 
> If `EA` is reset to `0`, no interrupt will be acknowledged. Whereas, if `EA` is set to `1`, the interrupts can be enabled individually:  
> - `ET2` enables/disables Timer 2 overflow interrupt  
> - `ES` enables/disables Serial Port (UART) interrupt  
> - `ET1` enables/disables Timer 1 overflow interrupt  
> - `EX1` enables/disables External interrupt 1   
> - `ET0`enables/disables Timer 0 overflow interrupt   
> - `EX0`enables/disables External interrupt 0  

## 3. Short Assembly Programs

1. Modify the Display subroutine so that it not only displays the digit but also switches to the next 7-segment LED. It just needs to a different digit at a time; does not need to keep all four.  

	```asm
		ORG 0H
	
			MOV R0, #0H
	Top:	SETB P3.4
			SETB P3.3
			LCALL Update
			LCALL Display
			CLR  P3.3
			LCALL Update
			LCALL Display
			SETB P3.3
			CLR  P3.4
			LCALL Update
			LCALL Display
			CLR  P3.3
			LCALL Update
			LCALL Display
			SJMP Top
	
	Update:	MOV B, #10
			MOV A, R0
			ADD A, #1
			DIV AB
			MOV R0, B
			RET
			
	Display:MOV A, R0
			MOV DPTR, #LEDdata
			MOVC A, @A+DPTR	
			MOV P1, A	
			RET
	
	LEDdata: DB 0c0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H
	```
2. Convert your code to interrupt version, shown on slide 26 and 27.  

	```asm
			ORG 0H
			JMP Main
			ORG 23H
			JMP Serial_ISR
	
	Main:LCALL InitUart
			SETB ES
			SETB EA
			MOV R0, #0H
	Top:	SETB P3.4
			SETB P3.3
			LCALL Update
			LCALL Display
			CLR  P3.3
			LCALL Update
			LCALL Display
			SETB P3.3
			CLR  P3.4
			LCALL Update
			LCALL Display
			CLR  P3.3
			LCALL Update
			LCALL Display
			SJMP Top
	
	Update:	MOV B, #10
			MOV A, R0
			ADD A, #1
			DIV AB
			MOV R0, B
			RET
			
	Display:MOV A, R0
			MOV DPTR, #LEDdata
			MOVC A, @A+DPTR	
			MOV P1, A	
			RET
	
	Serial_ISR:	JNB TI, Check_RI
			CLR TI
			
	Check_RI:	JNB RI, Serial_D
			MOV A, SBUF
			CLR RI
			ADD A, #-48
			MOV R0, A
			LCALL DISPLAY
			
	Serial_D:	RETI
	
	InitUart:	MOV TMOD, #20H
			MOV TH1, #-6
			MOV SCON, #50H
			SETB TR1
			RET
	
	LEDdata: DB 0c0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H
	```