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

	std::ifstream input("file.txt", std::ios::in | std::ios::binary);

	BinarySortedTree<char*> alpha;

	int key;
	int dataSize = 0;

	char* data;

	do
	{
		input >> key;
		input >> dataSize;

		input.get(); // TODO: flushes empty space, must be removed when i start properly reading a binary file

		data = new char[dataSize + 1];
		data[dataSize] = 0;
		input.read(data, dataSize);
		if (!input.eof())
		{
			alpha.vine_insert(key, data);
		}
		else
		{
			break;
		}
	} while (true);

	alpha.balance_DSW();

	return 0;
}