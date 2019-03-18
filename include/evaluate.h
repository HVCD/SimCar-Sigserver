/*
* File: evaluate.h
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.1
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/01/2018]: evaluate from the network
	v1.1 [03/17/2019]: arranged version with improvement
*/

#ifndef EVALUATE_H
#define EVALUATE_H

#include "NetworkController.h"

struct POS {
    float x;
    float z;
    float r0;
    float r2;
};

class evaluate {
public:
    NetworkController m_nc;

public:
    int init();
    int sendPos(struct POS pos);
};

#endif