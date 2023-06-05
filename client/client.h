#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 1024
#define PORT 9999
#define SA struct sockaddr

//------------------------------------------------------------------
/**
 * Send a request to the server to list files.
 *
 * @param sockfd Socket file descriptor
 */
void list_files(int sockfd);
//------------------------------------------------------------------
/**
 * Upload a file to the server.
 *
 * @param sockfd Socket file descriptor
 * @param filename Name of the file to upload
 */
void upload_file(int sockfd, const char* filename);
//------------------------------------------------------------------
/**
 * Download a file from the server.
 *
 * @param sockfd Socket file descriptor
 * @param filename Name of the file to download
 */
void download_file(int sockfd, const char* filename);
//-------------------------------------------------------------------
/**
 * Print the FTP client menu.
 */
void print_menu();
//-------------------------------------------------------------------
/**
 * Handle user action selection.
 *
 * @param sockfd Socket file descriptor
 */
void action_selection(int sockfd);
//-------------------------------------------------------------------
/**
 * Perform user authentication.
 *
 * @param sockfd Socket file descriptor
 */
void user_authentication(int sockfd);
//-------------------------------------------------------------------
