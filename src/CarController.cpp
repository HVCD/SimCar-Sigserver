/*
* File: CarController.cpp
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.0
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/17/2019]: control the car
*/

#include <iostream>
#include "CarController.h"

using namespace std;

CarController::CarController(int wheelDis, int wheelRadius) {
	m_wheelDis = wheelDis;
	m_wheelRadius = wheelRadius;
}

VELOCITY CarController::getVelocity(float v, float w) {
	VELOCITY vel;
	std::cout << "--> " << v << ", " << w << std::endl;

	vel.leftVel = v - w * m_wheelDis / 2;
	vel.rightVel = v + w * m_wheelDis / 2;
	return vel;
}