#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>
#include "file_transfer.h"

#define MAX 800
#define MAX_BUFF_SIZE 256

// Send a list of files in the current directory to the client
void list_request(int connfd) {
    DIR* dir;
    struct dirent* entry;
// Open the server's directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Failed to open directory");
        return;
    }

    char file_list[MAX] = {0};
    while ((entry = readdir(dir)) != NULL) {
         // Exclude the current directory (".") and parent directory ("..")
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Concatenate the filename with a newline character to the file list
            strncat(file_list, entry->d_name, sizeof(file_list) - strlen(file_list) - 1);
            strncat(file_list, "\n", sizeof(file_list) - strlen(file_list) - 1);
        }
    }

    closedir(dir);
    // Send the file list to the client
    write(connfd, file_list, strlen(file_list));
}
// Function to send a file to the client
void send_file(int connfd, const char* filename) {
    // Open the file in binary mode for reading
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        char msg[MAX];
        snprintf(msg, sizeof(msg), "File '%s' not found on the server.\n", filename);
        write(connfd, msg, strlen(msg));
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Send the file size to the client
    write(connfd, &file_size, sizeof(file_size));

    char buffer[MAX];
    ssize_t num_bytes;

    // Read the file in chunks and send them to the client
    while ((num_bytes = fread(buffer, sizeof(char), sizeof(buffer), file)) > 0) {
        write(connfd, buffer, num_bytes);
    }

    fclose(file);
}

// Function to receive a file from the client
void receive_file(int connfd, const char* filename) {
    // Check if the file already exists on the server
    char msg[MAX];
    FILE* existing_file = fopen(filename, "rb");

    if (existing_file != NULL) {
        snprintf(msg, sizeof(msg), "File '%s' already exists on the server.\n", filename);
        write(connfd, msg, strlen(msg));
        fclose(existing_file);
        return;
    }
    
    // Open the file in binary mode for writing
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        
        snprintf(msg, sizeof(msg), "Failed to create file '%s' on the server.\n", filename);
        write(connfd, msg, strlen(msg));
        return;
    }
    snprintf(msg, sizeof(msg), "The file is being updated\n");
    write(connfd, msg, strlen(msg));
    // Receive the file size from the client
    long file_size;
    read(connfd, &file_size, sizeof(file_size));

    char buffer[MAX];
    ssize_t num_bytes;
    long total_bytes = 0;

    // Receive the file data from the client and write it to the file
    while (total_bytes < file_size && (num_bytes = read(connfd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, sizeof(char), num_bytes, file);
        total_bytes += num_bytes;
    }

    fclose(file);
}