# CS3423 Operating Systems

This repository contains CS3423 Operating Systems coursework, encompassing:
- ***Weekly Review***: Weekly review questions covering topics taught in lectures, along with additional programming tasks.
- ***Project Checkpoints***: Step-by-step final project checkpoints implementing a threads package and interacting with peripheral devices on the EdSim51 simulator, including a Dinosaur game.
- ***Dinosaur Game on EdSim51***: A dinosaur game playable by pressing on the keypad.

## **Requirements**
- EdSim51 Simulator (available for free at [edsim51.com](http://edsim51.com/))
- SDCC for EdSim51 (available for free at [sdcc.sourceforge.net](http://sdcc.sourceforge.net))

## **Weekly Review**
Weekly review questions on topics covered in lectures, along with additional programming tasks in languages such as C and Python. Answers to these questions are compiled into Markdown files provided in the `weeklyreview/` directory. The write-up solutions are not guaranteed to be correct; use them at your own risk.

## **Project Checkpoints**
- `checkpoint1/` implements a single-buffer producer-consumer problem with a cooperative threads package where threads yield CPU control to other threads.
- `checkpoint2/` implements a single-buffer producer-consumer problem with a preemptive threads package where threads are interrupted by timer interrupts and context switched to other threads.
- `checkpoint3/` implements a 3-deep buffer producer-consumer problem with a preemptive threads package, along with a semaphore for synchrony.
- `checkpoint4/` implements a 3-deep buffer producer-consumer problem with two producers and one consumer on a preemptive threads package using a ping-pong thread scheduler for fairness.
- `checkpoint5/` implements a 3-deep buffer producer-consumer problem with two producers being keypad and button bank devices, and a Dinosaur game playable by the keypad device, all on a preemptive threads package.

## **Usage**
To run the program, ensure you meet all the listed requirements.
1. `make clean` to remove old files.
2. In the checkpoint directory, `make all` to generate a `.hex` file.
3. Load the `.hex` file into EdSim51.
4. Assemble the `.hex` file by tapping the `Assm` button.
5. Run the program by tapping the `Run` button.

## **Demo GIF**  
Coming Soon