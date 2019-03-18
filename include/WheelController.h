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

#endif