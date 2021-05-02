#ifndef __ADT_H
#define  __ADT_H
#include <string.h>
#include <malloc.h>
#include <assert.h>

enum supported_question_types {mcq = 0};
// more supported types will be added to this enumeration.

struct mcq_question
{
    char* question_text;
    char** option_list;
    int correct_option; // will have index of the correct option as in the option_list
    double difficulty;
    int total_options;
};

typedef struct mcq_question McqQuestion;

McqQuestion* initialize_mcq_question(double difficulty, char* question_text, int num_options, char option_list[num_options][140], char* correct_option);
// the above method takes the correct option as a string as well.

void display_mcq_question(McqQuestion* question);

#endif