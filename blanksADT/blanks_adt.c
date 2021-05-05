

#include "blanks_adt.h"
#include<stdlib.h>
#include<string.h>


questionPtr initializeQuestion(char question_string[], char answer_array[][answerLength], int numberOfAns){
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

void printQuestion(questionPtr q){
    printf("\n%s? (%d)\nAnswers:\n", q->questionString, q->numberOfoptions);
    for(int i = 1; i <= q->numberOfoptions; i++){
        printf("%d . %s\n", i, q->answerArray[i - 1]);
    }
}


int main(){
    char q_string[] = "what is this";
    char a_array[3][10] = {"That", "tHis", "this"};
    
    questionPtr q = initializeQuestion(q_string, a_array, 3);
    printQuestion(q);
    return 0;
}
