#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"

#define MAX_INPUT 100

node* createList();
node* createListWrapper();

/**
 * prints a linked list
 * @param head first node of the list
 */
void printLL(node *head) {
    while(head != NULL) {
        printf("%s\t", head->dataStr);
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
            temp->data = &d;
            temp->type = 2;
        }
        else {
            printf("The input is an integer\n");
            temp->data = &i;
            temp->type = 1;
        }
    }
    else {
        printf("The input is a string\n");
        temp->data = newData;
        temp->type = 3;
    }
    return temp;
}

node* createListWrapper() {
    char userInput[MAX_INPUT];
    int nodes = 0;

    printf("How many nodes would you like to add? ");
    fgets(userInput, MAX_INPUT, stdin);
    nodes = strtol(userInput, NULL, 10);
    printf("nodes are: %d\n", nodes);
    return createList(nodes);
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
<<<<<<< HEAD
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
 * Finds minimum value in linked list
 * @param list head of linked list
 * @return node that has the minimum value
 */
node* min(node *list){
    node *curr = list;
    node *min = list;
    if(list == NULL) return list;
    while(curr != NULL) {
        int cmp = strcmp(curr->dataStr, min->dataStr);
        if (cmp < 0){
            min = curr;
        }
        curr = curr->next;
    }
    return min;
}

/**
 * Finds minimum value in linked list
 * @param list head of linked list
 * @return node that has the minimum value
 */
node* max(node *list){
    node *curr = list;
    node *max = list;
    if(list == NULL) return list;
    while(curr != NULL) {
        int cmp = strcmp(curr->dataStr, max->dataStr);
        if (cmp > 0){
            max = curr;
        }
        curr = curr->next;
    }
    return max;
}

/**
 * Method to reverse linked list recursively
 * @param head head of linked list
 * @return tail that is inserted in front of list
 */
node* reverse(node *head){
    node *previous = NULL;
    node *curr = head;
    node *next = NULL;

    while (curr != NULL){

        next = curr->next;
        curr->next = previous;
        previous = curr;
        curr = next;
    }
    return previous;
}

/**
 * Modifies linked list node at specified index
 * @param head linked list head
 * @param indexToInsert index to change value
 * @param data data to insert
 * @return head of linked list
 */
node* modify(node *head, int indexToInsert, char *data){
    node *newNode = createNode(data);
    node *curr = head;

    if (indexToInsert == 0){
        newNode->next = curr->next;
        return newNode;
    }
    int index = 1;
    while(curr->next != NULL) {
        if (index == indexToInsert){
            newNode->next = curr->next->next;
            curr->next = newNode;
            return head;
        }
        index++;
        curr = curr->next;
    }
    //insert at tail
    if (index == indexToInsert){
        curr->next = newNode;
    }

    return head;
}

/**
 * helper method for insertion sort
 * @param headOfSorted sorted part of the list
 * @param toInsert  new element to insert
 * @return head of newly sorted list
 */
node* insertNodeIntoSorted(node *headOfSorted, node *toInsert) {

    if (headOfSorted == NULL){
        return toInsert;
    }
    int cmp;
    // sorts integers using a strncmp which correctly sorts integers with multiple digits
    if(headOfSorted->type == 1 && toInsert->type == 1) {
        cmp = strncmp(headOfSorted->dataStr, toInsert->dataStr, MAX_INPUT);
    }
    else {
        cmp = strcmp(headOfSorted->dataStr, toInsert->dataStr);
    }
    if (cmp > 0){
        //insert at front
        toInsert->next = headOfSorted;
        return toInsert;
    }
    node* curr = headOfSorted;
    while (cmp < 0 && curr->next != NULL){
        cmp = strcmp(curr->next->dataStr, toInsert->dataStr);
        if(cmp < 0) curr = curr->next;
    }
    toInsert->next = curr->next;
    curr->next = toInsert;
    return headOfSorted;
}

/**
 * insertion sort alogortithm to sort a list
 * @param list - list to be sorted
 * @return sorted head of list
 */
node* insertionSort(node *list){

    node *headOfSorted = NULL; //Start with empty list
    node *curr = list;
    node *newlySorted = NULL;
    while (curr != NULL){
        printf("outside while curr is: %s\n", curr->dataStr);
        node *next = curr->next;
        curr->next = NULL;
        newlySorted = insertNodeIntoSorted(headOfSorted,curr);
        headOfSorted = newlySorted;
        curr = next;
    }
    return headOfSorted;
}

/**
 * program main function
 * @return
 */
int main() {
    char userInput[MAX_INPUT];
    char *inputPtr = userInput;
    int nodes = 0;

    printf("How many nodes would you like to add? \n");
    fgets(userInput, MAX_INPUT, stdin);

    nodes = strtol(userInput, NULL, 10);
    node *newHead = createList(nodes);
//
//    printf("How many nodes would you like for the second list? \n");
//    fgets(userInput, MAX_INPUT, stdin);
//
//    nodes = atoi(userInput);
//    node *second = createList(nodes);
//
//    printLL(new);

//    node *newHead = insert(new, 2, "[1,2,3,4]");
//    node *newHead = append(new, "54321");
//    node *newHead = concat(new, second);

    printLL(newHead);
    node *minNode = min(newHead);
    printf("min: %s\n", minNode->dataStr);

    node *maxNode = max(newHead);
    printf("max: %s\n", maxNode->dataStr);

//    printf("What node would you like to modify (index starts at 0)? \n");
//    fgets(userInput, MAX_INPUT, stdin);
//
//    int modifyIndex = atoi(userInput);
//
//    printf("What value would you like that node to be? \n");
//    fgets(userInput, MAX_INPUT, stdin);
//
//    newHead = modify(newHead, modifyIndex, userInput);
//
//    printf("new linked list after modification:\n");
//    printLL(newHead);
//
//    printf("reversed linked list:\n");
//    newHead = reverse(newHead);
//    printLL(newHead);

    printf("sorted linked list:\n");
    newHead = insertionSort(newHead);
    printLL(newHead);

}
