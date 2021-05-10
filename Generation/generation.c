#include "generation.h"

int BinarySearch_LowerBound( ParsedTree* T , double L ){
    /*Here, we account for the case where the largest element in the array is smaller than the lower bound.*/
    if( T->mcq_questions[T->num_mcq_questions-1] -> difficulty < L ){
        return -1;
    }
    /*Here, we account for the case where the smallest element is larger than the lower bound.*/
    if( T->mcq_questions[0] -> difficulty >= L ){
        return 0;
    }
    int i = 1;
    int mid = T->num_mcq_questions;
    while(1){
        if( T->mcq_questions[i-1] -> difficulty < L && T->mcq_questions[i] -> difficulty >= L ){
            return i;
        }
        if( T->mcq_questions[i] -> difficulty >= L ){
            if( mid != 1 ){
              mid /= 2;
            }
            i -= mid;
        }
        if( T->mcq_questions[i] -> difficulty < L ){
            if( mid != 1 ){
              mid /= 2;
            }
            i += mid;
        }
    }
}

int BinarySearch_UpperBound( ParsedTree* T , double U ){
    /*Here, we account for the case where the largest element is smaller than the upper bound.*/
        if( T->mcq_questions[T->num_mcq_questions-1]->difficulty <= U ){
        return T->num_mcq_questions-1;
    }
    /*Here, we account for the case where the smallest element is larger than the upper bound.*/
    if( T->mcq_questions[0]->difficulty > U ){
        return -1;
    }
    int i = 1;
    int mid = T->num_mcq_questions;
    while(1){
        if( T->mcq_questions[i-1]->difficulty <= U && T->mcq_questions[i]->difficulty > U ){
            return i-1;
        }
        if( T->mcq_questions[i]->difficulty > U ){
            if( mid != 1 ){
              mid /= 2;
            }
            i -= mid;
        }
        if( T->mcq_questions[i]->difficulty <= U ){
            if( mid != 1 ){
              mid /= 2;
            }
            i += mid;
        }
    }
}

void ChooseQuestions( ParsedTree* T, double U, double L, int NumQuestions, FILE* fp, int* start_index ){
    // this method will be called whenever we want to display all the questions corresponding to a sample
    // these batches will be printed one after the other
    // the start_index gives us an idea of the stage of printing
    // so the question no. will be decided from the start index
    // doube U is for the upper bound of difficulty 
    // double L is for the lower bound of difficulty
    bool* Disp = ( bool* ) malloc( NumQuestions * sizeof( bool ) );
    int NumDisp = 0;
    int Question;
    ///int Up = BinarySearch_UpperBound( T , U );
    int Lw = BinarySearch_LowerBound( T , L );
    int Uw = BinarySearch_UpperBound(T, U);
    int difference = Uw - Lw + 1; // has the number of available questions in the range
    if(NumQuestions > difference)
    {
        // if more questions are required in a range
        // than available in the bank then exit and print
        printf("Error: more questions demanded in difficulty range %lf to %lf than available\n", L, U);
        printf("Demanded: %d, available: %d", NumQuestions, difference);
        exit(0);
    }
    while( NumDisp < NumQuestions ){
        Question = rand() % difference;
        if( !Disp[Question] ){
            display_mcq_question( T->mcq_questions[Question + Lw], *start_index, fp);
            *start_index = *start_index + 1;
            Disp[Question] = true;
            NumDisp++;
        }
    }
}
