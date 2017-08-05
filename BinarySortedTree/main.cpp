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

// /BST sort
// This program reads a text in 1024B - 1050B chunks, converts it's numbers to ints( anything different than a number and a '-' is 
// considered a delimeter) and sorts them in a binary sorted tree. 
// /repetition- free BST
// It makes sure there are no repetitions by going through the tree first to check whether it would meet a node 
// with the same value. This may seem like unneeded overhead but it removes issues with automatically counting 
// the number of children a node has( see below).
// /counts subtrees with exactly N nodes
// Saves the amount of nodes every node has while adding a number to the tree beneath it, so when we need 
// that info we can reach it fast. This removes the need of recursive counting of all children nodes. The children 
// node check is still recursive tho..
// /saves inplace
// Saves the sorted data in the same file it was loaded from( not necessarily in a sorted way) and separates entries with a " ".

#include<iostream>
#include<fstream>

#include"BinarySortedTree.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Read the instructions pls" << std::endl;
		return 1;
	}

	std::ifstream file;
	file.open(argv[1]);
	if (!file)
	{
		std::cout << "There is an issue with your file??" << std::endl;
		return 2;
	}

	BinarySortedTree alpha;

	char buffer[1050];

	int readCharsSize = 1024;
	int additionalReadSize = 0;
	unsigned int extracted = 0;

	while (file.read(buffer, readCharsSize) || file.gcount() != 0)
	{
		additionalReadSize = 0;
		extracted = (unsigned int)file.gcount();

		if (file.eof())
		{
			buffer[extracted] = '\0';
		}
		else
		{
			// this while takes care of the cases where a number has been sliced while reading; reads byte by byte
			while (buffer[(readCharsSize + additionalReadSize) - 1] != ' ' && buffer[(readCharsSize + additionalReadSize) - 1] != '\n')
			{
				additionalReadSize++;
				file.get(buffer[(readCharsSize + additionalReadSize) - 1]);
				if (file.eof()) break;
			}
			buffer[readCharsSize + additionalReadSize] = '\0';
		}
		alpha.addNumbersByString(buffer);
	}
	
	// "Amount of subtrees" part below
	int N;
	
	std::cout << "N = "; std::cin >> N;
	
	std::cout << alpha.numberOfSubtreesWithNNodes(N) << std::endl;

	file.close();

	// "Saving" part below
	std::ofstream output;
	output.open(argv[1]);

	alpha.saveToFile(output);

	return 0;
}