#include "generation.h"

int BinarySearch_LowerBound( ParsedTree* T , double L ){
    if( T->mcq_questions[T->num_mcq_questions-1]->difficulty < L ){
        return -1;
    }
    if( T->mcq_questions[0]->difficulty >= L ){
        return 0;
    }
    int i = 1;
    int mid = T->num_mcq_questions;
    while(1){
        if( T->mcq_questions[i-1]->difficulty < L && T->mcq_questions[i]->difficulty >= L ){
            return i;
        }
        if( T->mcq_questions[i]->difficulty >= L ){
            mid /= 2;
            i -= mid;
        }
        else if( T->mcq_questions[i]->difficulty < L ){
            mid /= 2;
            i += mid;
        }
    }
}

int BinarySearch_UpperBound( ParsedTree* T , double U ){
    if( T->mcq_questions[T->num_mcq_questions-1]->difficulty <= U ){
        return T->num_mcq_questions-1;
    }
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
            mid /= 2;
            i -= mid;
        }
        else if( T->mcq_questions[i]->difficulty <= U ){
            mid /= 2;
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
    srand( time( NULL ) );
    bool* Disp = ( bool* ) malloc( NumQuestions * sizeof( bool ) );
    int NumDisp = 0;
    int Question;
    ///int Up = BinarySearch_UpperBound( T , U );
    int Lw = BinarySearch_LowerBound( T , L );
    int Uw = BinarySearch_UpperBound(T, U);
    int difference = Uw - Lw;
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
