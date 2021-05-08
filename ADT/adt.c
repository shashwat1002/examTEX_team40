#include "adt.h"

McqQuestion* initialize_mcq_question(double difficulty, char* question_text, int num_options, char** option_list, char* correct_option)// Initialises the MCQ adt 
{
    McqQuestion* question = (McqQuestion*) malloc(sizeof(McqQuestion));// Allocating memory to the main file
    assert(question != NULL);
    question -> difficulty = difficulty;

    int length = strlen(question_text);// Length of the question text
    length++;
    // length includes the '\0' character

    char* question_text_insert = (char *) malloc(length); // allocating memory to the string i.e(char *).

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

    question -> question_text = question_text_insert;// Making the actual file to be returned in the function
    question -> option_list = option_list_insert;
    question -> correct_option = correct_option_index;
    question -> total_options = num_options;

    return question;
}



void RandDisplay(McqQuestion *question) // A function which prints a MCQ question with randomised options
{
    srand(time(NULL)); // Uses the computer's internal clock to generate a random number
    bool *OptionDisp = (bool *)malloc(4 * sizeof(bool));
    int NumDisp = 1;
    int Option;
    while (NumDisp <= 4) //This loop goes on until we end up with 4 random options printed to the console
    {
        Option = rand() % 4; // So that we are left with {0, 1, 2, 3} randomly

        if (!OptionDisp[Option])
        {
            printf("{%d} %s\n", NumDisp, question->option_list[Option]);
            OptionDisp[Option] = true;
            NumDisp++;
        }
    }
}

void display_mcq_question(McqQuestion *question, int Serial_number) // function to display the questions.
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


questionPtr initializeQuestion(char question_string[], char answer_array[][answerLength], int numberOfAns, double difficulty_blanks){ //  function to initialise the FILL IN THE BLANKS question
    questionPtr q = (questionPtr)malloc(sizeof(question)); // The texts from the file are taken as the input.
    q->numberOfoptions = numberOfAns;
    q->difficulty = difficulty_blanks;
    strcpy(q->questionString, question_string);
    q->answerArray = (char**)malloc(sizeof(char*)*numberOfAns); // initialising a 2D array of chars, or an array of strings.
//    q->answerArray
    for(int i = 0; i < numberOfAns; i++){
        q->answerArray[i] = malloc(sizeof(char)*answerLength);// Initialising each string to a length which is fixed and prdefined
        strcpy(q->answerArray[i], answer_array[i]); // Copying the options to the array
    }
    return q;
}

void printQuestion_blanks(questionPtr q, int q_number){ 
    printf("\n%d.%s? (%d)\nAnswers:\n",q_number, q->questionString, q->numberOfoptions);
    for(int i = 1; i <= q->numberOfoptions; i++){
        printf("%d . %s\n", i, q->answerArray[i - 1]); // A function for displaying the Fill in the blanks question. 
    }
}

int takeAnswer_blanks(questionPtr q, char answer[]){ // returns 0 if wrong
    for(int i = 0; i < q->numberOfoptions;i++){
        if(strcmp(answer, q->answerArray[i]) == 0){
            return 1; // Traversing through the array to find if the user's answer is in the array of options
        }
    }
    return 0;
}


