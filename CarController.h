//CarController.h
#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct VELOCITY
{
	float leftVel;
	float rightVel;
};

class CarController
{
public:
	int m_wheelDis;
	int m_wheelRadius;

public:
	CarController(int wheelDis, int wheelRadius);
	~CarController();

	VELOCITY getVelocity(float v, float w);
};

CarController::CarController(int wheelDis, int wheelRadius)
{
	m_wheelDis = wheelDis;
	m_wheelRadius = wheelRadius;
}

CarController::~CarController()
{
}

VELOCITY CarController::getVelocity(float v, float w)
{
	VELOCITY vel;
	cout << "--> \t" << v << "\t" << w << endl;
  
	vel.leftVel = v - w * m_wheelDis / 2;
	vel.rightVel = v + w * m_wheelDis / 2;
	return vel;
}
#endif
