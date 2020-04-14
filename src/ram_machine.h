#ifndef RAM_MACHINE
#define RAM_MACHINE
#include <stdio.h>
#include <stdlib.h>
#include "input_tape.c"

typedef struct command
{
    char label[32];
    char instruction[32];
    char operator;
    size_t dest_adress;
    char *comment[256];
} command;

FILE *load_file(char *file_path);
void print_file(FILE *fp);
struct command **parse_commands(FILE *fp);
size_t count_commands(FILE* fp);

#endif 