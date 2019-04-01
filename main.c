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
//        strcpy(temp->data.str, newData);
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
//        printf("Enter 1 to add a value and 2 to add a list");
//        char inputData1[MAX_INPUT];
//        char *inputPtr = inputData1;
//        fgets(inputPtr, MAX_INPUT, stdin);
//        inputPtr[strcspn(inputPtr, "\n")] = 0;
////        int userInput = (int)(inputPtr);
//        int userInput = strtol(inputData1, NULL, 10);
//        printf("the input ptr is: %s\n", inputPtr);
//        printf("the use input is: %d\n", userInput);
//        if(userInput == 2) {
//            currNode = createListWrapper();
//        }
//        else {
            printf("Please enter a value to add: ");
            char inputData[MAX_INPUT];
            char *newData = inputData;
            fgets(newData, MAX_INPUT, stdin);
            newData[strcspn(newData, "\n")] = 0; // removes new line from fgets buffer
            currNode = createNode(newData);
//        }

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
 * inserts new element into list
 * @param head head of the list to insert into
 * @param idx position to insert at
 * @param str data of new node
 * @return head of list inserted into
 */
node* insertNode(node *head, node* elem, int idx) {
    node *curr = head;
    while(curr != NULL) {
        printf("curr is: %s\n", curr->dataStr);
        printf("index is: %d\n", idx);

        if(idx == 0) {
            elem->next = head;
            return elem;
        }
        else if(idx - 1 == 0) {
            printf("curr and elem %s\t%s\n", curr->dataStr, elem->dataStr);
            node *temp = curr->next;
            curr->next = elem;
            elem->next = temp;
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

node* getNode(int pos, node* head) {
    node *curr = head;
    while(pos != 0) {
        if(curr == NULL) return NULL;
        curr = curr->next;
        pos --;
    }
    return curr;
}

node* sort(node *head) {
    node *newHead = head;
    node *curr = head;
    node *prev = curr;
    node *prevCurr = NULL;
    int pos = 0;
    int minIdx = 0;
    while(curr != NULL) {
        printf("inside while\n");
        printf("curr is: %s\n", curr->dataStr);
        node *min = curr;
        int innerIdx = pos;
        if(curr->next != NULL) {
            node *innerPrev = curr;
            node *next = curr->next;
            while(next != NULL) {
                innerIdx++;
                printf("inside inner while\n");
                printf("next is: %s\n", next->dataStr);
                int compare = strcmp(min->dataStr, next->dataStr);
                if(compare > 0) {
                    min = next;
                    prev = innerPrev;
                    minIdx = innerIdx;
                }
                next = next->next;
                if(next != NULL) innerPrev = innerPrev->next;
            }
        }
        printf("the previous is: %s\n", prev->dataStr);
        printf("the min is: %s\n", min->dataStr);
        if(min != curr) {
            prev->next = min->next;
            node *inserted = insertNode(head, min, pos);
            if(pos == 0) newHead = inserted;
            newHead->next = curr->next;
            printf("inside if %s\n", curr->dataStr);
            printf("MIN IDX is: %d\n", minIdx);
            curr->next = NULL;

            insertNode(newHead, curr, minIdx);
        }
        pos++;
        prevCurr = curr;
        curr = curr->next;
    }
    return newHead;
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
//    char userInput[MAX_INPUT];
//    int nodes = 0;
//
//    printf("How many nodes would you like to add? ");
//    fgets(userInput, MAX_INPUT, stdin);
//
//    nodes = atoi(userInput);
//    node *new = createList(nodes);
////
////    printf("How many nodes would you like for the second list? ");
////    fgets(userInput, MAX_INPUT, stdin);
////
////    nodes = atoi(userInput);
////    node *second = createList(nodes);

    node *new = createListWrapper();

//    node *one;
//    node *two;
//    int oneNum = 6;
//    int *onePtr = &oneNum;
//    int twoNum = 5;
//    int *twoPtr = &twoNum;
//    two = &(node){.data = twoPtr, .dataStr = "5", .type = 1, .next = NULL};
//    one = &(node){.data = onePtr, .dataStr = "6", .type = 1, .next = two};

    printLL(new);

//    node *sorted = sort(new);

//    printLL(sorted);

//    node *newHead = insert(new, 2, "[1,2,3,4]");
//    node *newHead = append(new, "54321");
//    node *newHead = concat(new, second);

//    printLL(newHead);

    return 0;
}
