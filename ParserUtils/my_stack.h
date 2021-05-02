///#include "complex.h"
#include <stdlib.h>
#ifndef __MY_STACK_
#define __MY_STACK_

typedef char ElementType;

typedef struct stack_element stack_element;
typedef struct stack_element *ptr_to_element;
typedef struct stack_element *Stack;

typedef struct stack_head Header;
typedef struct stack_head *PtrToHeader;

struct stack_head
{
    ptr_to_element pStack;
    int number_of_elements;
};

struct stack_element
{
    ElementType data;
    ptr_to_element next;
};

void Push(PtrToHeader HS, ElementType X);
ElementType Pop(PtrToHeader HS);
void PrintStack(PtrToHeader HS);

#endif
