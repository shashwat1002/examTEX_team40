#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

ptr_to_element CreateStackElement(ElementType X)
{
    ptr_to_element New = (ptr_to_element)malloc(sizeof(stack_element));
    ///New->data.Re = X->Re;
    ///New->data.Im = X->Im;
    New->data = X;
    New->next = NULL;
}

void Push(PtrToHeader HS, ElementType X)
{
    // ptr_to_element P_New = CreateStackElement(X);
    // ptr_to_element *P = SP;
    // ptr_to_element K = *P;
    // *P = P_New;
    // P_New->next = K;

    ptr_to_element P = HS->pStack;
    HS->pStack = CreateStackElement(X);
    HS->pStack->next = P;
    HS->number_of_elements++;
}

ElementType Pop(PtrToHeader HS)
{
    // ptr_to_element *P = SP;
    // ptr_to_element K = *P;
    // if (K != NULL)
    // {
    //     *P = K->next;
    // }
    // else
    // {
    //     *P = NULL;
    //     printf("The stack is empty.\n");
    // }

    if (HS->pStack != NULL)
    {
        ptr_to_element P = HS->pStack;
        HS->pStack = HS->pStack->next;
        ElementType E = P->data;
        HS->number_of_elements--;
        free(P);
        return E;
    }
    else
    {
        printf("The stack is empty.\n");
        return -1;
    }
}

void PrintStack(PtrToHeader HS)
{
    // ptr_to_element *P = SP;

    ptr_to_element K = HS->pStack;
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
