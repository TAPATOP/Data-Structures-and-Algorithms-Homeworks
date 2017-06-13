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

#include"Queue.h"
#include"Command.h"

class Elevator
{
public:
	Elevator();
	Elevator(unsigned short floorNum);

	void readCommand();
	void plusOneSecond(int& time);
	void addCommand(Command);
	bool registerIsEmpty();

	~Elevator();

private:
	Queue<Command> commandsRegister;// ex. 0(dir) 8(floor) 25(time)
	unsigned short floorNum;

	bool* downRegister;
	bool* goRegister;
	bool* upRegister;
	void registerInitializer();

	unsigned short currentFloor;
	short transition;
	unsigned short destinationFloor;
	short currentDirection;

	void moveElevator(short direction);
	void stopOnFloor(int time); // used to tell the elevator to stop on the current floor
	void nullifyCommand();
	PseudoString outputDirection();
};

