#include <iostream>
#include <fstream>

#include "BinarySortedTree.h"

int main(int argc, char** argv)
{
	//std::ofstream output("binary.txt", std::ios::out | std::ios::binary);
	//char* text = "asss";

	//if (!output.is_open())
	//{
	//	std::cout << "Something fucked up" << std::endl;
	//	return 1;
	//}
	//int a = 97;
	//int b = sizeof(text);
	//for (int i = 1; i < 10; i++)
	//{
	//	output.write((char*)&i, sizeof(int));
	//	output.write((char*)&b, sizeof(int));
	//	output.write(text, b);
	//}
	//output.close();

	//std::ifstream input2("binary.txt", std::ios::in | std::ios::binary);
	//
	//for (int i = 0; i < 9; i++)
	//{
	//	input2.read((char*)&a, sizeof(int));
	//	std::cout << a << " ";
	//	
	//	input2.read((char*)&a, sizeof(int));
	//	std::cout << a << " ";

	//	char* text = new char[a + 1];
	//	input2.read(text, a);
	//	text[a] = 0;
	//	std::cout << text << std::endl;
	//}

	// testing end //

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
	//while (true)
	//{
	//	input >> key;
	//	input >> dataSize;

	//	input.get(); // TODO: flushes empty space, must be removed when i start properly reading a binary file

	//	data = new char[dataSize + 1];
	//	data[dataSize] = 0;
	//	input.read(data, dataSize);
	//	if (!input.eof())
	//	{
	//		alpha.vine_insert(key, data);
	//	}
	//	else
	//	{
	//		break;
	//	}
	//} 

	alpha.balance_DSW();

	char* rdata = new char[2];
	rdata[0] = '1';
	rdata[1] = 0;

	int t = 1;
	int stop = 0;
	while (stop < 50000)
	{
		BinarySortedTree<int> test;
		for (int i = 0; i < 100; i++)
		{
			test.add(i, t);
		}
		stop++;
	}

	//for(int i = 0;; i++)
	//{
	//	alpha.add(69, rdata);
	//	alpha.remove(69, rdata);
	//}

	return 0;
}