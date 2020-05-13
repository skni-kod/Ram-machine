#ifndef RAM_MACHINE
#define RAM_MACHINE
#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 100
#define MAX_LABEL_LENGTH 33

typedef struct Command
{
    size_t cmd_index;
    char label[MAX_LABEL_LENGTH];
    char instruction[MAX_LABEL_LENGTH];
    char operand;
    size_t dest_adress;
    char dest_label[MAX_LABEL_LENGTH];
}Command;

typedef struct MachineState
{
    int *memory;
    size_t max_memory_size;
    int instruction_pointer;
    size_t cmd_count;
    Command *cmd_list;
    FILE *input_fp;
    FILE *output_fp; //TODO
}MachineState;

//input tape
FILE *load_file(char *file_path);
void print_file(FILE *fp);
int get_new_input(FILE *fp);
struct Command *parse_commands(FILE *fp, size_t *cmd_count);
size_t count_commands(FILE* fp);
void print_commands(Command *cmd_list, size_t cmd_count);
size_t get_matching_label(Command *cmd_list, size_t cmd_count, Command cmd);

//memory
int *init_memory(size_t mem_size);
void save_to_memory(int **memory, int index, int value);
int load_from_memory(int **memory, int index);
void print_memory(int **memory, size_t mem_size);

//instructions
int execute_command(MachineState *machine_ptr);
void loop(MachineState *machine_ptr);

#endif 