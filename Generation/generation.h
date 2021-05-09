#ifndef __GENERATION_H
#define __GENERATION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "../ADT/adt.h"


int BinarySearch_LowerBound( ParsedTree* T , double L );
int BinarySearch_UpperBound( ParsedTree* T , double U );
void RandDisplay(McqQuestion *question);
void display_mcq_question(McqQuestion *question, int Serial_number);
void ChooseQuestions( ParsedTree* T , double U , double L , int NumQuestions );

#endif
