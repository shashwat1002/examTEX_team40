#include <stdio.h>
#include <stdlib.h>
#include "my_stack.h"

ptr_to_element CreateStackElement(ElementType *X)
{
    ptr_to_element New = (ptr_to_element)malloc(sizeof(stack_element));
    ///New->data.Re = X->Re;
    ///New->data.Im = X->Im;
    New->data = *X;
    New->next = NULL;
}

void Push(Stack *SP, ElementType *X)
{
    ptr_to_element P_New = CreateStackElement(X);
    ptr_to_element *P = SP;
    ptr_to_element K = *P;
    *P = P_New;
    P_New->next = K;
}

void Pop(Stack *SP)
{
    ptr_to_element *P = SP;
    ptr_to_element K = *P;
    if (K != NULL)
    {
        *P = K->next;
    }
    else
    {
        *P = NULL;
        printf("The stack is empty.\n");
    }
}

void PrintStack(Stack *SP)
{
    ptr_to_element *P = SP;
    ptr_to_element K = *P;
while (K != NULL)
    {
        printf("%c", K->data);
        K = K->next;
        if (K != NULL)
        {
            printf("--");
        }
    }
    printf("\n");
}
