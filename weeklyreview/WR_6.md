# Weekly Review 6  

## 1. EdSim51 SDCC  

1. What is the difference between a subroutine and a function?  Which one is more complicated?  

> A subroutine is an ISA-supported call-return code fragment and it assumes a hardware-supported stack and a program counter. Meanwhile, a function is a compiler-supported wrapper around a subroutine and it involves saving and restoring registers, passing parameters, and auto local variables, assuming a stack, register set, and a program counter. A function is a high-level concept and is more complicated.  

2. What instruction can be used for calling a subroutine?  

> `LCALL` (for a longer distance) or `ACALL` (for much shorter distance) can both be used for calling a subroutine.  

3. What instruction is used for returning from a subroutine call?  

> `RET` (i.e. `PC = POP()`) is used for returning from a subroutine call. 

4. The subroutine-call instruction needs to specify the address of the subroutine to call, but the return instruction just returns without operand.  How does it know where to return to?  

> The `LCALL` or `ACALL` automatically pushes the return adddress (`PC` of the next instruction) into the stack. When returning, the `RET` instruction only needs to pop the address from the stack and assign the `PC` to the popped address.  

5. What is the power-on value of the stack pointer `SP`?  

> The initial value of `SP` upon power-on is `07H`.  

6. Which way does the 8051 stack grow?  That is, when you `PUSH`, does the processor increment or decrement the stack pointer?  

> The stack in 8051 grows upwards (in contrary to modern day architectures that has stack growing downwards). When executing `PUSH`, the processor increments the `SP` value.  

7. if `SP` is currently pointing to address `8H`, after a `PUSH` instruction, what address contains the newly pushed value, and what is the new value of `SP`?  

> The address `09H` contains the newly pushed value and the `SP` is now `09H`.  

8. if `SP` is currently pointing at address `9H`, what address is the `POP` value read from?  

> The assigned value is read from the address `09H` and the `SP` is now `08H`.  

9. Can the program counter (`PC`) be modified by a `MOV` instruction?  If not, what instruction (or sequence of instructions) can be used  

> No, the `PC` is an internal register and not a special function register (SFR), it cannot be modified through the `MOV` instruction.  

- to assign a constant address to the PC?  

> The `LCALL`, `ACALL`, or a combination of `PUSH` and `RET` can be used to assign a constant address to the PC.  

- to assign the PC a variable address in DPTR?  
	
> The following instruction can accomplish so:  
> ```asm
> push pdl
> push dph
> ret
> ```

10. Is 8051 a big-endian or little-endian architecture?  

> 8051 is a little-endian architecture.  
	
11. If you do an LCALL to target address `1234H`, and the SP is currently pointing at address `7H`, what are the new values at address `8H` and at address `9H` after the call, and what is the new value of `SP`?  

> The value of the address `8H` is the lower byte of the next instruction after `LCALL` and the value of the address `9H` is the upper byte of the next instruction after `LCALL`. The new value of `SP` is `09H`.  

12. What is the addressing mode accepted by `PUSH` and `POP` instructions on 8051?  

> `PUSH` and `POP` only accept direct addressing mode.  

13. Does 8051 allow `PUSH A` or `POP A`?  If not, how do you push a value from the accumulator to the stack or pop a value from the stack into the accumulator?  

> No, `A` is not the direct address of the accumulator. `PUSH ACC` and `POP ACC` can push and pop the accumulator into and out of the stack.  

14. Does 8051 allow `PUSH R2` or `POP R2`?  If not, how does SDCC generate code that pushes a value from register `R2` or pop a value into register `R2`?  

> `PUSH R2` and `POP R2` are illegal in 8051 because they are not the direct aaddresses of the Register 2. Instead, the SDCC generates `push ar2` and `pop ar2`, where `ar2` is the direct address of Register 2.  

15. Why does C compiler need to save registers before a function call and restore registers after a function return?  

> Because the C compiler assumes a calling convention where the registers were 'caller-save'. Hence, the compiler generates code to save for registers it needs after returning from the function call.  

16. What does `JC` instruction do?  

>`JC` is a jump instruction that occurs if carry flag is set to `1`.  

17. How does SDCC pass parameter to a function that expects  
- A single-byte parameter?   
	
> The single-byte parameter is passed through `DPL`.  

- Two single-byte parameters?  
	
> The two single-byte parameters is passed through `DPL` and `DPH`.  

- A single two-byte parameter?  
	
> The two-byte parameter is passed through the `DPTR`, the concatenation of `DPL` and `DPH`. The lower byte is placed in `DPL` and the upper byte is placed in `DPH`.  
	
18. How does SDCC return a value from a function:  
- a single byte return value?  
	
> Similarly, a single byte return value is passed through `DPL`.  

- a two-byte return value?  

> A two-byte return value is passed through `DPTR`, the concatenation  of `DPL` and `DPH`. The lower byte is placed in `DPL` and the upper byte is placed in `DPH`.  

## 2. Cooperative Threads  

19. Why is 8051 called a **Harvard Architecture**?  

> 8051 is called the Harvard Architecture because it has separate memory for code (or program) and data.  

20. What defines the context of a thread on an 8051?  

> The context of a thread is defined by its own registers and special-function registers (SFR), its own stack pointer and stack space (allocated in the heap memory of its process), and its own program counter value.  

21. What does this C declaration do?  
```c
typedef void (*FunctionPtr)(void);
```

> The C declaration declares `FunctionPtr` as a data type for a function pointer that takes nothing (void) as an argument and returns nothing (void).  

22. In the `testcoop.c` file, what does this code do:
```c
void _sdcc_gsinit_startup(void) {
    __asm
            ljmp  _Bootstrap
    __endasm;
}
```
	
> The `_sdcc_gsinit_startup` function jumps to the `_Bootstrap` subroutine upon power-on.  

23. Why is the C function `Bootstrap` named `_Bootstrap` in assembly (i.e., prepended with an underscore)?  

> This is a common approach taken by some compilers to help prevent accidental usage and symbol clashes.  

24. In the Producer-Consumer example, what are the different ways threads can be created to run the Producer and Consumer functions?

> 1. Three threads (`main`, `producer`, and `consumer`) can be used, but the thread for `main` is unused.  
> 2. Two threads (`producer` and `main` (`consumer`) or `consumer` and `main`(`producer`)) can be used.  

25. In the memory allocation scheme for cooperative threads, what is the **address range of the stack** for Thread 0? Thread 1? Thread 2?  Thread 3?  

> Thread 0: `40H` to `4FH`  
> Thread 1: `50H` to `5FH`  
> Thread 2: `60H` to `6FH`  
> Thread 3: `70H` to `7FH`  

26. Register banks  
- Which bits in which register do you set to select the register bank?  
	
> The bits `3` and `4` of the `PSW` special function register is used to set the register bank select.  

- When `<RS1:RS0> = 2` (i.e., `PSW<4:3> = 2`), which RAM addresses get mapped to registers `R0` - `R7`?  
	
> `R0` = `10H`  
> `R1` = `11H`  
> `R2` = `12H`  
> `R3` = `13H`  
> `R4` = `14H`  
> `R5` = `15H`  
> `R6` = `16H`  
> `R7` = `17H`  

27. What are the purposes of the macros  
- `SAVESTATE`?  
	
> The `SAVESTATE` macro is used to push `ACC`, `B`, `DPTR`, `PSW` onto the stack and save `SP` for the current thread.  

- `RESTORESTATE`?   
	
> The `RESTORESTATE` macro does the reverse of `SAVESTATE`. It is used pop `ACC`, `B`, `DPTR`, `PSW` out of the stack and restore `SP` for the current thread.  

- Is it necessary to push the registers `R0` - `R7` onto the stack during `SAVESTATE` and pop them back into `R7` - `R0` during `RESTORESTATE`?  

> There is no need to push the registers `R0` - `R7` onto the stack because every thread has an independent memory addresses for registers `R0` - `R7` assigned by the bits `4:3` of the `PSW` (whcih is already saved in `SAVESTATE`). Hence, the contents of the registers would remain untouched after switching threads.  

28. Memory for variables  
- What region of memory is available for use by the thread manager and application program as global variables after the register banks and stacks have been allocated?  
	
> The addresses `20H` to `3FH` are available to be used as global variables after all register banks (`00H` - `07H`, `08H` - `0FH`, `11H` - `17H`, and `18H` - `1FH`) and stacks (`40H` - `4FH`, `50H` - `5FH`, `60H` - `6FH`, and `70H` - `7FH`) have been allocated.  

- What is the purpose of the **thread bitmap**, which is a (global) variable maintained by the thread manager?  
	
> Thread bitmap is a bitmask to identify which thread is active.  

29. What are the four major steps of the Bootstrap routine?  

> 1. Initialize thread manager variables (set thread bitmap to `0`)  
> 2. Create thread for `main` (deposit initial variable register values to stack, set thread bitmap to `1`, and save Thread 0 `SP`)  
> 3. Set current thread ID (global variable) to `0`  
> 4. Restore the state of Thread 0  by calling the macro `RESTORESTATE`  

30. Bootstrapping  
- (Slide Page 27) How should `Bootstrap` initialize the thread bitmap?  
	
> By setting the bits at addresses`20H` - `23H` to `0`.  

- (Slide Page 28) When `Bootstrap` calls `ThreadCreate(main)` to create the context for main, **which stack** is used, and what is the **content of that stack** when `ThreadCreate` is first entered?  How is the parameter passed and what does it mean?   

> The stack used is the initial stack at address `08H` - `0FH`. Upon calling `ThreadCreate(main)`, the return address (of the step 3 of the `Bootstrap` function) is pushed into the stack. The passed parameter is the two-byte address of `main` function, it is passed to the `ThreadCreate` function by the `DPTR`, with the lower byte stored in `DPL` and the upper byte stored in `DPH`.  

- Does `ThreadCreate()` modify the current thread ID?  

> No, the `ThreadCreate` does not modify the thread ID. However, it returns the thread ID of the new thread it created.  

- (Slide Page 32) How does `Bootstrap()` start running the `main()` function whose context has been set up by `ThreadCreate(main)`?  

> Since the address of `main` has already been deposited to the stack upon running `ThreadCreate(main)`. the `RESTORESTATE` macro will perform `RET` on the deposited address `main`, which eventually results in a jump to the `main()` function.  

- After `Bootstrap` starts running `main`'s thread, what happens to the **initial stack** that `Bootstrap` used (from part b of this question)?  
	
> The initial stack on the address `08H` - `0FH` will be unused, and will be trashed when Thread 2 is created.  
	

31. Thread creation  
- If you can assume all threads must explicitly call `ThreadExit()` if they ever exit (and never implicitly call `ThreadExit()` when the function finishes), to create the new Thread 0's context that can be restored to run `main` from the beginning, how should the `ThreadCreate()` function initialize the content of Stack 0 (and set its `SP` value) and why?  
	
> 1. Deposit the return address of the caller function  
> 2. Deposit the starting address of `main` function  
> 3. Deposit the intial values of `ACC`, `B`, `DPTR`, and `PSW`  
> 4. Save the value of Thread 0's `SP` to the starting address of where `PSW` is stored  
> 5. Set the thread bitmap to activate Thread 0  
> 6. Return to the caller function with thread ID `0` in `DPL`  
>
> \
> We deposit the return address of the caller function before the starting address of the `main` function. Hence, the return address of the caller function will be on the top of the stack when Thread 0 calls `ThreadExit()`.  

- How should `ThreadCreate()` initialize a thread's stack content before `RESTORESTATE` in order to support implicit call to `ThreadExit()` upon function return?  
	
> 1. Deposit the return address of the caller function  
> 2. Deposit the starting address of `ThreadExit`  
> 3. Deposit the starting address of `main` function  
> 4. Deposit the intial values of `ACC`, `B`, `DPTR`, and `PSW`  
> 5. Save the value of Thread 0's `SP` to the starting address of where `PSW` is stored  
> 6. Set the thread bitmap to activate Thread 0  
> 7. Return to the caller function with thread ID `0` in `DPL`  
>
> \
> Similarly, we deposit the starting address of the `ThreadExit` before the starting address of the `main` function and after the return address of the caller function. Hence, the starting address of the `ThreadExit` will be on the top of the stack when Thread 0 calls `RET`.  

32. (Slide Page 33) When `main()` calls `ThreadCreate(Producer)`, 
- Which stack does main use to make this call?  

>Stack 1 is used to make this call.  

- what is that stack's content upon entering the `ThreadCreate` function, assuming we do not need to support implicit `ThreadExit` (and therefore need not push `ThreadExit`'s address upon `ThreadCreate`)?  

> Stack 1 has the address of the second step of the `main` function.  

33. (Slide Page 34) By the time `main()` returns from `ThreadCreate(Producer)`, which returns the thread ID of 1 for the newly created thread,
- What is on Stack 0?  

> Nothing is in Stack 0.  

- What is on Stack 1? and what is its `savedSP` value?  

> Stack 1 contains the starting address of `Producer` function and the initial values of `ACC`, `B`, `DPTR`, and `PSW`, respectively. The value of Thread 1's `savedSP` value is `46H, 56H, 00H, 00H`.  

- What is the value of `SP`?  

> `SP` is `3FH`.  

- What is the value of `DPL` and why?  

> `DPL` is `1` since `ThreadCreate` returns the thread ID of the newly created thread.  

- Stack 1 contains value `08H` at address `56H`, which is intended to be restored into `PSW` when thread 1 resumes.  Why value `08H`?  

> `08H` is `0000 1000` in binary. The bits `4:3` of the `PSW` is the register bank select and `01` translates to the register bank select for Thread 1.  

34. Why should `main()` call `Consumer()` instead of creating another thread to run `Consumer`?  

> It saves the effort of creating another thread since the thread for `main` does not perform any useful computation if each `Producer` and `Consumer` has its own thread.  

35. (Slide Page 35) When `main()` calls `Consumer()`, what is the content of the stack upon entering `Consumer`?  

> Stack 0 (the stack of Thread 0 for `main`) contains the adddress of step 3 of `main`.  

36. (Slide Page 36) When `Consumer()` calls `ThreadYield()`, what is the content of the stack upon entering `ThreadYield()`?  

> Stack 0 (the stack of Thread 0 for `main`) contains the address of step 2 of `Consumer`.  

37. (Slide Page 37) What are the three major steps in `ThreadYield()?` 

> 1. Save the state of the current thread by calling the `SAVESTATE` macro  
> 2. Select the next active thread to run  
> 3. Restore the state of selected thread by calling the `RESTORESTAATE` macro  

38. What does the Thread 0's stack look like after `ThreadYield()` calls `SAVESTATE`?  

> Stack 0 contains the address of step 3 of `main`, the address of step 2 of `Consumer`, and the values of `ACC`, `B`, `DPTR`, and `PSW`, respectively.  

39. When `ThreadYield()` is picking the next thread  to context switch to,
- What **data structure** does it check to know what threads are available to choose from?  

>The ThreadYield checks for the next available thread from the bitmask in the thread bitmap.  

- What **stack** is it running on during choosing the next thread?  

> The previous stack remains used when selecting the next thread.  

- What happens if an **interrupt** happens during this time?  Can an interrupt cause any problems?  

> Yes, an interrupt will require the operating to save the current state (registers, PC, and special function registers). In this case, it will overflow Stack 0 because the values are already filled up to `48H` and will overwrite the contents for Stack 1.  

40. (Slide Page 39 - 40) How does the `SP` change from the time `ThreadYield()` **just before** `RESTORESTATE` to **just after** `RESTORESTATE`?  

> The value of `SP` was initially `43H` (starting address of `PSW` in Stack 0) just before calling `RESTORESTATE`, and it changes to `4FH` (the starting address of Stack 1) after `RET` is called (to invoke `Producer`) in `RESTORESTATE`.  

41. (Slide Page 40) After `ThreadYield()` does `RESTORESTATE`, where and how does it "continue" running the thread it is restoring?  

> Since `RET` is called in `RESTORESTATE` to the starting address of `Producer`, the processor continues running from the beginning of `Producer`.   
