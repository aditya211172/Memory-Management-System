#include <stdio.h>
#include <stdlib.h>


#define MAX_BLOCKS 100

struct MemoryBlock {
    int processId;
    int size;
    int isAllocated;
};

struct Memory {
    struct MemoryBlock blocks[MAX_BLOCKS];
    int totalBlocks;
};

// Function prototypes
void initializeMemory(struct Memory *memory, int size);
void allocateMemoryFixed(struct Memory *memory, int processId, int size);
void deallocateMemoryFixed(struct Memory *memory, int processId);
void allocateMemoryDynamic(struct Memory *memory, int processId, int size);
void deallocateMemoryDynamic(struct Memory *memory, int processId);
void printMemoryStatus(struct Memory *memory);

// Implementations of memory management functions
                                                 
void initializeMemory(struct Memory *memory, int size) {
    memory->totalBlocks = 1;
    memory->blocks[0].processId = -1;
    memory->blocks[0].size = size;
    memory->blocks[0].isAllocated = 0;
}

void allocateMemoryFixed(struct Memory *memory, int processId, int size) {
    // Fixed partitioning, allocate in the first available block of exact size
    int i;
    for (i = 0; i < memory->totalBlocks; i++) {
        if (!memory->blocks[i].isAllocated && memory->blocks[i].size == size) {
            memory->blocks[i].processId = processId;
            memory->blocks[i].isAllocated = 1;
            printf("Memory allocated successfully for process %d.\n", processId);
            return;
        }
    }
    printf("Memory allocation failed for process %d.\n", processId);
}

void deallocateMemoryFixed(struct Memory *memory, int processId) {
    // Fixed partitioning, deallocate the block assigned to the process
    int i;
    for (i = 0; i < memory->totalBlocks; i++) {
        if (memory->blocks[i].processId == processId && memory->blocks[i].isAllocated) {
            memory->blocks[i].isAllocated = 0;
            printf("Memory deallocated successfully for process %d.\n", processId);
            return;
        }
    }
    printf("Memory deallocation failed for process %d.\n", processId);
}

void allocateMemoryDynamic(struct Memory *memory, int processId, int size) {
    // Dynamic partitioning, allocate in the first available block of sufficient size
    int i;
    for (i = 0; i < memory->totalBlocks; i++) {
        if (!memory->blocks[i].isAllocated && memory->blocks[i].size >= size) {
            memory->blocks[i].processId = processId;
            memory->blocks[i].isAllocated = 1;
            if (memory->blocks[i].size > size) {
                // Split the block if necessary
                struct MemoryBlock newBlock;
                newBlock.processId = -1;
                newBlock.size = memory->blocks[i].size - size;
                newBlock.isAllocated = 0;
                memory->totalBlocks++;
                int j;
                for (j = memory->totalBlocks - 1; j > i + 1; j--) {
                    memory->blocks[j] = memory->blocks[j - 1];
                }
                memory->blocks[i + 1] = newBlock;
                memory->blocks[i].size = size;
            }
            printf("Memory allocated successfully for process %d.\n", processId);
           
return;
}
}
printf("Memory allocation failed for process %d.\n", processId);
}

void deallocateMemoryDynamic(struct Memory *memory, int processId) {
// Dynamic partitioning, deallocate the block assigned to the process
int i;
for (i = 0; i < memory->totalBlocks; i++) {
if (memory->blocks[i].processId == processId && memory->blocks[i].isAllocated) {
memory->blocks[i].isAllocated = 0;
// Merge adjacent free blocks if possible
if (i > 0 && !memory->blocks[i - 1].isAllocated) {
memory->blocks[i - 1].size += memory->blocks[i].size;
for (int j = i; j < memory->totalBlocks - 1; j++) {
memory->blocks[j] = memory->blocks[j + 1];
}
memory->totalBlocks--;
i--;
}
if (i < memory->totalBlocks - 1 && !memory->blocks[i + 1].isAllocated) {
memory->blocks[i].size += memory->blocks[i + 1].size;
for (int j = i + 1; j < memory->totalBlocks - 1; j++) {
memory->blocks[j] = memory->blocks[j + 1];
}
memory->totalBlocks--;
}
printf("Memory deallocated successfully for process %d.\n", processId);
return;
}
}
printf("Memory deallocation failed for process %d.\n", processId);
}

void printMemoryStatus(struct Memory *memory) {
printf("Memory Status:\n");
printf("---------------\n");
for (int i = 0; i < memory->totalBlocks; i++) {
printf("Block %d: ", i);
if (memory->blocks[i].isAllocated) {
printf("Process %d (Size: %d)\n", memory->blocks[i].processId, memory->blocks[i].size);
} else {
printf("Free (Size: %d)\n", memory->blocks[i].size);
}
}
}

// Main function
int main() {
struct Memory memory;
int memorySize;
int choice;
int partitionChoice;
int processId, processSize;printf("Enter the memory size: ");
scanf("%d", &memorySize);

printf("Select partitioning scheme:\n");
printf("1. Fixed Partitioning\n");
printf("2. Dynamic Partitioning\n");
printf("Enter your choice: ");
scanf("%d", &partitionChoice);

// Initialize the memory
initializeMemory(&memory, memorySize);

while (1) {
    printf("\nMemory Management Menu:\n");
    printf("1. Allocate Memory\n");
    printf("2. Deallocate Memory\n");
    printf("3. Print Memory Status\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the process ID: ");
            scanf("%d", &processId);
            printf("Enter the process size: ");
            scanf("%d", &processSize);
            if (partitionChoice == 1) {
                allocateMemoryFixed(&memory, processId, processSize);
            } else if (partitionChoice == 2) {
                allocateMemoryDynamic(&memory, processId, processSize);
            } else {
                printf("Invalid partitioning scheme choice!\n");
            }
           
            break;
        case 2:
            printf("Enter the process ID to deallocate: ");
            scanf("%d", &processId);
            if (partitionChoice == 1) {
                deallocateMemoryFixed(&memory, processId);
            } else if (partitionChoice == 2) {
                deallocateMemoryDynamic(&memory, processId);
            } else {
                printf("Invalid partitioning scheme choice!\n");
            }
            break;
        case 3:
            printMemoryStatus(&memory);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
    }
}

return 0;
}