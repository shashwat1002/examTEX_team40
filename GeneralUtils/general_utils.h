#ifndef __GENERAL_UTILS_H
#define __GENERAL_UTILS_H

#include <stdlib.h>
struct mcq_question
{
    char *question_text;
    char **option_list;
    int correct_option;
    double difficulty;
    int total_options;
};

typedef struct mcq_question McqQuestion;


void merge( McqQuestion** arr, int low, int mid, int high);
void merge_sort(McqQuestion** arr, int low, int high);





#endif
