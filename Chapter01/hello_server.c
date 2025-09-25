#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define SERVER_PORT "9190"

void ErrorHandling(char* message);

int main()
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	SOCKADDR D;

	int szClntAddr;
	char message[] = "Hello World!";
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(SERVER_PORT));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) ErrorHandling("bind() error");
	if (listen(hServSock, 5) == SOCKET_ERROR) ErrorHandling("listen() error");


	for (int i = 0; i <= 9; i++)
	{
		szClntAddr = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
		if (hClntSock == INVALID_SOCKET) ErrorHandling("accept() error");
		send(hClntSock, message, sizeof(message), 0);
		printf("serverSend :%dth message\n",i+1);
		closesocket(hClntSock);
	}


	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}