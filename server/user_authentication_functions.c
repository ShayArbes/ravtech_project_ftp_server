#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_authentication_functions.h"
#include "user_list.h"
extern User* head;
int username_authentication(char* user_str) {
    if (*user_str == '\n') {
        return 0;
    }
    User* current = head;
    int username_match;
    //char* p_user_str = strtok(user_str, "\n ");
    while (current != NULL) {
        username_match = strcmp(user_str, current->user_name) == 0;
        if (username_match) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to authenticate the password provided by the client
int pass_authentication(char* pass) {

    if (*pass == '\n') {
        return 0;
    }
    User* current = head;
    int pass_match;
    char* p_pass = strtok(pass, "\n ");
    if(p_pass == NULL ){
        printf("pass=null");
        return 0;
    }
    while (current != NULL) {
        pass_match = strcmp(p_pass, current->password) == 0;
        if (pass_match) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}