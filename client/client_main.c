#include "client.h"

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