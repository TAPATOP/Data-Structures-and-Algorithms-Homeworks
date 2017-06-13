/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 2
* @compiler VC
*
*/

#pragma once
#include"PseudoString.h"

using namespace std;

class Command
{
public:
	Command();

	void readCommand(PseudoString command);

	void setDirection(PseudoString direction);
	void setFloor(unsigned short);

	unsigned short getFloor();
	short getTime();
	short getDirection();
	
	~Command();
private:
	short direction;
	unsigned short floor;
	unsigned short time;
};

