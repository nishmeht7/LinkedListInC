#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helper.h"

#define MAX_INPUT 100

node* createList();
node* createListWrapper();


void printString(node *value) {
    printf("\"");
    printf("%s", value->dataStr);
    printf("\"");
}

/**
 * prints a nested list with the format of array brackets
 * @param head node of nested list to be printed
 */
void printNestedList(node *head) {
    printf("[");
    while(head != NULL) {
        while(head != NULL) {
            if(head->type == 3) {
                printString(head);
            }
            else {
                printf("%s", head->dataStr);
            }
            head->next == NULL ? printf("") : printf(",\t");
            head = head->next;
        }
    }
    printf("]\t");
}

/**
 * prints a linked list
 * @param head first node of the list
 */
void printLL(node *head) {
    while(head != NULL) {
        if(head->type == 4) {
            printNestedList(head->data);
        }
        else if(head->type == 3) {
            printString(head);
        }
        else {
            printf("%s\t", head->dataStr);
        }
        head->next == NULL ? printf("") : printf(",\t");
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
            temp->data = &d;
            temp->type = 2;
        }
        else {
            temp->data = &i;
            temp->type = 1;
        }
    }
    else {
        temp->data = newData;
        temp->type = 3;
    }
    return temp;
}

/**
 * function to create a nested list
 * @return head node of nested list
 */
node* createNestedList() {
    node *temp = (node*)malloc(sizeof(node));

    temp->data = createListWrapper();
    temp->type = 4;
    return temp;
}

/**
 * wrapper method to create a list
 * @return the head node of the newly created list
 */
node* createListWrapper() {
    char userInput[MAX_INPUT];
    int nodes = 0;
    printf("How many nodes would you like to add? \n");
    fgets(userInput, MAX_INPUT, stdin);
    userInput[strcspn(userInput, "\n")] = 0; // removes new line from fgets buffer
    nodes = strtol(userInput, NULL, 10);
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
//        printf("(inside list)\n");
        char userInput[MAX_INPUT];
        char *inputPtr = userInput;
        printf("Enter 1 to enter a value, or 2 to add a nested list\n");
        fgets(inputPtr, MAX_INPUT, stdin);
        inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
        int choice = strtol(inputPtr, NULL, 10);
//        printf("the choice is: %d\n", choice);
        if(choice == 2) {
            currNode = createNestedList();
        }
        else {
            printf("Please enter a value to add: \n");
            char inputData[MAX_INPUT];
            char *newData = inputData;
            fgets(newData, MAX_INPUT, stdin);
            newData[strcspn(newData, "\n")] = 0; // removes new line from fgets buffer
//            printf("NEW DATA ENTERED: %s\n", newData);
            currNode = createNode(newData);
        }
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

    if (head == NULL && idx == 0){
        return newNode;
    }
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
        if(curr->type != 4) {
            int cmp = strcmp(curr->dataStr, min->dataStr);
            if (cmp < 0){
                min = curr;
            }
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
 * Modifies linked list node at specified index
 * @param head linked list head
 * @param indexToInsert index to change value
 * @param data data to insert
 * @return head of linked list
 */
void get(node *head, int indexToFind){
    int index = 0;
    node *curr = head;
    char userInput[20];
    char *inputPtr = userInput;
    int choice = 0;

    while(curr != NULL) {
        if (index == indexToFind){
            if(curr->type == 4) {
                printf("Please enter an index to access the nested array: \n");
                fgets(inputPtr, MAX_INPUT, stdin);
                choice = strtol(inputPtr, NULL, 10);
                get(curr->data, choice);
            }
            else {
                printf("The value at index %d is:\n %s\n", indexToFind, curr->dataStr);
            }
            return;
        }
        index++;
        curr = curr->next;
    }
    printf("There was not a value at that index\n");
}
/**
 * helper method for insertion sort
 * @param headOfSorted sorted part of the list
 * @param toInsert  new element to insert
 * @return head of newly sorted list
 */
node* insertNodeIntoSorted(node *headOfSorted, node *toInsert) {
    printf("inside insert node: %s\n", toInsert->dataStr);
    if(toInsert->type == 4) return toInsert;
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
//        printf("outside while curr is: %s\n", curr->dataStr);
        node *next = curr->next;
        if(curr->type == 4) {
            strcpy(curr->dataStr, "");
        }
        curr->next = NULL;
        newlySorted = insertNodeIntoSorted(headOfSorted,curr);
        headOfSorted = newlySorted;
        curr = next;
    }
//    printf("the head of sorted is: %s\n", headOfSorted->dataStr);
    return headOfSorted;
}

/**
 * program main function
 * @return
 */
int main() {

    int inputCorrect = 0;
    int quit = 0;
    int singleListMenu = 0;
    int input;
    int menu;
    node *list = NULL;
    int nodes = 0;

    char userInput[MAX_INPUT];
    char *inputPtr = userInput;
//
//<<<<<<< HEAD
//
//    node *newHead = createListWrapper();
//
//    printLL(newHead);
//    node *minNode = min(newHead);
//    printf("min: %s\n", minNode->dataStr);
//
//    node *maxNode = max(newHead);
//    printf("max: %s\n", maxNode->dataStr);
//
//    printf("sorted linked list:\n");
//    node *sortedHead = insertionSort(newHead);
//    printLL(sortedHead);
//=======

    printf("Welcome to the Linked List program.\n");
    while (quit == 0){
        inputCorrect = 0;
        singleListMenu = 0;
        while (inputCorrect == 0){
            printf("\nEnter 1 to work with one list.\n");
            printf("Enter 2 to concat two lists.\n");
            printf("Enter 3 to quit.\n");

            fgets(inputPtr, MAX_INPUT, stdin);
            inputPtr[strcspn(inputPtr, "\n")] = 0;
            menu = strtol(inputPtr, NULL, 10);

            if (menu == 1){
                inputCorrect = 1;
                singleListMenu = 1;
            }
            else if (menu == 2) {
                inputCorrect = 1;

                printf("How many nodes would you like to add to the first list? \n");

                fgets(inputPtr, MAX_INPUT, stdin);
                inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
                nodes = strtol(inputPtr, NULL, 10);

                node *firstHead = createList(nodes);

                printf("How many nodes would you like for the second list? \n");

                fgets(inputPtr, MAX_INPUT, stdin);
                inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
                nodes = strtol(inputPtr, NULL, 10);

                node *secondHead = createList(nodes);

                node *newHead = concat(firstHead, secondHead);
                printf("The concatenated list: \n");
                printLL(newHead);
            }
            else if (menu == 3){
                printf("Exiting the program...\n");
                inputCorrect = 1;
                quit = 1;

            }
            else {
                printf("Please enter a valid menu input.\n");
            }
        }
        while (singleListMenu == 1 && quit == 0){
            inputCorrect = 0;
            printf("Welcome to the single list section.\n");
            printf("Enter 1 to print the current list.\n");
            printf("Enter 2 to add an element.\n");
            printf("Enter 3 to modify an element.\n");
            printf("Enter 4 to print the max value.\n");
            printf("Enter 5 to print the minimum value.\n");
            printf("Enter 6 to sort the list.\n");
            printf("Enter 7 to reverse the list.\n");
            printf("Enter 8 to print a specific element.\n");
            printf("Enter 9 to determine the length.\n");
            printf("Enter 10 to insert an element at a specific index.\n");
            printf("Enter 0 to go back to main menu.\n");

            char secondInput[20];
            char *newPtr = secondInput;
            int newInt;
            fgets(newPtr, MAX_INPUT, stdin);
            newPtr[strcspn(newPtr, "\n")] = 0; // removes new line from fgets buffer
            menu = strtol(newPtr, NULL, 10);


            if (menu > -1 && menu < 12){
                if (menu == 1){
                    printf("The list currently: \n");
                    printLL(list);
                }
                else if (menu == 2){
                    node *newNode = createList(1);
                    list = concat(list, newNode);
                    printf("The list currently: \n");
                    printLL(list);
                }
                else if (menu == 3){

                    printf("What node would you like to modify (index starts at 0)? \n");
                    fgets(inputPtr, MAX_INPUT, stdin);
                    inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
                    int modifyIndex = atoi(inputPtr);

                    printf("What value would you like that node to be? \n");
                    fgets(inputPtr, MAX_INPUT, stdin);
                    inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
                    list = modify(list, modifyIndex, inputPtr);
                    printf("new linked list after modification:\n");
                    printLL(list);
                }
                else if (menu == 4){
                    printf("The maximum value is: \n");
                    printf("%s\n", max(list)->dataStr);
                }
                else if (menu == 5){
                    printf("The minimum value is: \n");
                    printf("%s\n", min(list)->dataStr);
                }
                else if (menu == 6) {
                    printf("The list is now sorted: \n");
//                    list = insertionSort(list);
                    node *sorted = insertionSort(list);
                    list = sorted;
                    printLL(list);
                }
                else if (menu == 7){
                    printf("The list is now reversed: \n");
                    list = reverse(list);
                    printLL(list);
                }
                else if (menu == 8){
                    printf("What element would you like to print? \n");
                    fgets(inputPtr, MAX_INPUT, stdin);
                    inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
                    input = strtol(inputPtr, NULL, 10);
                    get(list, input);
                }
                else if (menu == 9){
                    printf("The length of the list is %d\n", getLen(list));
                }
                else if (menu == 10) {
                    printf("What index would you like to insert at (index starts at 0)? \n");
                    fgets(inputPtr, MAX_INPUT, stdin);
                    inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer
                    int insertIndex = atoi(userInput);

                    printf("What value would you like that node to be? \n");
                    fgets(inputPtr, MAX_INPUT, stdin);
                    inputPtr[strcspn(inputPtr, "\n")] = 0; // removes new line from fgets buffer

                    list = insert(list, insertIndex, inputPtr);
                    printLL(list);
                }
                else if (menu == 0){
                    singleListMenu = 0;
                }
            }
            else {
                printf("Please enter a valid input\n");
            }
        } // (while singleListMenu == 1 && quit == 0)
    }
}
