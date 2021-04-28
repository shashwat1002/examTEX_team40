///#include "complex.h"
#ifndef __MY_STACK_
#define __MY_STACK_

typedef char ElementType;

typedef struct stack_element stack_element;
typedef struct stack_element* ptr_to_element;
typedef struct stack_element* Stack;

struct stack_element{
    ElementType data;
    ptr_to_element next;
};


void Push( Stack* S , ElementType* X );
void Pop( Stack* S );
void PrintStack( Stack* S );

#endif
