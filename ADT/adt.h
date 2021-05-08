#ifndef __ADT_H
#define  __ADT_H
#include <string.h>
#include <malloc.h>
#include <assert.h>
#define answerLength 10 // for fill in the blanks questions

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

McqQuestion* initialize_mcq_question(double difficulty, char* question_text, int num_options, char** option_list, char* correct_option);
// the above method takes the correct option as a string as well.

void display_mcq_question(McqQuestion* question , int Serial_number );



typedef struct question_blanks{
    char questionString[256];
    char** answerArray;
    int numberOfoptions;
    double difficulty;
}question_blanks;
typedef question_blanks* questionPtr;

questionPtr initializeQuestion(char question_string[], char answer_array[][answerLength], int numberOfAns, double difficulty_blanks); // New change made here
void printQuestion_blanks(questionPtr q); // Prints Output to the console
int takeAnswer_blanks(questionPtr q, char answer[]);

#endif
