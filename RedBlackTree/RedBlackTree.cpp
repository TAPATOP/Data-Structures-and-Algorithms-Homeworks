#include "RedBlackTree.h"



RedBlackTree::RedBlackTree()
{
	first = nullptr;
}

void RedBlackTree::insert(int key, void* data)
{
	if (first == nullptr)
	{
		node* newNode = new node(key, data);
		first = newNode;
		return;
	}

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


RedBlackTree::~RedBlackTree()
{
}
