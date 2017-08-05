#pragma once

#include<iostream>
#include<fstream>

class BinarySortedTree
{
private: struct node;

public:
	BinarySortedTree();

	void addNumber(int number);
	void addNumbersByString(char* text);

	unsigned int numberOfSubtreesWithNNodes(unsigned int N);

	void saveToFile(std::ofstream& outputFile);

	~BinarySortedTree();
private:
	unsigned int checkNodeCount(node* address, unsigned int N);
	bool isNumberAlreadyInTree(int number);
	void recursiveWriteToFile(node* nodeAddress, std::ofstream &outputFile);
private:
	struct node
	{
		node(int number)
		{
			data = number; // constructor helps my lazyness
		}
		node* left = nullptr;
		node* right = nullptr;
		int data;
		unsigned int nodesBelow = 0;
	};
	node* first;
};

