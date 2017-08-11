#include <iostream>
#include <fstream>

#include "BinarySortedTree.h"

int main(int argc, char** argv)
{
	argv[1] = "binary.txt";
	argc = 2;
	
	if (argc != 2)
	{
		std::cout << "Pls read the instructions thx" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1], std::ios::in | std::ios::binary);

	BinarySortedTree<char*> alpha;

	int key;
	int dataSize = 0;

	char* data = nullptr;

	while(true)
	{
		input.read((char*)&key, sizeof(int));

		input.read((char*)&dataSize, sizeof(int));

		data = new char[dataSize + 1];
		input.read(data, dataSize);
		data[dataSize] = 0;
		
		if (!input.eof())
		{
			alpha.vine_insert(key, data);
		}
		else
		{
			break;
		}
	}

	alpha.balance_DSW();

	char* commandName = new char[10];
	int inputKey;
	char* inputKeyString = new char[15];
	char* inputData = new char [200];

	int i = 0;
	int j = 0;

	char* commandLine = new char [201];

	// interface part //

	// keep in mind it's not 100% idiot proof 
	while (!(std::cin.eof()))
	{
		i = 0;
		j = 0;

		// commenting this comment in case of automatisation
		// std::cout << "Give query: \n0: exit \n1: add <key> <data> \n2: remove <key> <data> \n3: removeall <key> \n4: search <key> <data>\n";
		
		
		std::cin.getline(commandLine, 200);

		int commandLineSize = strlen(commandLine);

		// get command's name
		while (commandLine[i] != ' ' && i <= commandLineSize)
		{
			commandName[j++] = commandLine[i++];
		}
		commandName[j] = 0;
		i++;
		j = 0;

		// stop if something has messed up with the input
		if (i > commandLineSize)
		{
			continue;
		}

		// get key
		while (commandLine[i] != ' ' && i <= commandLineSize)
		{
			inputKeyString[j++] = commandLine[i++];
		}
		inputKeyString[j] = 0;

		// beware this will set inputKey to 0 if the string isnt a number
		inputKey = atoi(inputKeyString);

		i++;
		j = 0;

		// read data if command requires it
		if (strcmp(commandName, "removeall") != 0)
		{
			while (commandLine[i] != 0)
			{
				inputData[j++] = commandLine[i++];
			}
			inputData[j] = 0;
		}

		// choose command and execute
		if (strcmp(commandName, "add") == 0)
		{
			alpha.add(inputKey, inputData);
		}
		else if (strcmp(commandName, "remove") == 0)
		{
			alpha.remove(inputKey, inputData);
		}
		else if (strcmp(commandName, "removeall") == 0)
		{
			alpha.remove_all(inputKey);
		}
		else if (strcmp(commandName, "search") == 0)
		{
			alpha.search(inputKey, inputData);
		}
	}

	return 0;
}


//std::ofstream output("binary.txt", std::ios::out | std::ios::binary);
//char* text = "asss";
//
//if (!output.is_open())
//{
//	std::cout << "Something fucked up" << std::endl;
//	return 1;
//}
//int a = 97;
//int b = sizeof(text);
//for (int i = 2; i <= 32; i++)
//{
//	output.write((char*)&i, sizeof(int));
//	output.write((char*)&b, sizeof(int));
//	output.write(text, b);
//}
//output.close();