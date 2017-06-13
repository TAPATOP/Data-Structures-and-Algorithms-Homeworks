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

#include "Elevator.h"


Elevator::Elevator()
{
	floorNum = 0;
	currentFloor = 0;
	destinationFloor = 0;
	currentDirection = 0;
	transition = 0;
	registerInitializer();
}

Elevator::Elevator(unsigned short floorNum)
{
	this->floorNum = floorNum;
	currentFloor = 0;
	destinationFloor = 0;
	currentDirection = 0;
	transition = 0;
	registerInitializer();
}
//
// constructors above
//

void Elevator::readCommand()
{
	while (
		((
		commandsRegister.top().getDirection() == 0 && goRegister[commandsRegister.top().getFloor()] == 0
		) ||
		commandsRegister.top().getFloor() == 0) && !commandsRegister.isEmpty()
		)
		{
			commandsRegister.dequeue(); // dequeue command if it has already been dealt with
		}
		if (!commandsRegister.isEmpty())
		{
			destinationFloor = commandsRegister.top().getFloor(); // set the new destination

			if (currentFloor > destinationFloor)
			{
				currentDirection = -1; // elevator must go down
			}
			else
			{
				currentDirection = 1; // elevator must go up
			}
		}
}
//
// tell the elevator where to head
//

void Elevator::plusOneSecond(int& time)
{
	if (currentFloor == 0)
	{
		currentFloor = 1;
		readCommand();
	} // this breaks the elevator's virginity

	if (transition == 0)// transition represents whether the elevator has finished moving between the floros;  
	{					// the elevator doesn really care about anything if it is between two floors though

		if (currentFloor == destinationFloor) // if the destination floor has been reached
		{
			// since the current floor is the destination one, we need a new destination and thus a new command

			stopOnFloor(time); // first mark that we've fulfilled the current query

				if (!commandsRegister.isEmpty())
				{	
					if (commandsRegister.queueSize() == 1)
					{
						readCommand(); // drops already executed commands !!!
						commandsRegister.dequeue();
						//moveElevator(currentDirection);
					}
					else
					{
						commandsRegister.dequeue();
						readCommand(); // drops already executed commands !!!
					}
				} // iirc the reason this if exists is to handle situations with no commands in the register
		}

		if (goRegister[currentFloor] == 1)
		{
			// the elevator will always stop if he has a >go< command 
			// to the currentFloor, no matter the destination or direction
			stopOnFloor(time);
		}
	}

	if (currentFloor != destinationFloor)
	{
		moveElevator(currentDirection); // the elevator has to move if he hasn't stopped on the destination floor
	}
}
//
// simulate events in a second
//

void Elevator::addCommand(Command command) // I believe having a copy instead of the actual thing would be better
{
	commandsRegister.enqueue(command);

	unsigned short flo = command.getFloor();

	goRegister[flo] = 1; // record that the elevator should drop someone off to destinfloor
}
//
// make the elevator aware of the given command destinations and add it to the command register
//

bool Elevator::registerIsEmpty()
{
	return commandsRegister.isEmpty();
}
//
// 1 if commandsRegister is empty; 0 if not
//

void Elevator::registerInitializer()
{
	goRegister = new bool [floorNum + 1]();
}
//
// set up all of the arrays responsible for passenger (un)loading
//

void Elevator::moveElevator(short direction)
{
	transition++;
	if (transition == 5) // 5 * 0.2 = 1 floor
	{
		currentFloor += direction;
		transition = 0;
	}
}
//
// does the movement calculations
//

void Elevator::stopOnFloor(int time)
{
	bool flag = 0;// this exists because of empty cycles

	if (goRegister[currentFloor])
	{
		goRegister[currentFloor] = 0;
		flag = 1;
	}

	if (flag) cout << time << " " << currentFloor << " " << outputDirection() << endl;

	nullifyCommand();
}
//
// tells the elevator what to do once he has an order to stop
//

void Elevator::nullifyCommand()
{
	short size1 = commandsRegister.getHead();
	short size2 = commandsRegister.getTail();

	for (short i = size1; i < size2; i++)
	{
		if (commandsRegister[i].getFloor() == currentFloor)
		{
			commandsRegister[i].setFloor(0);
		}
	}
}
//
// tells all the current commands in the commandsRegister that they have been executed if they match the
// floor on which the elevator has stopped
//

PseudoString Elevator::outputDirection()
{
	if (currentFloor == 1)
	{
		return "down";
	}
	if (currentDirection == -1 || currentDirection == 0)
	{
		return "down";
	}
	else
	{
		return "up";
	}
}
//
// helps with cout
//

Elevator::~Elevator()
{
	delete[] goRegister;
}

