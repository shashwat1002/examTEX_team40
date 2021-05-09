#include "generation.h"

int BinarySearch_LowerBound( ParsedTree* T , double L ){
    if( T->mcq_questions[T->num_mcq_questions-1] < L ){
        return -1;
    }
    if( T->mcq_questions[0] >= L ){
        return 0;
    }
    int i = 1;
    int mid = T->num_mcq_questions;
    while(1){
        if( T->mcq_questions[i-1] < L && T->mcq_questions[i] >= L ){
            return i;
        }
        if( T->mcq_questions[i] >= L ){
            mid /= 2;
            i -= mid;
        }
        if( T->mcq_questions[i] < L ){
            mid /= 2;
            i += mid;
        }
    }
}

int BinarySearch_UpperBound( ParsedTree* T , double U ){
    if( T->mcq_questions[T->num_mcq_questions-1] <= U ){
        return T->num_mcq_questions-1;
    }
    if( T->mcq_questions[0] > U ){
        return -1;
    }
    int i = 1;
    int mid = T->num_mcq_questions;
    while(1){
        if( T->mcq_questions[i-1] <= U && T->mcq_questions[i] > U ){
            return i-1;
        }
        if( T->mcq_questions[i] > U ){
            mid /= 2;
            i -= mid;
        }
        if( T->mcq_questions[i] <= U ){
            mid /= 2;
            i += mid;
        }
    }
}


void RandDisplay(McqQuestion *question)
{
    srand(time(NULL));
    bool *OptionDisp = (bool *)malloc(4 * sizeof(bool));
    int NumDisp = 1;
    int Option;
    while (NumDisp <= 4)
    {
        Option = rand() % 4;

        if (!OptionDisp[Option])
        {
            printf("{%d} %s\n", NumDisp, question->option_list[Option]);
            OptionDisp[Option] = true;
            NumDisp++;
        }
    }
}

void display_mcq_question(McqQuestion *question, int Serial_number)
{
    int String_length = strlen(question->question_text);
    for (int i = 0; i < String_length + 15; i++)
    {
        printf("_");
    }
    printf("\n\n");
    printf("%d) %s\n", Serial_number, question->question_text);
    for (int i = 0; i < String_length + 15; i++)
    {
        printf("_");
    }
    printf("\n");

    // for (int i = 0; i < 4; i++)
    // {
    //     printf(" {%d} %s\n", i + 1, question->option_list[i]);
    // }
    RandDisplay(question);
}

