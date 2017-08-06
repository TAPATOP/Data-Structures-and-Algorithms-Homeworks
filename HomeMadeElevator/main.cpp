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

int main(int argc, char** argv)
{
	argv[1] = "file.txt";
	ifstream input(argv[1]);
	int N;
	int K;
	input >> N;
	input >> K;

	PseudoString* commands = new PseudoString[K];
	Command* readyCommands = new Command[K];

	PseudoString a;

	int index = 0;

	input >> a;
	// ÒODO: Proper reading
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
		readyCommands[i].readCommand(commands[i].getText());
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

/*/
10 10
call down 5 1
call up 5 6
go 2 7
go 8 9
call up 4 10
go 2 12
go 10 13
call down 5 16
go 1 18
go 8 19
:
16 4 up
21 5 up
36 2 down
66 8 up
76 10 up
121 1 down
/*/