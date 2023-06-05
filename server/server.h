#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>

#define MAX 800
#define PORT 9999
#define SA struct sockaddr


void run_server();
/**
 * Thread function to handle communication with a client.
 *
 * @param Pconnfd Pointer to the connection file descriptor
 * @return NULL
 */
void* handle_communication(void* Pconnfd);
#endif
