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

#include"Command.h"
#include"Elevator.h"
#include"Queue.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Read the instructions pls" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);

	if (!input.is_open())
	{
		std::cout << "I can't really open this file.." << std::endl;
		return 2;
	}

	int N;
	int K;
	input >> N;
	input >> K;

	char command[50];
	command[0] = '\0';

	char word[40];
	Command* readyCommands = new Command[K];

	int index = 0;

	input >> word;
	// ÒODO: Proper reading
	while (!input.eof())
	{
		strcat_s(word, " ");
		strcat_s(command, word);

		if (word[0] == 'c')
		{
			input >> word;
			strcat_s(word, " ");
			strcat_s(command, word);
		}
		input >> word;
		strcat_s(word, " ");
		strcat_s(command, word);

		input >> word;

		strcat_s(command, word);
		
		readyCommands[index].readCommand(command);

		index++;
		input >> word;
		strcpy_s(command, "");
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