#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"

#define MAX_INPUT 100

void printLL(node *head) {
    node *curr = head;
    while(curr != NULL) {
        printf("%s\t", &curr->dataStr);
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

    if(sscanf(newData, "%lf", &d) == 1) {
        i = (int)d; // typecast to int.
        if (fabs(d - i) / d > tolerance) {
            printf("The input is a floating point\n");
            temp->data.d = d;
            temp->type = 2;
        }
        else {
            printf("The input is an integer\n");
            temp->data.i = i;
            temp->type = 1;
        }
    }
    else {
        printf("The input is a string\n");
        strcpy(temp->data.str, newData);
        temp->type = 3;
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
        newData[strcspn(newData, "\n")] = 0; // removes new line from fgets buffer
        currNode = createNode(newData);

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