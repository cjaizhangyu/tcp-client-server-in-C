#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5566

void main(int argc, char** argv){

	int sockfd;
	short port = PORT;
	if (argc > 1) {
		port = (short)atoi(argv[1]);
	}
	struct sockaddr_in serverAddr;
	int newSocket;
	struct sockaddr_in newAddr;
	socklen_t addr_size;
	char buffer[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("[+]Server Socket Created Sucessfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);;
	// serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", port);

	listen(sockfd, 5);
	printf("[+]Listening...\n");

	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	char clientIPAddr[32] = {0};
	inet_ntop(AF_INET, &newAddr.sin_addr.s_addr, clientIPAddr, 16);
	printf("[+]New client %s.\n", clientIPAddr);
	strcpy(buffer, "Hello");
	recv(newSocket, buffer, sizeof(buffer), 0);
	send(newSocket, buffer, strlen(buffer), 0);
	printf("[+]Closing the connection.\n");
	close(newSocket);
	close(sockfd);
}
