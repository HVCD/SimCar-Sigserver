/*
* File: NetworkController.h
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.1
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/01/2018]: network interface for the HVCD
	v1.1 [03/17/2019]: arranged version with improvement
*/

#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

#include <netinet/in.h>
#include <sys/socket.h>

class NetworkController {
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

#endif