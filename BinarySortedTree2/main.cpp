#include <iostream>
#include <fstream>

#include "BinarySortedTree.h"

int main(int argc, char** argv)
{
	argv[1] = "file.txt";
	argc = 2;

	if (argc != 2)
	{
		std::cout << "Pls read the instructions thx" << std::endl;
		return 1;
	}

	BinarySortedTree alpha;

	int key1 = 3;
	int key2 = 1;
	int key3 = 2;
	int key4 = 4;
	int key5 = 5;

	int data = 5;

	alpha.vine_insert(key1, &data);
	alpha.vine_insert(key2, &data);
	alpha.vine_insert(key3, &data);
	alpha.vine_insert(key4, &data);
	alpha.vine_insert(key5, &data);

	alpha.left_rotate(key5, &data);
	return 0;
}