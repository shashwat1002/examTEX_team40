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
typedef enum supported_question_types QuestionType;

struct sample_information
{
    QuestionType type; // will have a value as to which question this sample corresponds to
    double difficulty_lower_bound;
    double difficulty_upper_bound;
    int number_of_questions;
};

typedef struct sample_information SampleInformation;

enum randomization_scheme {global=0, sample_wise=1};
// global randomization will lead to all questions being picked according to specification first
// followed by randomization
// sample wise randomization will randomize questions on a per sample basis.

struct question_paper_specifications
{
    SampleInformation** sample_list;
    enum randomization_scheme scheme;
    int number_of_papers;
};

McqQuestion* parse_mcq_question(FILE *question_bank_file);

ParsedTree* parse_question_bank(FILE *question_bank_file);
#endif