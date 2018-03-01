//evaluate.h
#ifndef EVALUATE_H
#define EVALUATE_H

#include "NetworkController.h"

struct POS
{
  float x;
  float z;
  float r0;
  float r2;
};

class evaluate
{
 public:
  NetworkController m_nc;
 public:
  int init();
  int sendPos(struct POS pos);
};

int evaluate::init()
{
  m_nc.initServer(9700);
  m_nc.serverListen();
  return 0;
}

int evaluate::sendPos(struct POS pos)
{
  //cout << "in sendPos for recv" << endl;
  char command[5] = "";
  m_nc.serverRecv(command, 2);
  //cout << "recv finish => " << command << endl;
  if(command[0] == 'R' && command[1] == 'P')
    {
      m_nc.serverSend((char*)&pos, sizeof(struct POS));
      return 0;
    }
  return 1;
}

#endif
