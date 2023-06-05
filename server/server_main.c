#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_list.h"
User* head = NULL;

int main() {

    //User* userList = NULL;
    insertNode(&head, "a", "1");
    insertNode(&head, "user2", "pass2");
    insertNode(&head, "shay", "123");
    run_server();
    return 0;
}