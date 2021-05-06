

#include "blanks_adt.h"
//#include<stdlib.h>
//#include<string.h>


questionPtr initializeQuestion_fillInTheBlanks(char question_string[], char answer_array[][answerLength], int numberOfAns){
    questionPtr q = (questionPtr)malloc(sizeof(question));
    q->numberOfoptions = numberOfAns;
    strcpy(q->questionString, question_string);
    q->answerArray = (char**)malloc(sizeof(char*)*numberOfAns);
//    q->answerArray
    for(int i = 0; i < numberOfAns; i++){
        q->answerArray[i] = malloc(sizeof(char)*answerLength);
        strcpy(q->answerArray[i], answer_array[i]);
    }
    return q;
}

void printQuestion_blanks(questionPtr q){
    printf("\n%s? (%d)\nAnswers:\n", q->questionString, q->numberOfoptions);
    for(int i = 1; i <= q->numberOfoptions; i++){
        printf("%d . %s\n", i, q->answerArray[i - 1]);
    }
}

int printQuestion_takeAnswer_blanks(questionPtr q){ // returns 0 if wrong
    char s[asnwerLength];
    printf("\n%s?\n");
    printf("Answer: ");
    scanf("%s", s);
    for(int i = 0; i < q->numberOfoptions;i++){
        if(strcmp(s, q->answerArray[i]) == 0){
            return 1;
        }
    }
    return 0;
}


