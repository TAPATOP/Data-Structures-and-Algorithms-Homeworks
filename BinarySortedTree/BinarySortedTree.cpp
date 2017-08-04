#include "BinarySortedTree.h"



BinarySortedTree::BinarySortedTree()
{
	first = nullptr;
}

void BinarySortedTree::addNumber(int number)
{
	if (first == nullptr)
	{
		first = new node(number);
		return;
	}

	node* current = first;
	bool addToLeft = 0;

	while (true)
	{
		if (number < current->data)
		{
			if (current->left == nullptr)
			{
				current->nodesBelow++;
				addToLeft = 1; // readability
				break;
			}
			else // better readability(?)
			{
				current->nodesBelow++;
				current = current->left;
			}
		}
		else
		{
			if (number == current->data) return;

			if (current->right == nullptr)
			{
				current->nodesBelow++;
				addToLeft = 0; // readability
				break;
			}
			else
			{
				current->nodesBelow++;
				current = current->right;
			}
		}
	}

	if (addToLeft)
	{
		current->left = new node(number);
	}
	else
	{
		current->right = new node(number);
	}
}

unsigned int BinarySortedTree::numberOfSubtreesWithNNodes(unsigned int N)
{
	return checkNodeCount(first, N);
}


BinarySortedTree::~BinarySortedTree()
{
}

unsigned int BinarySortedTree::checkNodeCount(node * address, unsigned int N)
{
	if(address == nullptr || address->nodesBelow < N) return 0;
	if (address->nodesBelow == N) return 1;

	return checkNodeCount(address->left, N) + checkNodeCount(address->right, N);
	// recursion is bad for your health ;(
}
