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

void save_to_memory(int **memory, int index, int value)
{
    if (index > MEM_SIZE)
    {
        fprintf(stderr, "Memory limit exceeded!");
        exit(EXIT_FAILURE);
    }

    (*memory)[index] = value;
}

int load_from_memory(int **memory, int index)
{
    if (index > MEM_SIZE)
    {
        fprintf(stderr, "Memory limit exceeded!");
        exit(EXIT_FAILURE);
    }

    int value = (*memory)[index];

    return value;
}

void print_memory(int **memory, size_t mem_size)
{
    printf("index : value\n");
    for (int i = 0; i < mem_size; i++)
    {   
        printf("%d   -   %d\n", i, (*memory)[i]);
    }
}
