#ifndef SERVER_ROUTINE_H_INCLUDED
#define SERVER_ROUTINE_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512
#define PORT 8888

int InitializeServer(void);
int ReceiveMessage(void);
int SendMessage(void);
int TurnOff(void);

#endif
