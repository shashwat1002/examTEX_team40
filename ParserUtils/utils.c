#include "utils.h"


void __trim__characters(char* text, char character)
{
    // take a string and a character
    // gets rid of all leading and trailing instances of the character from the text
    char current_character = text[0];
    int index_l = 0;
    while(current_character == character)
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

    // leading instances removed

    char* first_space = index(text, character);
    if(first_space != NULL)
    {
        text[(first_space - &text[0])] = '\0';
        // trailing instances were removed.
    }

}

void _trim_spaces(char* text)
{
    // gets rid of leading and trailing spaces
    __trim__characters(text, ' ');
}

void _trim_newlines(char* text)
{
    // gets rid of leading and trailing newlines
    __trim__characters(text, '\n');
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

ParsedTree* parse_question_bank(FILE* question_bank_file)
{
    int mcq_index = 0;
    int current_mcq_arr_size = 1;
    ParsedTree* pt = (ParsedTree*) malloc(sizeof (ParsedTree));
    McqQuestion** mcq_question_list = (McqQuestion**) malloc(sizeof(McqQuestion*) * 1);
    while(!feof(question_bank_file))
    {
        char tag[20] = {0};
        fscanf(question_bank_file, "%[^{]", tag);
        _trim_spaces(tag);
        _trim_newlines(tag);
        if(strcmp(tag, "\\end") == 0) // in case of end tag
        {
            continue;
        }
        if(strcmp(tag, "\\mcq") == 0) {
            McqQuestion* current = parse_mcq_question(question_bank_file);

            fscanf(question_bank_file, "%*[^\n]");

            if (index >= current_mcq_arr_size) {
                // reallocating and increasing the size of the array
                current_mcq_arr_size *= 2;
                assert(mcq_question_list != NULL);
                McqQuestion **tmp = (McqQuestion **) realloc(mcq_question_list, current_mcq_arr_size * sizeof(McqQuestion *));
                mcq_question_list = tmp; // realloc frees old memory on success
            }
            mcq_question_list[mcq_index] = current;
            mcq_index++;


            mcq_question_list = (McqQuestion **) realloc(mcq_question_list, (mcq_index + 1) * sizeof(McqQuestion *));
            // realloc to save memory, index+1 because index was the last place filled.

            pt->mcq_questions = mcq_question_list;
            pt->num_mcq_questions = mcq_index;
        }

    }

    return pt;
}