#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

StackNodePtr top;

void evaluate(char symbol) {
    /*
        Evaluates given symbol.
    */

    printf("%c", symbol);

}

int isLeftAssociative(char symbol) {
    /*
        If given symbol left to right associative returns 1
        If given symbol right to left associative returns 0
    */
    int isLeft = 0;

    if (symbol=='+' || symbol=='-' || symbol=='*' || symbol=='/')
        isLeft = 1;

    return isLeft;

}

int getPriority(char symbol) {
    /*
        Returns the priority of given symbol.
        + -   returns 1
        * /   returns 2

        If given symbol is not an operator, returns 0
    */
    int priority = 0;

    if (symbol=='+' || symbol=='-')
        priority = 1;
    else if (symbol=='*' || symbol=='/')
        priority = 2;

    return priority;
}


int main() {
    char example_input[] = "A/(B+C)";
    int len = strlen(example_input);

    for (int i=0; i<len; i++)
        evaluate(example_input[i]);

    return 0;
}


