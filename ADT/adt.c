#include "adt.h"

McqQuestion* initialize_mcq_question(double difficulty, char* question_text, int num_options, char** option_list, char* correct_option)
{
    // method to construct mcq question objects and return the respective pointer
    McqQuestion* question = (McqQuestion*) malloc(sizeof(McqQuestion));
    assert(question != NULL); // checking malloc fails
    question -> difficulty = difficulty;

    int length = strlen(question_text);
    length++;
    // length includes the 0 character

    char* question_text_insert = (char *) malloc(length);

    strcpy(question_text_insert, question_text); // copying for safety

    int correct_option_index = 0;

    char** option_list_insert = (char**) malloc(num_options * sizeof (char*));
    // the list that'll be entered into the object, basically a copy of input into the heap


    for(int j = 0; j < num_options; j++) // this loop to copy the options list from the argument to the object
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



void RandDisplay(McqQuestion *question, FILE* fp)
{
    bool *OptionDisp = (bool *)calloc(4, sizeof(bool));
    int NumDisp = 1;
    int Option;
    while (NumDisp <= 4)
    {
        Option = rand() % 4;
        while(OptionDisp[Option])
        {
            Option = (Option + 1) % 4; // probe till next un-seen option
        }
        // this loop prevents infinite loops

        if (!OptionDisp[Option])
        {
            fprintf(fp, "{%d} %s\n", NumDisp, question->option_list[Option]);
            OptionDisp[Option] = true;
            NumDisp++;
        }
    }
}

void display_mcq_question(McqQuestion *question, int Serial_number, FILE* fp)
{
    int String_length = strlen(question->question_text);
    /*This is for printing a line.*/
    for (int i = 0; i < String_length + 15; i++)
    {
        fprintf(fp, "_");
    }
    fprintf(fp, "\n\n");
    fprintf(fp, "%d) %s\n", Serial_number, question->question_text);
    /*This is for printing a line.*/
    for (int i = 0; i < String_length + 15; i++)
    {
        fprintf(fp, "_");
    }
    fprintf(fp, "\n");


    RandDisplay(question, fp);
}



questionPtr initializeQuestion(char question_string[], char answer_array[][answerLength], int numberOfAns){ // A function to initialise the Question of blanks
    questionPtr q = (questionPtr)malloc(sizeof(questionPtr)); // Main struct's allocation
    q->numberOfoptions = numberOfAns; // giving in the number of answers.
    strcpy(q->questionString, question_string); // Copying the main question string
    q->answerArray = (char**)malloc(sizeof(char*)*numberOfAns); // allocating the space for each char* in the array of correctAnswers (strings)
    for(int i = 0; i < numberOfAns; i++){
        q->answerArray[i] = malloc(sizeof(char)*answerLength); // Allocating string linealy
        strcpy(q->answerArray[i], answer_array[i]); // Copying the answer
    }
    return q;
}

void printQuestion_blanks(questionPtr q, FILE*fp){ // A function to print the question to the output file.
    for(int i = 0; i < strlen(q->questionString); i++){
        fprintf(fp, "_");
    }
    fprintf(fp, "\n%s? (%d)\n", q->questionString, q->numberOfoptions); // The question is printed.
    fprintf(fp, "Answer: \n"); // The user's prompt or the place to write the answer.
    for(int i = 0; i < strlen(q->questionString); i++){
        fprintf(fp, "_");
    }
    
}

int takeAnswer_blanks(questionPtr q, char answer[]){ // Returns a boolean if the answer  (0 if wrong, else 1).
    for(int i = 0; i < q->numberOfoptions;i++){
        if(strcmp(answer, q->answerArray[i]) == 0){ // This is basically linear traversal thorugh the array of strings checking for the correct answer.
            return 1; // Whenever correct answer is found, 1 is returned and we exit from the function
        }
    }
    return 0; // If it exits the loop, it means that no correct answer is found. So, returns 0
}
