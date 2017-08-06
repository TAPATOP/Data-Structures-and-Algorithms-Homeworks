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

#include "Command.h"


Command::Command()
{
	//type = 0;
	direction = 0;
	floor = 0;
	time = 0;
}

void Command::readCommand(const char* command)
{
	PseudoString direction = "";
	int i = 0;

	if (command[0] == 'c')
	{
		i = 5;

		if (command[i] == 'd')
		{
			direction = "down";
			i += 5;
		}
		else
		{
			direction = "up";
			i += 3;
		}
	}
	else
	{
		i = 3;
	}

	while (command[i] != ' ')
	{
		floor = floor * 10 + (command[i] - 48);
		i++;
	}
	i++;

	while (command[i])
	{
		time = time * 10 + (command[i] - 48);
		i++;
	}
	setDirection(direction);
}
//
// gets data for command
//

void Command::setDirection(PseudoString direction)
{
	if (direction == "up")
	{
		this->direction = 1; // 1 for up, -1 for down, 0 for "go" by default
	}
	else if (direction == "down")
	{
		this->direction = -1; // 1 for up, -1 for down, 0 for "go" by default
	}
	else
	{
		this->direction = 0; // default
	}
}
//
// uses read string to materialize an actual command
//

void Command::setFloor(unsigned short floor)
{
	this->floor = floor;
}
unsigned short Command::getFloor()
{
	return floor;
}
short Command::getTime()
{
	return time;
}
short Command::getDirection()
{
	return direction;
}

Command::~Command()
{
}
