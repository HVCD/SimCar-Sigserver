/*
* File: CarController.h
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.1
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/01/2018]: control the car
	v1.1 [03/17/2019]: arranged version with improvement
*/

#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct VELOCITY {
	float leftVel;
	float rightVel;
};

class CarController {
public:
	int m_wheelDis;
	int m_wheelRadius;

public:
	CarController(int wheelDis, int wheelRadius);
	~CarController();

	VELOCITY getVelocity(float v, float w);
};

CarController::CarController(int wheelDis, int wheelRadius) {
	m_wheelDis = wheelDis;
	m_wheelRadius = wheelRadius;
}

VELOCITY CarController::getVelocity(float v, float w) {
	VELOCITY vel;
	cout << "--> " << v << ", " << w << endl;

	vel.leftVel = v - w * m_wheelDis / 2;
	vel.rightVel = v + w * m_wheelDis / 2;
	return vel;
}
#endif