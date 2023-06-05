
#include "server.h"
#include "user_list.h"
#include "file_transfer.h"
#include "user_authentication_functions.h"
extern User* head;
void run_server(){
    int sockfd, len;
    struct sockaddr_in servaddr, cli;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind the socket
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }

    // Listen for connections
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else {
        printf("Server listening..\n");
    }
    len = sizeof(cli);

    while (1) {
        // Accept a connection
        int* connfd = malloc(sizeof(int));
        *connfd = accept(sockfd, (SA*)&cli, &len);
        if (*connfd < 0) {
            printf("Server accept failed...\n");
            exit(0);
        } else {
            printf("Server accepted the client...\n");
        }

        // Create a new thread to handle the communication with the client
        pthread_t tid;
        pthread_create(&tid, NULL, handle_communication, (void*)connfd);
        pthread_detach(tid);
    }
    close(sockfd);
}

void* handle_communication(void* Pconnfd) {
    int connfd = *(int*)Pconnfd;
    char buff[MAX]= {0};
    int n;
    //head = userList;
    // Read the username from the client

    recv(connfd, buff, sizeof(buff)-1,0);
    int username_valid = username_authentication(buff);

    // Read the password from the client
 
    bzero(buff, MAX);
    recv(connfd, buff, sizeof(buff)-1,0);
    int pass_valid = pass_authentication(buff);

    if (username_valid && pass_valid) {
        // Authentication successful
        bzero(buff, MAX);
        strcpy(buff, "The connection was successful\n");
        write(connfd, buff, sizeof(buff));
    } else {
        // Authentication failed
        printf("Connection attempt: username or password not verified\n");
        bzero(buff, MAX);
        strcpy(buff, "The connection failed\n");
        write(connfd, buff, sizeof(buff));

        // Close the connection and terminate the thread
        close(connfd);
        sleep(5); // For the server to print that there was a failed connection before the process died
        pthread_exit(NULL);
    }
    printf("\n");

    char log_msg[MAX];
    snprintf(log_msg, sizeof(log_msg), "Client connected: %d\n", connfd);
    printf("%s", log_msg);

    while (1) {
        bzero(buff, MAX);
        //There is a bug here
        int ret = read(connfd, buff, sizeof(buff));
        if (ret == 0) {
            break;
        }
        
        printf("Received command from client %d: %s\n", connfd, buff);

        // List files in the server's directory
        if (strncmp("list", buff, 4) == 0) {
            list_request(connfd);
        }
        // Upload a file to the server
        else if (strncmp("upload", buff, 6) == 0) {
            char filename[MAX];
            bzero(filename, MAX);
            // read MAX bytes from the socket
            read(connfd, filename, MAX);

            receive_file(connfd, filename);
        }
        // Download a file from the server
        else if (strncmp("download", buff, 8) == 0) {
            char filename[MAX];
            bzero(filename, MAX);
            read(connfd, filename, MAX);
            send_file(connfd, filename);
        }
        // Exit the connection
        else if (strncmp("exit", buff, 4) == 0) {
            printf("Client %d disconnected\n", connfd);
            break;
        } else {
            printf("error: selection does not exist");
        }
    }

    close(connfd);
    freeList(head);
    free(Pconnfd);
    pthread_exit(NULL);
}
