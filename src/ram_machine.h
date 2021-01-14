#ifndef RAM_MACHINE
#define RAM_MACHINE
#include <stdio.h>
#include <stdlib.h>

#define MAX_LABEL_LENGTH 33

//!Structure representing one ram-machine command.
/*! \struct Command
    Each line of the ram-machine code is parsed to this structure.
*/
typedef struct Command
{
    size_t cmd_index; /*!<An index of the command. Represents its place in the program.*/
    size_t dest_adress;/*!<Destination adress. Represents an index the command is referring to.*/
    char label[MAX_LABEL_LENGTH];/*!<Label of the command. Used with the jump instuctions.*/
    char instruction[MAX_LABEL_LENGTH];/*!<Instruction of the command. Defines the command's activity.*/
    char operand;/*!<Operand/access modifier of the command. Speficies how to handle the instruction argument. */
    char dest_label[MAX_LABEL_LENGTH];/*!<Destination label of the command. Used with the jump instructions.*/
}Command;

//!Structure representing current ram-machine state.
/*! \struct MachineState
    Allows to keep track of the machine's state and keeps all the information at one place.
*/
typedef struct MachineState
{
    int *memory;/*!<A pointer to the machine's memory, which is an array of integers.*/
    size_t max_memory_size;/*!<The maximum amount of the registers. Specifies the last available register.*/
    int instruction_pointer;/*!<An instruction pointer. Specifies the command currently executed by the machine.*/
    size_t cmd_count;/*!<The amount of commands in the ram-machine program. Helps to keep track of the machine's state.*/
    int max_used_memory_index;/*!<An index of the highest memory register used. Allows to keep track how many registers are being used.*/
    Command *cmd_list;/*!<The array of the commands. Contains the whole parsed ram-machine program.*/
    FILE *input_fp;/*!<A pointer to the input stream.*/
    FILE *output_fp; /*!<A pointer to the output stream.*/
}MachineState;


//! Main function.
/*!
    The main function links the whole program together.
*/
int main(int argc, char *argv[]);

//init
//! Parse program arguments.
/*! 
    The parse_arguments fuction parses arguments passed with the program's execution.
    This is the program's initial step.
    \param machine_ptr A pointer to the MachineState structure.
    \param argc The amount of arguments passed with the program's execution.
    \param argv An array of the arguments passed with the program's execution.
    \param instr_fp A pointer to the ram-machine code's stream pointer.
*/
void parse_arguments(MachineState *machine_ptr, int argc, char *argv[], FILE **instr_fp);

//input tape
//! Load an input file.
/*!
    The load_file function loads a file in read only mode.
    \param file_path A file path.
    \returns A pointer to a FILE stream on success or NULL pointer on failure.
*/
FILE *load_file(char *file_path);

//! Load an output file.
/*!
    The load_file function loads a file in write only mode.
    \param file_path A file path.
    \returns A pointer to a FILE stream on success or NULL pointer on failure.
*/
FILE *load_output_file(char *file_path);

//! Print file.
/*!
    The print_file function prints the contents of the file.
    \param fp A pointer to the FILE stream.
*/
void print_file(FILE *fp);

//! Get new input.
/*!
    The get_new_input function gets next value from the input stream.
    Exits with EXIT_FAILURE when there are no more values to retrieve.
    \param fp A pointer to the input FILE stream.
    \returns Retrieved value from the input stream on success.
*/
int get_new_input(FILE *fp);

//! Parse commands.
/*!
    The parse_commands function parses the code file, 
    which contains the ram-machine program. 
    \param fp A pointer to the code FILE stream.
    \param cmd_count A pointer to the command count variable, which is modified inside the function.
    \returns An array of Command structures, containing parsed ram-machine program.
*/
struct Command *parse_commands(FILE *fp, size_t *cmd_count);

//! Count commands.
/*!
    The count_commands function counts the number of the ';' sign apperances
    in the code file, which is equal to the number of commands in the ram-machine program.
    \param fp A pointer to the code FILE stream.
    \returns The number of the commands in the code file.
*/
size_t count_commands(FILE* fp);

//! Print commands.
/*!
    The print_commands function prints out the commands, with its content, from the commmands array.
    \param cmd_list The array of commands, parsed using parse_commands function.
    \param cmd_count Command count variable.
*/
void print_commands(Command *cmd_list, size_t cmd_count);

//! Get matching label.
/*!
    The get_matching_label function searches the commands array for a command with matching label.
    \param cmd_list The array of commands, parsed using parse_commands function.
    If the matching command has not been found, the function returns error and exits, 
    as the program itself has to be wrong.
    \param cmd_cmount Command count variable.
    \param cmd The command for which a matching label has to be found. It has to be one of the jump instructions
    \returns An index of the command with matching label.
*/
int get_matching_label(Command *cmd_list, size_t cmd_count, Command cmd);

//memory
//! Initialise memory.
/*!
    The init_memory function initialises the ram-machine memory, 
    allocating the memory for the memory array in size of mem_size.
    \param mem_size The size of the initialised memory. It also represents the maximum available register.
    \returns A pointer to the memory array.
*/
int *init_memory(size_t mem_size);

//! Save to memory.
/*!
    The save_to_memory function writes a value to the memory's register.
    \param machine_ptr A pointer to the MachineState structure.
    \param index An index of the memory register for the value to be written to.
    \param value The value to be written to the memory register.
*/
void save_to_memory(MachineState *machine_ptr,  int index, int value);

//! Load from memory.
/*!
    The load_from_memory function gets a value from the memory register 
    speficied by the index.
    \param machine_ptr A pointer to the MachineState structure.
    \param index An index of the memory register from which the value will be retrieved.
    \returns The retrieved value of the memory register.
*/
int load_from_memory(MachineState *machine_ptr, int index);

//! Print memory.
/*!
    The print_memory function prints out the contents of the ram-machine's memory,
    printing out first mem_size registers.
    \param machine_ptr A pointer to the MachineState structure.
    \param mem_size The number of registers we want to print out, beginning from 0.
*/
void print_memory(MachineState *machine_ptr, size_t mem_size);

//instructions
//! Execute command.
/*!
    The execute_command function is probably the most important function in the whole program.
    It executes one command from the commands array, using the current instruction_pointer 
    located in the MachineState structure. Depending on the command, it changes the instruction 
    pointer, memory contents, performs operations on the accumulator, reads new input from the input
    stream or writes values to the output.
    \param machine_ptr A pointer to the MachineState structure.
    \returns 0 on success.
*/
int execute_command(MachineState *machine_ptr);

//! Loop function.
/*!
    The loop function is the main loop of the ram-machine interpreter. It runs the parsed code 
    until the program finishes or an error is encountered.
*/
void loop(MachineState *machine_ptr);

#endif 