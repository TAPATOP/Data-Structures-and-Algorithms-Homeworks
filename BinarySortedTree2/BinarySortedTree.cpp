#include "BinarySortedTree.h"

template <typename T>
int BinarySortedTree<T>::node::nodesCount;

template class BinarySortedTree<char*>; // this way I avoid putting everything in a single file

template <typename T>
BinarySortedTree<T>::BinarySortedTree()
{
	first = nullptr;
	node::nodesCount = 0;
}

// inserts without rebalancing
template <typename T>
void BinarySortedTree<T>::tree_insert(int key, T& data)
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
}

template <typename T>
void BinarySortedTree<T>::vine_insert(int key, T& data)
{
	////////////////////
	// VINE INITIALIZATION
	////////////////////

	if (first == nullptr)
	{
		first = new node(key, data);
		return;
	}
	
	/////////////////////
	// FIND newNode ADDRESS
	/////////////////////

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

	/////////////////
	// newNode CREATION AND INSERTION
	/////////////////

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

template <typename T>
void BinarySortedTree<T>::balance_DSW()
{
	if (first == nullptr)
	{
		std::cout << "You're trying to balance a nonexistant tree" << std::endl;
		return;
	}
	// calculate the number of nodes on the lowest level //

	int levelNodes = 1;
	int remainingNodes = node::nodesCount;

	while (remainingNodes >= levelNodes)
	{
		remainingNodes -= levelNodes;
		levelNodes *= 2;
	}
	
	// rotate the nodes that will find themselves on the lowest level //

	node* currentNode = first;
	node* nextNode = nullptr;
	for (int i = 0; i < remainingNodes; i++)
	{
		nextNode = currentNode->right->right;
		left_rotate(currentNode->key, currentNode->data);
		currentNode = nextNode;
	}

	// rotate the remaining nodes //
	currentNode = first;
	while (currentNode != nullptr)
	{
		if (currentNode->right == nullptr)
		{
			nextNode = nullptr;
		}
		else
		{
			nextNode = currentNode->right->right;
		}

		left_rotate(currentNode->key, currentNode->data);
		currentNode = nextNode;
	}
}


template <typename T>
BinarySortedTree<T>::~BinarySortedTree()
{
}

template <typename T>
void BinarySortedTree<T>::left_rotate(int key, T& data)
{
	// gets parentNode and nodeForRotation //
	
	node* parentNode = nullptr;
	node* nodeForRotation = find_node(key, data, parentNode);

	// verifies you can rotate the found node //
	
	if (nodeForRotation == nullptr)
	{
		std::cout << "This node doesnt exist bro" << std::endl;
		return;
	}

	if (nodeForRotation->right == nullptr)
	{
		return; // you cant move the leftest node to the right?
	}

	// does the rotation //

	node* rightChild = nodeForRotation->right;
	node* rightChildsRight = rightChild->right;
	node* rightChildsLeft = rightChild->left;

	rightChild->left = nodeForRotation;
	nodeForRotation->right = rightChildsLeft;

	if (parentNode != nullptr)
	{
		if (parentNode->key < nodeForRotation->key)
		{
			parentNode->right = rightChild;
		}
		else
		{
			parentNode->left = rightChild;
		}
	}
	else
	{
		first = rightChild;
	}
}

template <typename T>
typename BinarySortedTree<T>::node* BinarySortedTree<T>::find_node(int key, T& data, node*& parentNode)
{
	parentNode = nullptr;
	node* currentNode = first;

	while (currentNode != nullptr && !(currentNode->key == key && currentNode->data == data) )
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

	return currentNode;
}
