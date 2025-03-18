#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef enum TYPE{
    MANUAL_RANDOM,
    MANUAL_EMPTY,
    MANUAL_FULL,
    MANUAL_CUSTOM,

    AI_RANDOM,
    AI_EMPTY,
    AI_FULL,
    AI_CUSTOM,
}func_type;

typedef struct INSTRUCTION{
    size_t nodes;
    size_t edges;
    func_type type;

    // for custom only 
    size_t* from;
    size_t* to;
    size_t custom_size;
}instruct;

instruct instruction_parser(char* instruction);

void free_instruction(instruct instruction);

#endif
