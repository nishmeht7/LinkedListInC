#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"

#define MAX_INPUT 100

/**
 * prints a linked list
 * @param head first node of the list
 */
void printLL(node *head) {
    while(head != NULL) {
        printf("%s\t", &head->dataStr);
        head = head->next;
    }
    printf("\n");
}

/**
 * returns the length of a list
 * @param head list to check length of
 * @return length of list
 */
int getLen(node *head) {
    int len = 0;
    while(head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

/**
 * creates a node with the given data by determining data type
 * @param newData int string format
 * @return the newly created node
 */
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

/**
 * user enabled creation of a new linked list
 * @param n number of nodes to start with
 * @return head to the newly created list
 */
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

/**
 * inserts new element into list
 * @param head head of the list to insert into
 * @param idx position to insert at
 * @param str data of new node
 * @return head of list inserted into
 */
node* insert(node *head, int idx, char *str) {
    node *curr = head;
    node *newNode = createNode(str);
    while(curr != NULL) {
        if(idx == 0) {
            newNode->next = head;
            return newNode;
        }
        else if(idx - 1 == 0) {
            node *temp = curr->next;
            curr->next = newNode;
            newNode->next = temp;
            break;
        }
        idx--;
        curr = curr->next;
    }
    return head;
}

/**
 * appends an item to the end of the list
 * @param head first node of list to be appended to
 * @param data the data for the new node that is created and appended
 * @return head of the newly appended to list
 */
node* append(node *head, char *data) {
    node *curr = head;
    node *newNode = createNode(data);
    if(head == NULL) return newNode;
    if(head->next == NULL) {
        head->next = newNode;
        return head;
    }
    while(curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;
}

/**
 * concatenates two lists
 * @param list1 head of list one
 * @param list2 head of list two
 * @return head of newly concatenated list
 */
node* concat(node *list1, node *list2) {
    node *curr = list1;
    if(list1 == NULL) return list2;
    if(list1->next == NULL) {
        list1->next = list2;
        return list1;
    }
    while(curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = list2;
    return list1;
}

//TODO print, append(data), getLength, insert(index, data), modify(index, data)
//TODO min, max, concat, reverse, sort (selection)

//TODO Nishant: print(done), append(done), concat(done), insert(done)
//TODO Fred: min, max, modify, reverse

/**
 * program main function
 * @return
 */
int main() {
    char userInput[MAX_INPUT];
    int nodes = 0;

    printf("How many nodes would you like to add? ");
    fgets(userInput, MAX_INPUT, stdin);

    nodes = atoi(userInput);
    node *new = createList(nodes);

    printf("How many nodes would you like for the second list? ");
    fgets(userInput, MAX_INPUT, stdin);

    nodes = atoi(userInput);
    node *second = createList(nodes);

    printLL(new);

//    node *newHead = insert(new, 2, "[1,2,3,4]");
//    node *newHead = append(new, "54321");
    node *newHead = concat(new, second);

    printLL(newHead);

    return 0;
}