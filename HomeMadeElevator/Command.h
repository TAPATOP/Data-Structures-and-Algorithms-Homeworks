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

#include<iostream>

class Command
{
public:
	Command();

	void setDirection(char* direction);
	void setFloor(unsigned short);

	unsigned short getFloor();
	short getTime();
	short getDirection();
	
	// uses char array to materialize an actual command
	void readCommand(const char* command);

	~Command();
private:
	short direction;
	unsigned short floor; // TODO: rename as destination?
	unsigned short time;
};

