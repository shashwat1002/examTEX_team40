#include "adt.h"

McqQuestion* initialize_mcq_question(double difficulty, char* question_text, int num_options, char** option_list, char* correct_option)
{
    McqQuestion* question = (McqQuestion*) malloc(sizeof(McqQuestion));
    assert(question != NULL);
    question -> difficulty = difficulty;

    int length = strlen(question_text);
    length++;
    // length includes the 0 character

    char* question_text_insert = (char *) malloc(length);

    strcpy(question_text_insert, question_text);

    int correct_option_index = 0;

    char** option_list_insert = (char**) malloc(num_options * sizeof (char*));
    // the list that'll be entered into the object, basically a copy of input into the heap


    for(int j = 0; j < num_options; j++)
    {
        char* current = option_list[j];
        if(strcmp(current, correct_option) == 0)
        {
            correct_option_index = j;
        }

        int length = strlen(current) + 1; // +1 to include the terminating byte
        char* copy_current = (char*) malloc(length);
        strcpy(copy_current, current);
        option_list_insert[j] = copy_current;
    }

    question -> question_text = question_text_insert;
    question -> option_list = option_list_insert;
    question -> correct_option = correct_option_index;
    question -> total_options = num_options;

    return question;
}

