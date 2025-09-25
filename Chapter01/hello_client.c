#pragma warning(disable: 4996)  
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define SERVER_PORT "9190"
#define SERVER_IP "127.0.0.1"

void ErrorHandling(char* message);

int main()
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) ErrorHandling("hSocketet() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERVER_IP);	
	servAddr.sin_port = htons(atoi(SERVER_PORT));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) ErrorHandling("connet() error");

	
	strLen = recv(hSocket, message, sizeof(message) - 1, 0);
	if (strLen == -1) ErrorHandling("read() error!");
	printf("Message from server : %s \n", message);

	closesocket(hSocket);
	getchar();
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}