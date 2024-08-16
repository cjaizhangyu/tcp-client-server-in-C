CC ?= gcc
all:
	$(CC) tcpClient.c -o tcpClient
	$(CC) tcpServer.c -o tcpServer

clean:
	rm -f tcpClient tcpServer
