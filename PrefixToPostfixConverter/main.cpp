/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 1
* @compiler VC
*
*/

#include<iostream>
#include<fstream>
#include<iomanip>

#include"PseudoString.h"
#include"Stack.h"

PseudoString mirror(PseudoString& oldPseudoString)// should check size first
{
	int size = oldPseudoString.getSize();
	PseudoString newPseudoString = oldPseudoString;

	for (int i = 0, j = size - 1; i < size; i++, j--)
	{
		newPseudoString[j] = oldPseudoString[i];
	}

	return newPseudoString;
}
//
// mirrors the PseudoString
void wordSeparator(Stack<PseudoString>& stek, PseudoString& commands)
{
	int size = commands.getSize();
	PseudoString checkMe = "";

	for (int i = size - 1; i >= 0; i--)
	{
		if (commands[i] != ' ' && i != 0)
		{
			checkMe += commands[i]; // creates word
		}
		else
		{
			if (i == 0)
			{
				checkMe += commands[i]; // adds the last element of the task PseudoString
			}
			//
			// word is ready
			if (checkMe != "")
			{
				stek.push(mirror(checkMe)); // pushes the word, should add if (checkme != "")
			}
			checkMe = "";
		}
	}
}
//
// returns all words into the stack stek as separate elements that can be accessed by pop/top
bool isNumber(PseudoString& command)
{
	int i = 0;
	int size = command.getSize();
	int floatFlag = 0;

	if (command[0] == '-')
	{
		i++;
		if (command.getSize() == 1)
		{
			return 0;
		}
	}


	for (i; i < size; i++)
	{
		if (command[i] == '.') floatFlag++;
		if (!(command[i] >= '0' && command[i] <= '9') || floatFlag > 1)
		{
			return 0;
		}
	}

	return 1;
	/*
	if (command[0] == ' ') return 0;
	int counter = 0;

	if (command[0] == '-')
	{
		if (command.getSize() < 2) return 0;
		counter++;
	}

	short size = command.getSize();

	for (counter; counter < size; counter++)
	{
		if (!(command[counter] >= '0' && command[counter] <= '9'))
		{
			if(command[counter] != '.' && command[counter] != ' ') return 0; // 1 for (negative) number
		}
	}
	return 1;
	*/
}
bool isOperator(PseudoString& command)
{
	short size = command.getSize();

	for (int i = 0; i < size; i++)
	{
		if (command[i] >= '0' && command[i] <= '9' || command == " ")
		{
			return 0;
		}
	}
	return 1;
}
bool isOperator(char& command)
{
	if (command >= '0' && command <= '9' || command == ' ')
	{
		return 0;
	}
	return 1;
}
int checkSymbolOrNum(PseudoString& checkMe)
{
	if (isNumber(checkMe))
	{
		return 1;
	}
	else
	{
		if (isOperator(checkMe))
		{
			return 2;// 2 for operator
		}
		return 0;
	}
}
//check if the word is either an operator or a number

bool check_validity_of_task(PseudoString& task)
{
	int taskSize = task.getSize();
	PseudoString checkMe = "";
	int symcount = 0;
	int numcount = 0;
	for (int i = 0; i <= taskSize; i++)
	{
		if (task[i] != ' ' && i != taskSize)
		{
			checkMe += task[i];
		}
		else
		{
			if (checkMe != "")
			{
				switch (checkSymbolOrNum(checkMe))
				{
				case 0: return 0;
				case 1: numcount++; break;
				case 2: symcount++; break;
				}

				checkMe = "";
			}
		}
	}
	if (numcount != symcount + 1) return 0;
	return 1;
}
//
// makes sure all elements are actual operands/ operators
// and that the operands = operators + 1

bool prefixToPostfix(Stack<PseudoString>& stek, PseudoString& command)
{
	if (isNumber(command) )
	{
		if (command.getSize() > 0)
		{
			command += " ";
			stek.push(command);
		}
	}
	//
	// if the command is a number, it gets pushed here( above)

	else
	{
		PseudoString elem1 = stek.topNpop();
		PseudoString elem2 = stek.topNpop();

		if (elem1 == "well, it's an error" || elem2 == "well, it's an error") return 0;// should fix this... somehow..

		stek.push(elem1 + elem2 + command + " ");
	}
	return 1;
}
//
// converts the prefix command into postfix command into the only stek element

double useOperator(PseudoString& elem2, PseudoString& elem1, char& oper, bool& flag)
{
	switch (oper)
	{
	case '+': return pstod(elem1) + pstod(elem2);
	case '-': return pstod(elem1) - pstod(elem2);
	case '*': return pstod(elem1) * pstod(elem2);
	case '/': 
		if (pstod(elem2) == 0)
		{
			flag = 1;
			break;
		}
		return pstod(elem1) / pstod(elem2);
	default:
		flag = 1;
		return 0;
	}
	return 0;
}
char matchOperator(char& oper, PseudoString& operatorList)
{
	int size = operatorList.getSize();
	for (int i = 0; i < size; i += 6)
	{
		if (operatorList[i] == oper)
		{
			return operatorList[i + 2];
		}
	}
	return '0';
}
//
// finds out what the redefined operator does
bool calculatingPart(Stack<PseudoString>& stek, PseudoString& command, PseudoString& operatorList)
{
	if (isNumber(command))
	{
		stek.push(command);
	}
	//
	// if the word is a number, it gets pushed (above)
	else
	{
		if (command != "")
		{
			PseudoString elem1 = stek.topNpop();
			PseudoString elem2 = stek.topNpop();

			char oper = matchOperator(command[0], operatorList);

			if (oper == '0') return 0;

			bool flag = 0;

			double result = useOperator(elem1, elem2, oper, flag);

			if (flag) return 0;

			stek.push(to_PseudoString(result));
		}
	}
	return 1;
}
bool letsCalculateThePostfix(PseudoString& commands, PseudoString& operatorList)
{
	Stack<PseudoString> stek;
	Stack<PseudoString> separatedCommands;
	wordSeparator(separatedCommands, commands);

	while (!separatedCommands.isEmpty())
	{
		if (!calculatingPart(stek, separatedCommands.topNpop(), operatorList)) return 0;
	}
	operatorList = stek.top();
	return 1;
}

bool letsConvertIt(Stack<PseudoString>& stek, PseudoString& task)
{
	if (!check_validity_of_task(task))
	{
		return 0;
	}

	int size = task.getSize();
	PseudoString checkMe = "";

	for (int i = size - 1; i >= 0; i--)
	{
		if (task[i] != ' ' && i != 0)
		{
			checkMe += task[i]; // creates word
		}
		else
		{
			if (checkMe != "" || (i == 0 && task[i] != ' '))
			{
				if (i == 0 && task[i] != ' ')
				{
					checkMe += task[i]; // adds the last element of the task PseudoString
				}
				//
				// word is ready
				if (!prefixToPostfix(stek, mirror(checkMe))) return 0; // pushes the word

				checkMe = "";
			}
		}
	}
	return 1;
}
// converts the prefix command into a postfix command

int main(int argc, char** argv)
{
	Stack<PseudoString> stek;
	std::ifstream input;

	argv[1] = "commands.txt";
	argv[2] = "operators.txt";

	PseudoString commandsPath = argv[1];
	PseudoString operatorsPath = argv[2];


	char buffer[530];

	input.open(commandsPath.getText());
	
	PseudoString commands = ""; 

	while (!input.eof())
	{
		input.read(buffer, 512);
		buffer[input.gcount()] = '\0';
		commands += buffer;
		buffer[0] = '\0';
	}

	input.close();

	input.open(operatorsPath.getText());
	PseudoString operators = "";

	while (!input.eof())
	{
		input.read(buffer, 512);
		buffer[input.gcount()] = '\0';
		operators += buffer;
		buffer[0] = '\0';
	}

	//
	// files are read above this, thus giving the task/ command and operators
	//

	if (!letsConvertIt(stek, commands))
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
    //
	// PseudoString should be converted by now
	//

	PseudoString postfix = stek.topNpop();

	if (letsCalculateThePostfix(postfix, operators))
	{
		std::cout << postfix << std::endl;
		std::cout << std::fixed;
		std::cout << std::setprecision(5) << pstod(operators) << std::endl; // operators have actually been overwritten with the result
	}
	else
	{
		std::cout << "Error" << std::endl;
		return 2;
	}
	return 0;
}