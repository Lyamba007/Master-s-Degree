# Models of logical control systems based on microcontroller devices

The concepts of logic control systems, real-time systems and time machines are considered in detail. The method of their use in microcontroller systems is analyzed.
The principles of automatic programming in accordance with the peculiarities of the implementation of devices on the microcontroller (compatibility with the system of events / interrupts) are considered in detail
Based on the entire analysis, an automatic template for microcontroller systems was created, which meets all the criteria of real-time systems.
A microcontroller control device for pedestrian crossing lighting based on a state machine with the considered ones has been developed.
The concept of an automatic template for microcontroller systems was used in the development of the microcontroller device. The software implementation has two scenarios (templates): standard and alternative.
The standard template corresponds to all time parameters that are embedded in the concept of time machines (implemented output delays, state delays and constraint window). An alternative template eliminates the concept of output delays, due to the mechanism of splitting states, which leads to the use of the concept of separation of responsibilities (each state is a specific task).
The result of real-time implementation of the implemented system with the help of hardware debugging with the help of logic analyzer is considered and analyzed.
___________________________________________________________________________________________________________________________________________
# Area of improvement

It is possible to base the solution on the microcontroller in STM32 series STM32F030C8T6.
____________________________________________________________________________________________________________________________________________
# Repository content

The repository consist of:
SPLIT control device realization and STANDARD control device realization on C (STM32F103C8T6)
SPLIT and STANDARD waveforms created in Logic software.
Projects notes (Master's degree) in Ukrainian.
Presentation notes in English
____________________________________________________________________________________________________________________________________________
