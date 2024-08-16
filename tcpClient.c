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
	char *ipaddr = "127.0.0.1";
	short port = PORT;
	if (argc > 1) {
		ipaddr = argv[1];
	}
	if (argc > 2) {
		port = (short)atoi(argv[2]);
	}
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	printf("[+]Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ipaddr);
	printf("[+]Connect to Server[%s:%d].\n", ipaddr, port);
	if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		printf("connect error\n");
		close(clientSocket);
		return;
	}
	printf("[+]Connected to Server.\n");
	send(clientSocket, buffer, 1024, 0);
	recv(clientSocket, buffer, 1024, 0);
	printf("[+]Data Recv: %s\n", buffer);
	printf("[+]Closing the connection.\n");
	close(clientSocket);
}
