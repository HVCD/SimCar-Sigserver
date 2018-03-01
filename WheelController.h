//WheelController.h
#ifndef WHEELCONTROLLER_H
#define WHEELCONTROLLER_H

#include "NetworkController.h"
//#include "evaluate.h"

struct VELOCITY
{
	float leftVel;
	float rightVel;
};

class WheelController : public NetworkController
{
public:
	WheelController();
	//~WheelController();

	int connectWheel();
	VELOCITY getWheelVelocity(/*struct POS pos*/);
};

WheelController::WheelController()
{
}

//~WheelController::~WheelController()
//{
//}

int WheelController::connectWheel()
{
	initServer(9600);
	cout << "Init Server..." << endl;
	serverListen();
	cout << "Server Listening..." << endl;
	return 0;
}

VELOCITY WheelController::getWheelVelocity(/*struct POS pos*/)
{
	VELOCITY vel;
	serverRecv((char*)&vel, sizeof(struct VELOCITY));
	//serverSend((char*)&pos, sizeof(struct POS));
	cout << vel.leftVel << "    " << vel.rightVel << endl;
	return vel;
}

#endif
