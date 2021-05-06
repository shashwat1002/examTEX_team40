#include "utils.h"


void _trim_spaces(char* text)
{
     char current_character = text[0];
     int index_l = 0;
     while(current_character == ' ')
     {
         index_l++;
         current_character = text[index_l];
     }
     int offset = index_l;
     int length = strlen(text);

     for(int i  = index_l; i <= length; i++) // include length because move null character as well
     {
         text[i-offset] = text[i];
     }

     // leading spaces removed

     char* first_space = index(text, ' ');
     if(first_space != NULL)
     {
         text[(first_space - &text[0])] = '\0';
         // trailing space were removed.
     }

}

McqQuestion* parse_mcq_question(FILE *question_bank_file)
{
    const int total_possible_attributes = 4;
    // an mcq question can have total 4 attributes
    // namely: difficulty, question text, options, correct answer

    char items_scanned[4] = {0, 0, 0, 0}; // all attributes that have been discovered

    Header* parsing_stack = (Header*) malloc(sizeof (Header));
    char** options;
    double difficulty;
    char* question_text = (char*) malloc(10000);
    char correct_option[current_option_limit] = {0};
    int num_options;
    char* general_temp_text = (char*) malloc(10000);
    for(int i = 0; i < 4; i++)
    {
        fscanf(question_bank_file, "%*[^{]"); // read till opening brackets
        fscanf(question_bank_file, "%*c"); // get rid of opening bracket
        //Push(parsing_stack, '{');
        char current_attribute_name[50] = {0}; // will store the name of the attribute read.
        fscanf(question_bank_file, "%[^=]%*c", current_attribute_name);
        // take everything till the equal

        _trim_spaces(current_attribute_name);
        // removed trailing and leading spaces.


        if(strcmp(current_attribute_name, "difficulty") == 0)
        {
            fscanf(question_bank_file, "%lf", &difficulty);
            fscanf(question_bank_file, "%*[^}]%*c");
        }
        else if(strcmp(current_attribute_name, "text") == 0)
        {
            fscanf(question_bank_file, "%*[^\"]%*c");
            fscanf(question_bank_file,"%[^\"]%*c", question_text);
            int length = strlen(question_text);
            question_text = (char*) realloc(question_text, length+1);
            fscanf(question_bank_file, "%*[^}]%*c");
        }
        else if(strcmp(current_attribute_name, "ans") == 0)
        {
            fscanf(question_bank_file, "%*[^\"]%*c");
            fscanf(question_bank_file,"%[^\"]%*c", correct_option);
            fscanf(question_bank_file, "%*[^}]%*c");
        }
        else if(strcmp(current_attribute_name, "opt") == 0)
        {
            fscanf(question_bank_file, "%[^}]%*c", general_temp_text);
            int count_commas = 0;

            char current_character = general_temp_text[0];
            int _ = 0;
            while(current_character != '\0')
            {
                if(current_character == ',')
                {
                    count_commas++;
                }
                _++;
                current_character = general_temp_text[_];
            }

            num_options = count_commas + 1;
            options = (char**) malloc(sizeof(char*) * num_options);
            int index = 0;
            for(int i = 0; i < num_options; i++)
            {
                options[i] = (char*) calloc(current_option_limit, 1);
                while(current_character != '\"')
                {
                    index++;
                    current_character = general_temp_text[index];
                    // everything before the first \" is not important
                }

                int j = 0;
                index++;
                current_character = general_temp_text[index];

                while(current_character != '\"')
                {
                    options[i][j] = general_temp_text[index];
                    index++;
                    j++;
                    current_character = general_temp_text[index];
                }

                index++;
                current_character = general_temp_text[index];

                if(current_character == '\0')
                {
                    break;
                }
            }
        }
    }
    McqQuestion* question = initialize_mcq_question(difficulty, question_text, num_options, options, correct_option);
    free(general_temp_text); // because the initialize_mcq_question copies everything

    // freeing sequence
    for(int i = 0; i < num_options; i++)
    {
        free(options[i]);
    }
    free(options);
    free(question_text);
    return question;

}