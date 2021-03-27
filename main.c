#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

// Function declarations
void evaluate(char currentChar);
int isOperator(char symbol);
int isOperand(char symbol);
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
        while (!isEmpty(top) && top->data != '(') { // isEmpty to avoid segmentation fault
            printf("%c", pop(&top));
        }
        
        // If no left parenthesis return with failure
        if (!isEmpty(top) && top->data != '(') {
            puts("\nInvalid Expression!");
            exit(0);
        }

        // to avoid printing pushed paranthesis
        pop(&top);

    }

    // if current token is an operand, prints it
    else if ( isOperand(currentChar) )
        printf("%c", currentChar);

    // If an operator
    // a. If empty stack or token has a higher precedence than the top stack element,
    // push token and go to 2.i
    // b. Else pop and place in the incomplete postfix expression and go to c
    else {
        if (isEmpty(top) || getPriority(currentChar) > getPriority(top->data))
            push(&top,currentChar);
        else {
            printf( "%c", pop(&top) );
            evaluate(currentChar); // recursively goes to c
        }

    }
            
}

int isOperand(char symbol) {
    /*
        Checks is symbol is operand.
        An operand can be either a digit or an alphabetic character
    */
    return isdigit(symbol) || isalpha(symbol);
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
    char infixExpression[] =  "1+B/3+5*(9-a)";

    int i;
    for (i = 0; i < strlen(infixExpression); i++) { // While not EOArithmeticExpression
        evaluate((infixExpression[i]));
    }

    char poppedValue;

    while (!isEmpty(top)) {
        poppedValue = pop(&top);
        if (poppedValue != '(' || poppedValue != ')') // dont print paratheses
            printf("%c", poppedValue);

    }
        

	return 0;
}


