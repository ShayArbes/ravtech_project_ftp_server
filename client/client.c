// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #define MAX 1024
// #define PORT 8050
// #define SA struct sockaddr
#include "client.h"


void list_files(int sockfd) {
    char buff[MAX];
    strcpy(buff, "list");
    write(sockfd, buff, strlen(buff));

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));
    printf("\n----------------------------\n");
    printf("Server files:\n%s", buff);
    printf("------------------------------\n");
}

void upload_file(int sockfd, const char* filename) {
    char buff[MAX];
    bzero(buff, MAX);
    strcpy(buff, "upload");
    write(sockfd, buff, strlen(buff));
    
    bzero(buff, MAX);
    strncpy(buff, filename, strlen(filename) + 1);
    // write strlen(buff)+1 bytes to include the null byte at the end of the string
    write(sockfd, buff, strlen(buff) + 1);
    //Checking whether the file already exists on the server
    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));

    if(!(strstr(buff,"The file is being updated"))){
        printf("%s",buff);
        return;
    }
    printf("%s",buff);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File '%s' not found\n", filename);
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Send the file size to the server
    write(sockfd, &file_size, sizeof(file_size));

    char buffer[MAX];
    ssize_t num_bytes;

    while ((num_bytes = fread(buffer, sizeof(char), MAX, file)) > 0) {
        write(sockfd, buffer, num_bytes);
    }

    fclose(file);

    printf("File '%s' uploaded successfully\n", filename);
}


void download_file(int sockfd, const char* filename) {
    char buff[MAX];
    strcpy(buff, "download");
    write(sockfd, buff, strlen(buff) + 1);

    bzero(buff, MAX);
    strcpy(buff, filename);
    write(sockfd, buff, strlen(buff) + 1);

    long file_size;
    read(sockfd, &file_size, sizeof(file_size));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to create file '%s' on the client\n", filename);
        return;
    }

    char buffer[MAX];
    int num_bytes;
    long total_bytes = 0;

    while (total_bytes < file_size && (num_bytes = read(sockfd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, sizeof(char), num_bytes, file);
        total_bytes += num_bytes;
    }

    fclose(file);

    printf("File '%s' downloaded successfully\n", filename);
}

void print_menu(){
    printf("\nFTP Client Menu:\n");
    printf("1. List files\n");
    printf("2. Upload file\n");
    printf("3. Download file\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}
void action_selection(int sockfd){
    int choice;
    char buff[MAX];
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    switch (choice) {
        case 1:
            list_files(sockfd);
            break;
        case 2: {
            printf("Enter the file to upload: ");
            bzero(buff, MAX);
            fgets(buff, sizeof(buff), stdin);
            strtok(buff, "\n");
            upload_file(sockfd, buff);
            //close(sockfd);
            break;
        }
        case 3: {
            printf("Enter the file to download: ");
            bzero(buff, MAX);
            fgets(buff, sizeof(buff), stdin);
            strtok(buff, "\n");
            download_file(sockfd, buff);
            break;
        }
        case 4:
            strcpy(buff, "exit");
            write(sockfd, buff, sizeof(buff));
            printf("Disconnecting from the server...\n");
            close(sockfd);
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    }
void user_authentication(int sockfd){


    char username[100];
    char password[100];
    char buff[MAX];
    // Authentication
    printf("Enter username: ");
    bzero(buff, MAX);
    fgets(buff, sizeof(buff), stdin);
    strtok(buff, "\n");
    send(sockfd, buff, strlen(buff),0);
    printf("Enter password: ");
    bzero(buff, MAX);
    fgets(buff, sizeof(buff), stdin);
    strtok(buff, "\n");
    puts(buff);
    send(sockfd, buff, strlen(buff),0);

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));
    printf("%s", buff);

    if (strstr(buff, "The connection failed")) {
        close(sockfd);
        exit(0);
    }

}


int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection to the server failed...\n");
        exit(0);
    } else {
        printf("Connected to the server..\n");
    }
    user_authentication(sockfd);
    while (1) {
        print_menu();
        action_selection(sockfd);
    }

    close(sockfd);

    return 0;
}
