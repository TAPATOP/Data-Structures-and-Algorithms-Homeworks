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

#include"Command.h"
#include"Queue.h"

class Elevator
{
public:
	Elevator();
	Elevator(unsigned short floorNum);

	void readCommand();
	void plusOneSecond(int time);
	void addCommand(Command);
	bool registerIsEmpty();

	~Elevator();
private:
	void registerInitializer();

	void moveElevator(short direction);
	void stopOnFloor(int time); // used to tell the elevator to stop on the current floor
	void markCommandAsExecuted();
	char* outputDirection();
private:
	Queue<Command> commandsRegister;// ex. 0(dir) 8(floor) 25(time)
	unsigned short floorNum;

	// killme bool* downRegister;
	bool* goRegister;
	// killme bool* upRegister;

	unsigned short currentFloor;
	short transition;
	unsigned short destinationFloor;
	short currentDirection;

};

