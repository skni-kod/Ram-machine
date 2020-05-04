#ifndef RAM_MACHINE
#define RAM_MACHINE
#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 100

typedef struct Command
{
    size_t cmd_index;
    char label[32];
    char instruction[32];
    char operand;
    size_t dest_adress;
    char dest_label[32];
}Command;

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
int execute_command(Command *cmd_list, size_t cmd_count, int *instruction_pointer, FILE *input_fp, int *memory);
void loop(Command *cmd_list, size_t cmd_count, FILE *input_fp, int *memory);

#endif 