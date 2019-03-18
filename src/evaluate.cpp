/*
* File: evaluate.h
* Author: Wenyu
* Date: 03/17/2019
* Version: 1.0
* Env: Ubuntu 12.04 x86, Sigverse 2.2.2
* Function:
	v1.0 [03/17/2018]: evaluate from the network
*/

#include "evaluate.h"

int evaluate::init() {
    m_nc.initServer(9700);
    m_nc.serverListen();
    return 0;
}

int evaluate::sendPos(struct POS pos) {
    char command[5] = "";
    m_nc.serverRecv(command, 2);
    if(command[0] == 'R' && command[1] == 'P') {
        m_nc.serverSend((char*)&pos, sizeof(struct POS));
        return 0;
    }
    return 1;
}