#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct listNode{
    int val;
    struct listNode *next;
} listNode;

int listSize = 0;

void printList(listNode* head){
    listNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
}

void push(listNode **list, int value){

    if(value < 0 || value > 9){
        printf("Value not accepted!\n");
        return;
    }

    // listNode *node;

    // if (listSize == 0){
    //     node = (listNode*)malloc(sizeof(listNode));
    // }

    listSize++;

    listNode *node = (listNode*)malloc(sizeof(listNode));
    if (node != NULL){
        node->val = value;
        node->next = *list;
        *list = node;
    } else {
        printf("\nFailed to add number to the list!");
    }
}

void resetList(listNode **head){
    listNode *temp = *head, *next;

    while (temp != NULL){
        next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
}

bool isPalindrome(listNode *head){

    if(listSize < 1 || listSize > pow(10, 5)){
        printf("\nNumber of iterations invalid!\n\n");
        return false;
    }
    
    listNode *prev = NULL, *current = head, *next = NULL;
    int original[listSize], i = 0, count = 0;

    while (current != NULL){
        next = current->next;
        current->next = prev;
        original[i] = current->val;
        prev = current;
        current = next;
        i++;
    } 

    head = prev;   
    
    for(i = 0; i < listSize; i++){
        if (original[i] == head->val){
            count++;
        }
        head = head->next;
    }

    free(prev);
    free(current);
    free(next);

    if (count == listSize){
        printf("\nPalindrome\n\n");
        listSize = 0;
        return true; 
    }
    listSize = 0;

    printf("\nNot a palindrome\n\n");
    return false;
}

int main(){
    listNode *head = NULL;

    listSize = 0;
    
    printf("Test 1: \n");
    
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printList(head);
    isPalindrome(head);
    resetList(&head);

    printf("Test 2: \n");
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);

    printList(head);
    isPalindrome(head);
    resetList(&head);

    printf("Test 3: \n");
    
    push(&head, 2);
    push(&head, 2);
    
    printList(head);
    isPalindrome(head);
    resetList(&head);

    printf("Test 4: \n");
    
    push(&head, 1);
    push(&head, 9);
    push(&head, 2);
    push(&head, 2);
    push(&head, 1);
    push(&head, 3);
    push(&head, 7);
    push(&head, 4);
    push(&head, 2);
    push(&head, 2);

    printList(head);
    isPalindrome(head);
    resetList(&head);

    printf("Test 5: \n");
    isPalindrome(head);
    resetList(&head);

    printf("Test 6: \n");

    push(&head, 44);
    push(&head, 3);
    push(&head, 2);
    push(&head, 10);
    push(&head, 3);

    printList(head);
    isPalindrome(head);
    resetList(&head);

    free(head);
    return 0;
}