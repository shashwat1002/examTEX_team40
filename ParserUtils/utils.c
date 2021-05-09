#include "utils.h"


void __trim__characters(char *text, char character)
{
    // take a string and a character
    // gets rid of all leading and trailing instances of the character from the text
    char current_character = text[0];
    int index_l = 0;
    while (current_character == character)
    {
        index_l++;
        current_character = text[index_l];
    }
    int offset = index_l;
    int length = strlen(text);

    for (int i = index_l; i <= length; i++) // include length because move null character as well
    {
        text[i - offset] = text[i];
    }

    // leading instances removed

    int index_r = length-1;
    current_character = text[index_r];
    while(current_character == character)
    {
        index_r--;
        current_character = text[index_r];
    }

    index_r++;
    text[index_r] = '\0';


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

            if (mcq_index >= current_mcq_arr_size) {
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



PaperSpec* parse_questions_file(FILE* questions_file)
{
    char buffer_text[300];
    int _tripple_dash = 0;

    PaperSpec* specs = (PaperSpec*) malloc(sizeof (PaperSpec));

    while (1)
    {
        fscanf(questions_file, "%[^\n]%*c", buffer_text);
        _trim_newlines(buffer_text);
        _trim_spaces(buffer_text);

        if (strcmp(buffer_text, "---") == 0)
        {
            _tripple_dash++;

            if (_tripple_dash == 1)
            {
                continue;
            }
            if (_tripple_dash == 2)
            {
                break;
            }
        }

        if (strcmp(buffer_text, "randomize: global") == 0)
        {
            specs -> scheme = global;
        }

        else if (strcmp(buffer_text, "randomize: sample-wise") == 0)
        {
            specs -> scheme = sample_wise;
        }

        else
        {

            char current = 0;
            int index = -1;
            while (current != ':')
            {
                index++;
                current = buffer_text[index];
            }
            int offset = index;

            char numbers[5] = {0};
            int digit = 0;

            while (1)
            {
                index++;
                current = buffer_text[index];
                if (current == '\0')
                {
                    break;
                }
                while (current == ' ')
                {
                    index++;
                    current = buffer_text[index];
                    // skip all spaces right after the :
                }
                if (!(current <= '9' && current >= '0'))
                {
                    printf("invalid argument for papers");
                    exit(0);
                }
                numbers[digit] = current;
                digit++;
            }

            int number = atoi(numbers);
            specs -> number_of_papers = number;
        }
    }

    char buffer[300] = {0};
    int index = 0;
    int size = 1;
    SampleInformation** sample_arr = (SampleInformation**) malloc(sizeof (SampleInformation*) * size);
    SampleInformation* current;
    while(!feof(questions_file)) {
        QuestionType type;
        int number;
        double difficulty_low = 0.0;
        double difficulty_high = 0.0;
        fscanf(questions_file, "%[^{]", buffer);
        _trim_newlines(buffer);
        _trim_spaces(buffer);
        if (strcmp(buffer, "\\sample") == 0) {
            current = (SampleInformation *) malloc(sizeof(SampleInformation));
            for (int i = 0; i < 3; i++) {
                fscanf(questions_file, "%*[^{]");
                fscanf(questions_file, "%*c");
                fscanf(questions_file, "%[^=]", buffer);
                fscanf(questions_file, "%*c");
                _trim_spaces(buffer);
                _trim_newlines(buffer);
                if (strcmp(buffer, "type") == 0) {
                    fscanf(questions_file, "%[^}]", buffer);
                    fscanf(questions_file, "%*c");
                    _trim_spaces(buffer);
                    _trim_newlines(buffer);
                    if (strcmp(buffer, "mcq") == 0) {
                        type = mcq;
                    }
                } else if (strcmp(buffer, "difficulty") == 0) {
                    fscanf(questions_file, "%*[^(]");
                    fscanf(questions_file, "%*c");
                    fscanf(questions_file, "%lf, %lf", &difficulty_low, &difficulty_high);
                    fscanf(questions_file, "%*[^}]");
                    fscanf(questions_file, "%*c");
                } else if (strcmp(buffer, "number") == 0) {
                    fscanf(questions_file, "%d", &number);
                    fscanf(questions_file, "%*[}]");
                    fscanf(questions_file, "%*c");
                }
            }

            current -> number_of_questions = number;
            current -> difficulty_lower_bound = difficulty_low;
            current -> difficulty_upper_bound = difficulty_high;
            current -> type = type;
            if(index >= size)
            {
                size *= 2;
                SampleInformation** tmp;
                tmp = realloc(sample_arr, sizeof(SampleInformation*) * size);
                assert(tmp != NULL);
                sample_arr = tmp; // realloc frees old memory
            }

            sample_arr[index] = current;
            index++;
        }
    }

    SampleInformation** tmp = realloc(sample_arr, sizeof (SampleInformation*) * index);
    // realloc to save memory

    if(tmp != NULL)
    {
        sample_arr = tmp;
    }

    // if realloc doesn't work then sample_arr points to valid memory
    // with all required data.

    specs -> num_of_samples = index;
    specs -> sample_list = sample_arr;

    return specs;
}
