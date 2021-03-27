#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

// Function declarations
void evaluate(char* infix);
int isOperator(char symbol);
int isLeftAssociative(char symbol);
int getPriority(char symbol);

/////////

StackNodePtr top = NULL;

void evaluate(char* infix) {
    int i;
    int k;

    for (i=0, k=-1; infix[i]; i++) {
        if ( isdigit(infix[i]) )
            infix[++k] = infix[i];

        else if (infix[i] == '(')
            push(&top, infix[i]);

        else if (infix[i] == ')') {
            while (!isEmpty(top) && top->data != '(')
                infix[++k] = pop(&top);
            pop(&top);
        }

        else {
            while (!isEmpty(top) && getPriority(infix[i]) <= getPriority(top->data) )
                infix[++k] = pop(&top);

            push(&top, infix[i]);
        }
            
    }

    while (!isEmpty(top))
        infix[++k] = pop(&top);

    infix[++k] = '\0';
    printf("%s", infix);

}



int isOperator(char symbol) {
    /*
        Returns 1 if symbol is operator, else 0
    */
    if (symbol=='+' || symbol=='-' || symbol=='*' || symbol=='/' || symbol=='^') {
        return 1;
    }

    return 0;
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
        ^     returns 3
        If given symbol is not an operator, returns 0
    */
    int priority = 0;

    if (symbol=='+' || symbol=='-')
        priority = 1;
    else if (symbol=='*' || symbol=='/')
        priority = 2;
    else if (symbol == '^')
        priority = 3;

    return priority;
}


int main() {
    char infix[] =  "1+2/3";
    evaluate(infix);
	return 0;
}


