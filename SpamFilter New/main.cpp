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

	argv[1] = "vocabulary2.txt";
	argv[2] = "file.txt";
	argv[3] = "file1.txt";

	Trie alpha;

	std::ifstream fileToRead(argv[1]);

	alpha.insertViaFile(fileToRead);
	fileToRead.close();

	for (int i = 2; i < argc; i++)
	{
		fileToRead.open(argv[i]);
		std::cout << argv[i] << std::endl;
		alpha.searchInFile(fileToRead);
		fileToRead.close();
		std::cout << "-----------" << std::endl;
	}
	return 0;
}