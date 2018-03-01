//mainController.cpp
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

using namespace std;

void *evaluateThread(void* ptr);
  
class mainController : public Controller 
{
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

public:

	int iConnect;
	//SimpleController m_SC;
	//EmgController m_EC;
	WheelController m_WC;

	ofstream outdata_pos;
	ofstream outdata_vw;
	ofstream outdata_vrphi;
};  

void* evaluateThread(void* ptr)
{
  //cout << "in evaluate thread" << endl;
  mainController *pmc = (mainController*)ptr;
  evaluate ev;

  struct POS pos;
  ev.init();
  while(true)
    {
      //cout << "in while" << endl;
      pos.x = pmc->v3d_pos.x();
      pos.z = pmc->v3d_pos.z();
      pos.r0 = pmc->r(0, 0);
      pos.r2 = pmc->r(0, 2);

      ev.sendPos(pos);
      usleep(100000);
    }
  return 0;
  }
  
void mainController::onInit(InitEvent &evt) 
{
  pthread_t id;
  int ret = pthread_create(&id, NULL, evaluateThread, this);
  //  pthread_join(id, NULL);

	iConnect = -1;
	m_time = 0.01;
	m_robot = getRobotObj(myname());
  
	mWheelRadius = 2;
	mWheelDis = 10;

	m_robot->setWheel(mWheelRadius, mWheelDis);
	  
	char posName[50] = "";
	char vrphiName[50] = "";
	char vwName[50] = "";

	char dest[15] = "";
	std::time_t tt = time(NULL);
	tm *t = localtime(&tt);
	std::sprintf(dest, "%d%02d%02d%02d%02d", 
		       t->tm_year + 1900, 
		       t->tm_mon + 1, 
		       t->tm_mday, 
		       t->tm_hour, 
		       t->tm_min);

	strcat(posName, dest);
	strcat(vrphiName, dest);
	strcat(vwName, dest);

	strcat(posName, "_Pos.txt");
        strcat(vrphiName, "_VrPhi.txt");
	strcat(vwName, "_VW.txt");

	outdata_pos.open(posName);
	outdata_vw.open(vwName);
	outdata_vrphi.open(vrphiName);

	//iConnect = m_WC.connectWheel();
}  
  
double mainController::onAction(ActionEvent &evt) 
{  
	if(iConnect == -1)
	{
		iConnect = m_WC.connectWheel();
		return m_time;
	}

	// record position information
	m_robot->getPosition(v3d_pos);
	m_robot->getRotation(r);

	outdata_pos << v3d_pos.x() << "\t"
		<< v3d_pos.z() << "\t"
		<< r(0, 0) << "\t"
		<< r(0, 2) << endl;
	///////////////////////////////

	// stop condition
	if(fabs(v3d_pos.x() + 1500) < 100 && fabs(v3d_pos.z() - 5400) < 100)
	{
		cout << "========== Reach Destination! ==========" << endl;
		m_robot->setWheelVelocity(0, 0);
		return m_time;
	}
	/*struct POS pos;
	pos.x = v3d_pos.x();
	pos.z = v3d_pos.z();
	pos.r0 = r(0, 0);
	pos.r2 = r(0, 2);*/
	VELOCITY vel = m_WC.getWheelVelocity();

	// record vr and varphi
	outdata_vrphi << vel.leftVel << "\t"
			<< vel.rightVel << endl;
	///////////////////////////////

	m_robot->setWheelVelocity(vel.leftVel, vel.rightVel);

	if(vel.leftVel > 0.1f)
	  {
	    vel.leftVel -= 0.1f;
	  }
	else if(vel.leftVel < -0.1f)
	  {
	    vel.leftVel += 0.1f;
	  }
	else
	  {
	    vel.leftVel = 0.0f;
	  }

	if(vel.rightVel > 0.1f)
	  {
	    vel.rightVel -= 0.1f;
	  }
	else if(vel.rightVel < -0.1f)
	  {
	    vel.rightVel += 0.1f;
	  }
	else
	  {
	    vel.rightVel = 0.0f;
	  }
	return m_time;      
}  
  
void mainController::onRecvMsg(RecvMsgEvent &evt)
{  
}  

void mainController::onCollision(CollisionEvent &evt) 
{ 
}
  
extern "C" Controller * createController() 
{  
	return new mainController;  
}
