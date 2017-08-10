#include <iostream>
#include <fstream>

#include "BinarySortedTree.h"

int main(int argc, char** argv)
{
	//std::ofstream output("binary.txt", std::ios::out | std::ios::binary);

	//if (!output.is_open())
	//{
	//	std::cout << "Something fucked up" << std::endl;
	//	return 1;
	//}
	//int a = 97;
	//int b = 80;
	//output.write((char*)&a, sizeof(int));

	//output.write((char*)&b, sizeof(int));
	//output.close();

	//std::ifstream input("binary.txt", std::ios::in | std::ios::binary);

	//input.read((char*)a, sizeof(int));

	//std::cout << a << " " << b << std::endl;

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

	while (true)
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
	} 

	alpha.balance_DSW();


	return 0;
}