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

	if (isNumberAlreadyInTree(number)) return;

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
			//if (number == current->data) return;

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

void BinarySortedTree::addNumbersByString(char * text)
{
	int textSize = std::strlen(text);
	bool lastSymbolIsDelimeter = 0;

	if (text[textSize - 1] < '0' || text[textSize - 1] > '9')
	{
		lastSymbolIsDelimeter = 1;
	}

	int index = 0;
	int number = 0;
	bool isNegative = 0;

	char currentChar;

	while (text[index] != '\0')
	{
		currentChar = text[index];

		if (currentChar == '-')
		{
			isNegative = 1;
			index++;
			continue;
		}

		if ((currentChar >= '0' && currentChar <= '9'))
		{
			number = number * 10 + (int)(currentChar - '0');
		}
		else
		{
			if (isNegative) number = -number;

			addNumber(number);
			number = 0;
			isNegative = 0;
		}
		index++;
	}
	if (!lastSymbolIsDelimeter)
	{
		if (isNegative) number = -number;

		addNumber(number);
	}
}

unsigned int BinarySortedTree::numberOfSubtreesWithNNodes(unsigned int N)
{
	return checkNodeCount(first, N);
}

void BinarySortedTree::saveToFile(std::ofstream &outputFile)
{
	recursiveWriteToFile(first, outputFile);
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

bool BinarySortedTree::isNumberAlreadyInTree(int number)
{
	node* current = first;

	while (current != nullptr)
	{
		if (current->data == number)
		{
			return true;
		}
		if (number < current->data)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	return false;
}

void BinarySortedTree::recursiveWriteToFile(node * nodeAddress, std::ofstream& outputFile)
{
	if (nodeAddress == nullptr) return;
	outputFile << nodeAddress->data << " "; // I know it's slow :<
	
	recursiveWriteToFile(nodeAddress->left, outputFile);
	recursiveWriteToFile(nodeAddress->right, outputFile);
}
