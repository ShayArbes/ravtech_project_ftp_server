C File Server
This program is a simple file server implemented in C. The server creates a socket and listens for client connections on a specified port. When a client connects, the server authenticates the client's username and password by checking them against a linked list of user records stored in memory. Once authenticated, the client can list, upload, and download files on the server.

Features
User Authentication: The server verifies the username and password provided by the client against a list of registered users.
File Transfer: The server supports listing, uploading, and downloading of files. When the client sends a list command, the server responds with a list of files in the server's directory. For upload and download commands, the client must also send the name of the file to transfer.
Multi-threading: The server creates a new thread for each client connection, allowing it to handle multiple clients simultaneously.
Running the Server
To run the server, simply compile and execute the main C file. The server will start and listen for client connections. A few user records are created at startup for testing purposes.

bash
Copy code
 gcc -o main server.c server_main.c file_transfer.c user_authentication_functions.c user_list.c 
./main
Using the Client
The client must connect to the server's IP address and port using a socket, then send the username and password for authentication. If the authentication is successful, the client can send commands to list, upload, or download files.

Code Structure
The code is divided into several files, each with a specific purpose:

user_list.h and user_list.c: Defines the User struct and functions for managing a linked list of User records.
user_authentication_functions.h and user_authentication_functions.c: Contains functions for authenticating a client's username and password.
server.h and server.c: Defines the main server functions, including socket creation, client connection handling, and command processing.
file_transfer.h and file_transfer.c: Defines functions for listing, sending, and receiving files.
main.c: Initializes the user list and starts the server.
Notes
The server does not persist user records or files between runs. When the server is restarted, it loses all data and must be reinitialized.
The server does not support encrypted connections or password hashing. The username and password are sent in plain text, and the password is stored in plain text in the server's memory.
The server does not handle file conflicts. If a client tries to upload a file that already exists on the server, the server simply rejects the upload.
The server does not limit the size of the files that can be transferred. If a client tries to upload or download a very large file, the server may run out of memory.
The server does not sanitize the filenames sent by the client. A malicious client could potentially upload a file with a name that causes issues on the server's file system.