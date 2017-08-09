#include "BinarySortedTree.h"

int BinarySortedTree::node::nodesCount;

BinarySortedTree::BinarySortedTree()
{
	first = nullptr;
	node::nodesCount = 0;
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
}

void BinarySortedTree::vine_insert(int key, void * data)
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

void BinarySortedTree::balance_DSW()
{
	//left_rotate
}


BinarySortedTree::~BinarySortedTree()
{
}

void BinarySortedTree::left_rotate(int key, void * data)
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

BinarySortedTree::node* BinarySortedTree::find_node(int key, void * data, node*& parentNode)
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
