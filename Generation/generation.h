#ifndef __GENERATION_H
#define __GENERATION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

struct mcq_question
{
    char *question_text;
    char **option_list;
    int correct_option;
    double difficulty;
    int total_options;
};

struct question_bank_tree{
    McqQuestion** mcq_questions;
    int num_mcq_questions;
};
typedef struct mcq_question McqQuestion;
typedef struct question_bank_tree ParsedTree;


int BinarySearch_LowerBound( ParsedTree* T , double L );
int BinarySearch_UpperBound( ParsedTree* T , double U );
void RandDisplay(McqQuestion *question);
void display_mcq_question(McqQuestion *question, int Serial_number);

#endif
