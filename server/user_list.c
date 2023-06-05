#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_list.h"
extern User* head;
User* createNode(const char* username, const char* password) {
    User* newNode = (User*)malloc(sizeof(User));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strncpy(newNode->user_name, username, sizeof(newNode->user_name) - 1);
    strncpy(newNode->password, password, sizeof(newNode->password) - 1);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new user node at the end of the user list
void insertNode(User** head, const char* username, const char* password) {
    User* newNode = createNode(username, password);
    if (*head == NULL) {
        *head = newNode;
    } else {
        User* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to free the user list
void freeList(User* head) {
    User* current = head;
    while (current != NULL) {
        User* temp = current;
        current = current->next;
        free(temp);
    }
}