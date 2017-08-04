#include<iostream>
#include<fstream>

#include"BinarySortedTree.h"

int main(int argc, char** argv)
{
	std::ifstream input;
	input.open("file.txt");

	BinarySortedTree alpha;
	int a;

	while (input >> a)
	{
		alpha.addNumber(a);
	}

	std::cout << alpha.numberOfSubtreesWithNNodes(0) << std::endl;

	return 0;
}