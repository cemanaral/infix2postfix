#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

// Function declarations
void evaluate(char currentChar);
int isOperator(char symbol);
int isLeftAssociative(char symbol);
int getPriority(char symbol);

/////////

StackNodePtr top = NULL;

void evaluate(char currentChar) {
    int i;

    if ( isdigit(currentChar) )
        printf("%c", currentChar);

    else if (currentChar == '(')
        push(&top, currentChar);

    else if (currentChar == ')') {
        while (!isEmpty(top) && top->data != '(')
            printf("%c", pop(&top));
        pop(&top);
    }

    else {
        while (!isEmpty(top) && getPriority(currentChar) <= getPriority(top->data) )
            printf("%c",  pop(&top));

        push(&top, currentChar);
    }
            
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
    char infixExpression[] =  "1+2/3";
    // evaluate(infix);
    int i;
    for (i = 0; i < strlen(infixExpression); i++) {
        evaluate((infixExpression[i]));
        // printf("%c ", infixExpression[i]);
    }

    while (!isEmpty(top))
        printf("%c", pop(&top));

	return 0;
}


