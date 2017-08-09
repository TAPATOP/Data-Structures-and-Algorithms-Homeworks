#include "BinarySortedTree.h"



BinarySortedTree::BinarySortedTree()
{
	first = nullptr;
}

// inserts without rebalancing
void BinarySortedTree::tree_insert(int key, void * data)
{
	////////////////////
	// TREE INITIALIZATION
	////////////////////

	if (first == nullptr)
	{
		first = new node(key, data);
		return;
	}

	/////////////////////
	// FIND NEW NODE ADDRESS
	/////////////////////

	node* currentNode = first;
	node* parentNode = currentNode;

	while (currentNode != nullptr)
	{
		parentNode = currentNode;
		if (key < currentNode->key)
		{
			currentNode = currentNode->left;
		}
		else
		{
			currentNode = currentNode->right;
		}
	}

	/////////////////
	// NODE CREATION AND INSERTION
	/////////////////

	node* newNode = new node(key, data);

	if (key < parentNode->key)
	{
		parentNode->left = newNode;
	}
	else
	{
		parentNode->right = newNode;
	}
	newNode->parent = parentNode;
}

void BinarySortedTree::vine_insert(int key, void * data)
{
	if (first == nullptr)
	{
		first = new node(key, data);
		return;
	}

	node* currentNode = first;
	node* parentNode = nullptr;

	while (currentNode != nullptr)
	{
		if (key > currentNode->key)
		{
			parentNode = currentNode;
			currentNode = currentNode->right;
		}
		else
		{
			break;
		}
	}


	node* newNode = new node(key, data);
	// if the newNode has a smaller key than the first node
	if (parentNode == nullptr)
	{
		newNode->right = first;
		first = newNode;
	}
	else
	{
		newNode->right = parentNode->right;
		parentNode->right = newNode;
	}
}


BinarySortedTree::~BinarySortedTree()
{
}
