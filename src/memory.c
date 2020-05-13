#include "ram_machine.h"
#include <stdio.h>
#include <stdlib.h>

int *init_memory(size_t mem_size)
{
    int *memory = calloc(mem_size, sizeof(int));
    
    if (memory == NULL)
    {
        fprintf(stderr, "Error while allocating memory:init_memory()!\n");
        exit(EXIT_FAILURE);
    }

    return memory;
}

void save_to_memory(MachineState *machine_ptr, int index, int value)
{
    if (index >= machine_ptr->max_memory_size)
    {
        fprintf(stderr, "Error:Memory limit exceeded!\n");
        fprintf(stderr, "Current memory size:%d\n", machine_ptr->max_memory_size);
        fprintf(stderr, "Exceeded memory index:%d\n", index);
        exit(EXIT_FAILURE);
    }

    machine_ptr->memory[index] = value;
}

int load_from_memory(MachineState *machine_ptr, int index)
{
    if (index >= machine_ptr->max_memory_size)
    {
        fprintf(stderr, "Error:Memory limit exceeded!\n");
        fprintf(stderr, "Current memory size:%d\n", machine_ptr->max_memory_size);
        fprintf(stderr, "Exceeded memory index:%d\n", index);
        exit(EXIT_FAILURE);
    }

    int value = machine_ptr->memory[index];

    return value;
}

void print_memory(MachineState *machine_ptr, size_t mem_size)
{
    printf("index : value\n");
    for (int i = 0; i < mem_size; i++)
    {   
        printf("%d   -   %d\n", i, machine_ptr->memory[i]);
    }
}
