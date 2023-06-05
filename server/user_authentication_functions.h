#ifndef USER_AUTHENTICATION_FUNCTIONS_H
#define USER_AUTHENTICATION_FUNCTIONS_H
/**
 * Authenticate the username provided by the client.
 *
 * @param user_str Username string provided by the client
 * @return 1 if the username is valid, 0 otherwise
 */
int username_authentication(char* user_str);

/**
 * Authenticate the password provided by the client.
 *
 * @param pass Password string provided by the client
 * @return 1 if the password is valid, 0 otherwise
 */
int pass_authentication(char* pass);
#endif//USER_AUTHENTICATION_FUNCTIONS_H