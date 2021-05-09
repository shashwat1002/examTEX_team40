#include "GeneralUtils/general_utils.h"
#include "ParserUtils/utils.h"
#include "Generation/generation.h"
#include <stdio.h>

int main()
{
    FILE* bank_file = fopen("questionBank2.txt", "r");

    ParsedTree* pt = parse_question_bank(bank_file);
    merge_sort(pt -> mcq_questions, 0, pt -> num_mcq_questions-1);
    // sorted on the basis of difficulty
    fclose(bank_file);

    FILE* questions_file = fopen("sample_questions_file.in", "r");

    PaperSpec* spec = parse_questions_file(questions_file);
    fclose(questions_file);
    // file_name should be variable because the program
    // can generate multiple files depending on the questions file
    char file_name[300] ;
    for(int i = 0; i < spec -> number_of_papers; i++)
    {
        sprintf(file_name, "paper%d.txt", (i+1));
        FILE* fp = fopen(file_name, "w");

        int question_no = 1;
        int number_of_sample = spec -> num_of_samples;

        for(int j = 0; j < number_of_sample; j++)
        {
            double U = spec -> sample_list[j] -> difficulty_upper_bound;
            double L = spec -> sample_list[j] -> difficulty_lower_bound;
            int number = spec -> sample_list[j] -> number_of_questions;

            ChooseQuestions(pt, U, L, number, fp, &question_no);
        }
        fclose(fp);
    }



}