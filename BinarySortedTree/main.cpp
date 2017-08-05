/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 6.2
* @compiler VC
*
*/

// This program reads a text, converts it's numbers to ints( anything different than a number and a '-' is considered
// a delimeter)

#include<iostream>
#include<fstream>

#include"BinarySortedTree.h"

int main(int argc, char** argv)
{
	std::ifstream input;
	input.open("file2.txt");

	BinarySortedTree alpha;

	char buffer[1050];

	int readCharsSize = 1024;
	int additionalReadSize = 0;
	unsigned int extracted = 0;

	while (input.read(buffer, readCharsSize) || input.gcount() != 0)
	{
		additionalReadSize = 0;
		extracted = (unsigned int)input.gcount();

		if (input.eof())
		{
			buffer[extracted] = '\0';
		}
		else
		{
			// this while takes care of the cases where a number has been sliced while reading; reads byte by byte
			while (buffer[(readCharsSize + additionalReadSize) - 1] != ' ' && buffer[(readCharsSize + additionalReadSize) - 1] != '\n')
			{
				additionalReadSize++;
				input.get(buffer[(readCharsSize + additionalReadSize) - 1]);
				if (input.eof()) break;
			}
			buffer[readCharsSize + additionalReadSize] = '\0';
		}
		alpha.addNumbersByString(buffer);
	}
	
	// "Amount of subtrees" part below
	int N;
	
	std::cout << "N = "; std::cin >> N;
	
	std::cout << alpha.numberOfSubtreesWithNNodes(N) << std::endl;

	return 0;
}