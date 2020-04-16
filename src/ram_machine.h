#ifndef RAM_MACHINE
#define RAM_MACHINE
#include <stdio.h>
#include <stdlib.h>


typedef struct Command
{
    size_t cmd_index;
    char label[32];
    char instruction[32];
    char operator;
    size_t dest_adress;
}Command;

FILE *load_file(char *file_path);
void print_file(FILE *fp);
struct Command *parse_commands(FILE *fp);
size_t count_commands(FILE* fp);

#endif 