//NetworkController.h
#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <iostream>
#include <cassert>

#include <cstdio>
#include <cstdlib>

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

using namespace std;

class NetworkController
{
public:
	int sock_fd;
	int client_fd;
	socklen_t sin_size;

	struct sockaddr_in my_addr;
	struct sockaddr_in remote_addr;

public:
	~NetworkController();
	void initServer(short port);
	void serverListen();
	void serverRecv(char* buffer, int bufLen);
	void serverSend(char* buffer, int bufLen);

};

NetworkController::~NetworkController()
{
  //close(client_fd);
}

void NetworkController::initServer(short port)
{
	sin_size = sizeof(struct sockaddr_in);

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		cout << "socket create failed" << endl;
	}
	my_addr.sin_family = AF_INET;
  
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	if(bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		cout << "bind error" << endl;
	}
}

void NetworkController::serverListen()
{
	if(listen(sock_fd, 10) == -1)
	{
		cout << "listen error" << endl;
	}
	while(true)
	{
		if((client_fd = accept(sock_fd, (struct sockaddr *)&remote_addr, &sin_size)) == -1)
		{
			cout << "waiting for connecting\r";
			continue;
		}
		cout << "received a connection from " << inet_ntoa(remote_addr.sin_addr) << endl;
		break;
	}
}

void NetworkController::serverRecv(char* buffer, int bufLen)
{
	if(-1 == recv(client_fd, buffer, bufLen, 0))
	{
		cout << "recieve error" << endl;
	}  
}

void NetworkController::serverSend(char* buffer, int bufLen)
{
  if(-1 == send(client_fd, buffer, bufLen, 0))
    {
      cout << "send error" << endl;
    }
}

#endif
