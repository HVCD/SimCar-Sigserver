/*
* File: WheelController.cpp
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.0
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/17/2018]: control the wheel car by network interface
*/

#include "NetworkController.h"
#include "WheelController.h"

#include <iostream>

WheelController::WheelController() {
}

int WheelController::connectWheel() {
	initServer(9600);
	std::cout << "Init Server..." << std::endl;
	serverListen();
	std::cout << "Server Listening..." << std::endl;
	return 0;
}

VELOCITY WheelController::getWheelVelocity() {
	VELOCITY vel;
	serverRecv((char*)&vel, sizeof(struct VELOCITY));
	std::cout << vel.leftVel << "  " << vel.rightVel << std::endl;
	return vel;
}