/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 3
* @compiler VC
*
*/
#include<iostream>
#include<fstream>

#include "Trie.h"

//tellg, seekg
int main(int argc, char** argv)
{
	argc = 3;

	argv[1] = "vocabulary1.txt";
	argv[2] = "file1.txt";
	argv[3] = "file1.txt";

	Trie alpha;

	std::ifstream fileToRead(argv[1]);

	alpha.insert_via_file(fileToRead);
	fileToRead.close();

	for (int i = 2; i < argc; i++)
	{
		fileToRead.open(argv[i]);
		if (!fileToRead.is_open())
		{
			std::cout << "There is something wrong with " << argv[i] << std::endl;
		}
		std::cout << argv[i] << std::endl;
		alpha.search_in_file(fileToRead);
		fileToRead.close();
		std::cout << "-----------" << std::endl;
	}
	return 0;
}