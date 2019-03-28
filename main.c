#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

void printLL(node *head) {
    node *curr = head;
    while(curr != NULL) {
        printf("%d\t", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int newMethodTest(){
    return 1;
}

node* createList(int n) {
    int i = 0;
    node *temp;
    node *head = NULL;
    node *tail = NULL;
//    node *mainList;

    for(i = 0; i < n; i++) {
        printf("inside\n");
        temp = (node*)malloc(sizeof(node));
        printf("Please enter a number to add: \n");
        scanf(" %d", &(temp->data));
        temp->next = NULL;
        printf("the num is: %d\n", temp->data);
        printf("head is: %p\n", head);
//
        if(head == NULL) {
            printf("inside if");
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
    }
    return head;
}

int main() {
    int nodes = 0;
    printf("How many nodes would you like to add? ");
    scanf("%d", &nodes);

    node *new = createList(nodes);
    printLL(new);
    return 0;
}