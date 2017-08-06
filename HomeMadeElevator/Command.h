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

class Command
{
public:
	Command();

	void readCommand(const char* command);

	void setDirection(PseudoString direction);
	void setFloor(unsigned short);

	unsigned short getFloor();
	short getTime();
	short getDirection();
	
	~Command();
private:
	short direction;
	unsigned short floor; // rename as destination?
	unsigned short time;
};

