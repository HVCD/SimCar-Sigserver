/*
* File: WheelController.h
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.1
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/01/2018]: control the wheel car by network interface
	v1.1 [03/17/2019]: arranged version with improvement
*/

#ifndef WHEEL_CONTROLLER_H
#define WHEEL_CONTROLLER_H

#include "NetworkController.h"
#include <iostream>

struct VELOCITY {
	float leftVel;
	float rightVel;
};

class WheelController : public NetworkController {
public:
	WheelController();

	int connectWheel();
	VELOCITY getWheelVelocity();
};

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
#endif