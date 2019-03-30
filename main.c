#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"

#define MAX_INPUT 100

void printLL(node *head) {
    node *curr = head;
    while(curr != NULL) {
        printf("%s", curr->dataStr);
        curr = curr->next;
    }
    printf("\n");
}

node* createNode(char *newData) {
    int i;
    double d;
    double tolerance = 1e-12;
    node *temp = (node*)malloc(sizeof(node));
    strcpy(temp->dataStr, newData);
    printf("the string is: %s\n", temp->dataStr);
    if(sscanf(newData, "%lf", &d) == 1) {
        i = (int)d; // typecast to int.
        if (fabs(d - i) / d > tolerance) {
            temp->data.d = d;
            printf("The input is a floating point\n");
        }
        else {
            temp->data.i = i;
            printf("The input is an integer\n");
        }
    }
    else {
        strcpy(temp->data.str, newData);
    }
    return temp;
}

node* createList(int n) {
    int i = 0;
    node *currNode;
    node *head = NULL;
    node *tail = NULL;

    for(i = 0; i < n; i++) {
        printf("(inside list)\n");
        printf("Please enter a value to add: ");
        char inputData[MAX_INPUT];
        char *newData = inputData;
        fgets(newData, MAX_INPUT, stdin);
        currNode = createNode(newData);
        printf("the data is: %s\n", currNode->data.str);

        if(head == NULL) {
            head = currNode;
            tail = currNode;
        }
        else {
            tail->next = currNode;
            tail = currNode;
        }
    }
    return head;
}

//TODO print, append(data), getLength, insert(index, data), modify(index, data)
//TODO min, max, concat, reverse, sort (selection)

//TODO Nishant: print, append, concat, insert
//TODO Fred: min, max, modify

int main() {
    char userInput[MAX_INPUT];
    int nodes = 0;

    printf("How many nodes would you like to add? ");
    fgets(userInput, MAX_INPUT, stdin);

    nodes = atoi(userInput);
    node *new = createList(nodes);

    printLL(new);
    return 0;
}