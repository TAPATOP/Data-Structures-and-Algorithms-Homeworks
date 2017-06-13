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

#include<iostream>
#include<fstream>

#include"Queue.h"
#include"Command.h"
#include"PseudoString.h"
#include"Elevator.h"

using namespace std;

int main(int argv, char** entrance)
{
	entrance[1] = "file.txt";
	ifstream input(entrance[1]);
	int N;
	int K;
	input >> N;
	input >> K;

	PseudoString* commands = new PseudoString[K];
	Command* readyCommands = new Command[K];

	PseudoString a;

	int index = 0;

	input >> a;

	while (!input.eof())
	{
		commands[index] += a + " ";
		if (a[0] == 'c')
		{
			input >> a;
			commands[index] += a + " ";

			input >> a;
			commands[index] += a + " ";

			input >> a;
			commands[index] += a;
		}
		else
		{
			input >> a;
			commands[index] += a + " ";

			input >> a;
			commands[index] += a;
		}
		index++;
		input >> a;
	}

	for (int i = 0; i < K; i++)
	{
		readyCommands[i].readCommand(commands[i]);
	}

	Elevator elev(N);

	Queue<Command> pushUs(readyCommands, K, K);

	unsigned short startTime = pushUs.top().getTime();

	for (int i = startTime; !pushUs.isEmpty() || !elev.registerIsEmpty(); i++)
	{
		if (pushUs.top().getTime() == i && !pushUs.isEmpty())
		{
			elev.addCommand(pushUs.topNpop());
			i--;
			continue;
		}
		elev.plusOneSecond(i);
	}
	return 0;
}

// string -(read command)> Command -(add command)> elevator

/*/
7 2
call up 7 35
call down 7 50
/*/

/*/
1 4
call down 1 1
call up 1 2
call up 1 5
call down 1 6
/*/

/*/
8 8
call down 7 0
go 1 30
call up 3 31
call down 5 31
call up 2 31
go 1 40
go 8 65
go 7 70
/*/