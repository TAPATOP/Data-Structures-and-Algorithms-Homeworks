#pragma once

#include"iostream"

class BinarySortedTree
{
private: struct node;

public:
	BinarySortedTree();

	void addNumber(int number);
	void addNumbersByString(char* text);

	unsigned int numberOfSubtreesWithNNodes(unsigned int N);

	~BinarySortedTree();
private:
	unsigned int checkNodeCount(node* address, unsigned int N);
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

