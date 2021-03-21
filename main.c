#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

// Function declarations
void evaluate(char symbol);
int isOperator(char symbol);
int isLeftAssociative(char symbol);
int getPriority(char symbol);
/////////

StackNodePtr top = NULL;

void evaluate(char symbol) {
    /*
        Evaluates given symbol using Infix to Postfix conversion rules.
    */

    // ‘(’: Push; //assume the lowest precedence for ‘(’
    if (symbol=='(') {
        push(&top, symbol);
    }

    // ‘)’: Pop and place token in the incomplete postfix expression until a left
    //      parenthesis is encountered;
    else if (symbol==')') {
        // TODO!!
    }

    // If an operator
    else if (isOperator(symbol)) {

        // If empty stack or token has a higher precedence than the top stack element,
        // push token and go to 2.i
        if ( isEmpty(top) ||  getPriority(symbol) <= getPriority( (char)(top->data) ) ) {
            push(&top, symbol);
        }

        // Else pop and place in the incomplete postfix expression and go to c
        else {
            printf("%c ", (char)pop(&top));
        }

    }

    // If an operand
    else if (isdigit(symbol)) {
        printf("%c ", symbol);
    }

} // end of evaluate()

int isOperator(char symbol) {
    /*
        Returns 1 if symbol is operator, else 0
    */
    if (symbol=='+' || symbol=='-' || symbol=='*'
        || symbol=='/' || symbol=='^')
        return 1;

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
    char example_input[] = "1 / 5 + 6";
    int len = strlen(example_input);

    for (int i=0; i<len; i++)
        evaluate(example_input[i]);


    // If EOArithmeticExpression
    // Pop and place token in the incomplete
    // postfix expression until stack is empty
    while (!isEmpty(top))
        printf("%c ", pop(&top));

    printf("\n");
    return 0;
}


