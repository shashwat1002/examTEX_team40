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
    while(current_character == character) // looping from behind to find the last valid character
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
    int mcq_index = 0; // to keep track of the number of mcq questions that have been parsed
    int current_mcq_arr_size = 1;
    ParsedTree* pt = (ParsedTree*) malloc(sizeof (ParsedTree)); // this will be what the question bank's representation
    McqQuestion** mcq_question_list = (McqQuestion**) malloc(sizeof(McqQuestion*) * 1);
    while(!feof(question_bank_file))
    {
        char tag[20] = {0};
        fscanf(question_bank_file, "%[^{]", tag);
        _trim_spaces(tag); // trim leading and trailing spaces
        _trim_newlines(tag); // trim leading and trailing newlines

        if(strcmp(tag, "\\mcq") == 0) {
            McqQuestion* current = parse_mcq_question(question_bank_file); // called the specific parser

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



PaperSpec* parse_questions_file(FILE* questions_file) // to parse the question instructions file
{
    char buffer_text[300];
    int _tripple_dash = 0; // this is to count the number of occurances of "---"

    PaperSpec* specs = (PaperSpec*) malloc(sizeof (PaperSpec)); // the return object

    while (1)
    {
        fscanf(questions_file, "%[^\n]%*c", buffer_text); // parameters parsed till newline
        _trim_newlines(buffer_text);
        _trim_spaces(buffer_text);

        if (strcmp(buffer_text, "---") == 0)
        {
            _tripple_dash++;

            if (_tripple_dash == 1) // If this is he first time we encounter "--"
            {
                continue;
            }
            if (_tripple_dash == 2)
            {
                break; // front matter is done with
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

        else // this portion is if the parameter is "papers"
        {

            char current = 0;
            int index = -1;
            while (current != ':') // we loop till ':' is encountered
            {
                index++;
                current = buffer_text[index];
            }
            int offset = index;

            char numbers[5] = {0}; // we expect a number, we don't know how big
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

            int number = atoi(numbers); // convert to integer
            specs -> number_of_papers = number;
        }
    }
    // parsing for the front matter is done with, next part begins here:
    char buffer[300] = {0};
    int index = 0; // keep track of how many samples have been read
    int size = 1; // size of the array
    SampleInformation** sample_arr = (SampleInformation**) malloc(sizeof (SampleInformation*) * size);
    SampleInformation* current;
    while(!feof(questions_file)) { // keep going till end of file is encountered
        QuestionType type;
        int number;
        double difficulty_low = 0.0;
        double difficulty_high = 0.0;
        fscanf(questions_file, "%[^{]", buffer);
        _trim_newlines(buffer);
        _trim_spaces(buffer);
        if (strcmp(buffer, "\\sample") == 0) {
            current = (SampleInformation *) malloc(sizeof(SampleInformation));
            for (int i = 0; i < 3; i++) { // we know each sample has only 3 attributes
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
