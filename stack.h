/* Cem Anaral 150119761 */

struct StackNode {
    int data;
    struct StackNode *next;
};

typedef struct StackNode StackNode;
typedef StackNode * StackNodePtr;

int isEmpty(StackNodePtr top) {
    /*
        If stack is empty returns 1, else 0.
    */
    return top == NULL;
}

int push(StackNodePtr *top, int newData) {
    /*
       Creates new node and pushes with provided newData. (i.e. node creation is encapsulated)
       Returns int to indicate whether push is succesfull or not.
       0: push failed
       1: push succesfull
    */

    StackNodePtr newNode = malloc(sizeof(StackNode));

    if (newNode == NULL) // if newNode creation fails (if no memory left)
        return 0;

    // Push operation starts here.
    newNode->data = newData;
    newNode->next = *top;
    *top = newNode;

    return 1;
}

int pop(StackNodePtr *top) {
    /*
        Pops top node and returns its data
    */
    StackNodePtr temp; // to free memory
    int poppedData;

    temp = *top;
    poppedData = (*top)->data;
    *top = (*top)->next;
    free(temp);

    return poppedData;
}

void printStack(StackNodePtr currentNode) {
    /*
        Prints stack elements to terminal.
    */

    if ( !isEmpty(currentNode) ) { //  If stack is not empty

        while (currentNode != NULL) { // Runs until encountering last element
            printf("%d -> ", currentNode->data);
            currentNode = currentNode->next;
        }

    }

    puts("NULL");
    puts("^");
    puts("|");
    puts("top\n");
}
