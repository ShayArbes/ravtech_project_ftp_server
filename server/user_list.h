#ifndef USERLIST_H
#define USERLIST_H

// Structure to represent a user
typedef struct users {
    char user_name[1000];
    char password[1000];
    struct users* next;
} User;



/**
 * Create a new user node.
 *
 * @param username User's username
 * @param password User's password
 * @return Pointer to the newly created User node
 */
User* createNode(const char* username, const char* password);

/**
 * Insert a new user node at the end of the user list.
 *
 * @param head     Pointer to the head of the user list
 * @param username User's username
 * @param password User's password
 */
void insertNode(User** head, const char* username, const char* password);

/**
 * Free the memory allocated for the user list.
 *
 * @param head Pointer to the head of the user list
 */
void freeList(User* head);

#endif /* USERLIST_H */