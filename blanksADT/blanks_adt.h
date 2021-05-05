

#ifndef blanks_adt_h
#define blanks_adt_h

#define answerLength 10
#include <stdio.h>

typedef struct question{
    char questionString[256];
    char** answerArray;
    int numberOfoptions;
}question;
typedef question* questionPtr;

questionPtr initializeQuestion(char question_string[], char answer_array[][answerLength], int numberOfAns);

#endif /* blanks_adt_h */
