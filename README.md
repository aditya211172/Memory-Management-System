# Memory Management System

This project is a simple Memory Management System implemented in C, designed to simulate memory allocation and deallocation using both fixed and dynamic partitioning schemes. The system allows you to allocate memory to processes and deallocate it, and it provides a visual representation of the memory blocks' status.

## Features

- **Fixed Partitioning**: Allocates memory blocks of a fixed size to processes.
- **Dynamic Partitioning**: Allocates memory blocks of varying sizes to processes, with the ability to split and merge blocks dynamically.
- **Memory Status Visualization**: Displays the current status of the memory blocks, showing which blocks are allocated and which are free.


## Usage
1. Run the compiled program:  ./memory_management_system
2. Enter the total memory size when prompted.
3. Choose the partitioning scheme (Fixed or Dynamic) when prompted.
4. Use the menu to allocate or deallocate memory for processes and view the memory status.

## Example
Enter the memory size: 1000
Select partitioning scheme:
1. Fixed Partitioning
2. Dynamic Partitioning
Enter your choice: 2

Memory Management Menu:
1. Allocate Memory
2. Deallocate Memory
3. Print Memory Status
4. Exit
Enter your choice: 1

Enter the process ID: 1
Enter the process size: 200
Memory allocated successfully for process 1.

Memory Management Menu:
1. Allocate Memory
2. Deallocate Memory
3. Print Memory Status
4. Exit
Enter your choice: 3

Memory Status:
---------------
Block 0: Process 1 (Size: 200)
Block 1: Free (Size: 800)
