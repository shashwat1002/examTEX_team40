#ifndef __PARSER_UTILS_H
#define  __PARSER_UTILS_H

#include <stdio.h>
#include "../ADT/adt.h"
#include "my_stack.h"

#define current_option_limit 140

struct question_bank_tree
{
    McqQuestion** mcq_questions;
    int num_mcq_questions;
    // is the list of pointers corresponding to each Mcq question
};

typedef struct  question_bank_tree ParsedTree;

McqQuestion* parse_mcq_question(FILE *question_bank_file);

ParsedTree* parse_question_bank(FILE *question_bank_file);
#endif