#include "parser.h"
#include "error.h"
#include "stdio.h"
#include "stdlib.h"
#include "symtable.h"

#define MAX_INSTRUCTION_COUNT 30000

int main (int argc, const char *argv[]){
    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
    if(argc != 2){
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL){
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    parse(fin, instructions);
    int num_instructions;
    num_instructions = parse(fin, instructions);
    fclose(fin);
    free(instructions);
}