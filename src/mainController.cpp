/*
* File: mainController.cpp
* Author: Wenyu
* Date: 03/17/2019
* Version: 2.0
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/01/2018]: main loop for HVCD server
	v2.0 [03/17/2019]: arranged version with improvement
*/

#include "ControllerEvent.h"
#include "Controller.h"
#include "Logger.h"

//#include "simpleController.h"
//#include "emgController.h"

#include "evaluate.h"
#include "WheelController.h"

#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <ctime>

void *evaluateThread(void* ptr);

class mainController : public Controller {
public:
	RobotObj* m_robot;
	double m_time;

	float mWheelRadius;
	float mWheelDis;
  
	Vector3d v3d_pos;
	Rotation r;

public:
	void onInit(InitEvent &evt);
	double onAction(ActionEvent&);
	void onRecvMsg(RecvMsgEvent &evt);
	void onCollision(CollisionEvent &evt);
	
	~mainController();

public:

	int iConnect;
	//SimpleController m_SC;
	//EmgController m_EC;
	WheelController m_WC;

	std::ofstream outdata;
};

mainController::~mainController(){
	outdata.close();
}

void* evaluateThread(void* ptr) {
	mainController *pmc = (mainController*)ptr;
	evaluate ev;

	struct POS pos;
	ev.init();
	
	while(true) {
		pos.x = pmc->v3d_pos.x();
		pos.z = pmc->v3d_pos.z();
		pos.r0 = pmc->r(0, 0);
		pos.r2 = pmc->r(0, 2);

		ev.sendPos(pos);
		usleep(100000);
	}
	return 0;
}

void mainController::onInit(InitEvent &evt) {
	pthread_t id;
	int ret = pthread_create(&id, NULL, evaluateThread, this);
	//  pthread_join(id, NULL);

	iConnect = -1;
	m_time = 0.01;
	m_robot = getRobotObj(myname());
  
	mWheelRadius = 2;
	mWheelDis = 10;

	m_robot->setWheel(mWheelRadius, mWheelDis);
	
	char file_name[50] = "RL_Data/";
	char dest[25] = "";
	std::time_t tt = time(NULL);
	tm *t = localtime(&tt);
	std::sprintf(dest, "%d%02d%02d_%02d%02d_data.csv",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min);

	strcat(file_name, dest);

	outdata.open(file_name);
	outdata << "x,z,r00,r02,v_l,v_r" << std::endl;
	//iConnect = m_WC.connectWheel();
}

double mainController::onAction(ActionEvent &evt) {
	if(iConnect == -1) {
		iConnect = m_WC.connectWheel();
		return m_time;
	}
	// record position information
	m_robot->getPosition(v3d_pos);
	m_robot->getRotation(r);

	outdata << v3d_pos.x() << "," 
		<< v3d_pos.z() << ","
		<< r(0, 0) << "," 
		<< r(0, 2) << ",";

	// stop condition
	if(fabs(v3d_pos.x() + 1500) < 100 && fabs(v3d_pos.z() - 5400) < 100) {
		std::cout << "========== Reach Destination! ==========" << std::endl;
		m_robot->setWheelVelocity(0, 0);
		return m_time;
	}

	VELOCITY vel = m_WC.getWheelVelocity();

	// record velocity of left and right wheel
	outdata << vel.leftVel << "," << vel.rightVel << std::endl;

	m_robot->setWheelVelocity(vel.leftVel, vel.rightVel);

	if(vel.leftVel > 0.1f) {
		vel.leftVel -= 0.1f;
	}
	else if(vel.leftVel < -0.1f) {
		vel.leftVel += 0.1f;
	}
	else {
		vel.leftVel = 0.0f;
	}

	if(vel.rightVel > 0.1f) {
		vel.rightVel -= 0.1f;
	}
	else if(vel.rightVel < -0.1f) {
		vel.rightVel += 0.1f;
	}
	else {
	    vel.rightVel = 0.0f;
	}
	return m_time;
}

void mainController::onRecvMsg(RecvMsgEvent &evt) {
}

void mainController::onCollision(CollisionEvent &evt) {
}

extern "C" Controller * createController() {
	return new mainController;
}