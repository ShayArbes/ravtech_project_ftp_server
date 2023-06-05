#ifndef FILETRANSFER_H
#define FILETRANSFER_H
/**
 * Send a file to the client.
 *
 * @param connfd   Connection file descriptor
 * @param filename Name of the file to send
 */
void send_file(int connfd, const char* filename);

/**
 * Receive a file from the client.
 *
 * @param connfd   Connection file descriptor
 * @param filename Name of the file to receive
 */
void receive_file(int connfd, const char* filename);

void list_request(int connfd) ;
#endif /* FILETRANSFER_H */