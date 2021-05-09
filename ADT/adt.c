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

void display_mcq_question(McqQuestion *question, int Serial_number, FILE* fp)
{
    fp = fopen("out.txt", "a");

    int String_length = strlen(question->question_text);
    for (int i = 0; i < String_length + 15; i++)
    {
        fprintf(fp, "_");
    }
    fprintf(fp, "\n\n");
    fprintf(fp, "%d) %s\n", Serial_number, question->question_text);
    for (int i = 0; i < String_length + 15; i++)
    {
        fprintf(fp, "_");
    }
    fprintf(fp, "\n");

    
    srand(time(NULL));
    bool *OptionDisp = (bool *)malloc(4 * sizeof(bool));
    int NumDisp = 1;
    int Option;
    while (NumDisp <= 4)
    {
        Option = rand() % 4;

        if (!OptionDisp[Option])
        {
            fprintf(fp, "{%d} %s\n", NumDisp, question->option_list[Option]);
            OptionDisp[Option] = true;
            NumDisp++;
        }
    }
    fclose(fp);
}



questionPtr initializeQuestion(char question_string[], char answer_array[][answerLength], int numberOfAns){
    questionPtr q = (questionPtr)malloc(sizeof(questionPtr));
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

void printQuestion_blanks(questionPtr q, FILE*fp){
    fp = fopen("out.txt", "a");

    fprintf(fp, "\n%s? (%d)\n", q->questionString, q->numberOfoptions);
    fclose(fp);
    
}

int takeAnswer_blanks(questionPtr q, char answer[]){ // returns 0 if wrong
    for(int i = 0; i < q->numberOfoptions;i++){
        if(strcmp(answer, q->answerArray[i]) == 0){
            return 1;
        }
    }
    return 0;
}

/*
int main(){
    FILE *fp = fopen("out.txt", "a");
  /*  char options[3][10] = {"this", "that", "none"};
    questionPtr q_blank = initializeQuestion("What is this", options, 3);
    printQuestion_blanks(q_blank, fp);
    


    fprintf(fp, "\nYE BOI\n");




    char** options = malloc(sizeof(char*)*4);
    for(int i = 0; i < 4; i++){
        options[i] = malloc(sizeof(char)*20);
    }

    options[0] = "OHNo";
    options[1] = "NANI?";
    options[2] = "OK";
    options[3] = "none";

    McqQuestion* question_mcq = initialize_mcq_question(0.2, "Omae wa mo shinderu", 4, options, "NANI");
    display_mcq_question(question_mcq, 1, fp);
    fclose(fp);
}
*/
// The main function is used for testing
