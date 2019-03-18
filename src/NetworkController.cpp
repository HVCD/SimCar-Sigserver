/*
* File: NetworkController.cpp
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.0
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/17/2019]: network interface for the HVCD
*/

#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#include "NetworkController.h"

NetworkController::~NetworkController() {
	//close(client_fd);
}

void NetworkController::initServer(short port) {
	sin_size = sizeof(struct sockaddr_in);

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		std::cerr << "socket create failed" << std::endl;
	}
	my_addr.sin_family = AF_INET;
  
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	if(bind(sock_fd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1) {
		std::cerr << "bind error" << std::endl;
	}
}

void NetworkController::serverListen() {
	if(listen(sock_fd, 10) == -1) {
		std::cerr << "listen error" << std::endl;
	}
	
	while(true)	{
		if((client_fd = accept(sock_fd, 
			(struct sockaddr*)&remote_addr, 
			&sin_size)) == -1)
		{
			std::cout << "waiting for connecting\r";
			continue;
		}
		std::cout << "received a connection from " 
			<< inet_ntoa(remote_addr.sin_addr) << std::endl;
		break;
	}
}

void NetworkController::serverRecv(char* buffer, int bufLen) {
	if(-1 == recv(client_fd, buffer, bufLen, 0)) {
		std::cerr << "recieve error" << std::endl;
	}  
}

void NetworkController::serverSend(char* buffer, int bufLen) {
	if(-1 == send(client_fd, buffer, bufLen, 0)) {
		std::cerr << "send error" << std::endl;
    }
}