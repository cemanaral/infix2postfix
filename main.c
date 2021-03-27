#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

// Function declarations
void evaluate(char currentChar);
int isOperator(char symbol);
int getPriority(char symbol);
/////////

StackNodePtr top = NULL; // 1. Initialize an operand stack

void evaluate(char currentChar) {
    /*
        Evaluates given symbol using Infix to Postfix conversion rules.
    */

    // ‘(’: Push; // assume the lowest precedence for ‘(’
    if (currentChar == '(')
        push(&top, currentChar);


    // ‘)’: Pop and place token in the incomplete postfix expression until a left '('
    //      parenthesis is encountered;
    else if (currentChar == ')') {

        if (!isEmpty(top)) { // isEmpty is for avoiding segmentation fault
            int leftParanthesisCount = 0; // to invalid expression check
        
            while (!isEmpty(top) && top->data != '(') {
                printf("%c", pop(&top));
                leftParanthesisCount++; 
            }
        
            if (leftParanthesisCount == 0) { // If no left parenthesis return with failure
                puts("Invalid expression !!");
                exit(-1);
            }
        }
    }

    // if an operand, prints it
    else if ( isdigit(currentChar) )
        printf("%c", currentChar);

    // If an operator
    // a. If empty stack or token has a higher precedence than the top stack element,
    // push token and go to 2.i
    // b. Else pop and place in the incomplete postfix expression and go to c
    else {
        while ( !isEmpty(top) // isEmpty is for avoiding segmentation fault
                && getPriority(currentChar) <= getPriority(top->data) )
        {
            printf("%c",  pop(&top));
        }

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
    char infixExpression[] =  "1+2/3+5*4";

    int i;
    for (i = 0; i < strlen(infixExpression); i++) { // While not EOArithmeticExpression
        evaluate((infixExpression[i]));
    }

    while (!isEmpty(top))
        printf("%c", pop(&top));

	return 0;
}


