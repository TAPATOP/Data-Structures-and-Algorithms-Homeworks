#pragma once

////////////////
// A Binary Search Tree that uses Day Stout Warren for balancing
////////////////

#include <iostream>

template <typename T>
class BinarySortedTree
{
private: struct node;

public:
	BinarySortedTree();

	// adds an element; I don't really need to copy the data so i'll just point to the object
	void add(int key, T& data); 

	// builds a binary search tree whose nodes are right only, e.g. a list, i know insertion in this
	// way is slower but i cant dedicate time to make it work by converting a tree to a vine
	void vine_insert(int key, T& data);

	void search(int key, T& data);
	bool remove(int key, T& data);
	void remove_all(int key);

	void balance_DSW();

	~BinarySortedTree();
private:
	void left_rotate(int key, T& data);

	// returns the parent node cause it might also be needed( saves a pointer from each node)
	node* find_node(int key, T& data, node*& parentNode);

	node* find_node(int key, node*& parentNode);
	bool remove(int key);
private:
	struct node
	{
		node(int key, T& data) : key(key), data(data) { nodesCount++; }

		~node() 
		{ 
			nodesCount--; 
			if (left != nullptr) delete left;
			if (right != nullptr) delete right;
		}

		node* left = nullptr;
		node* right = nullptr;
		T data;
		int key;

		static int nodesCount;
	};

	node* first;
};

// if this is in the cpp file it throws an error ???
template <>
inline typename BinarySortedTree<char*>::node* BinarySortedTree<char*>::find_node(int key, char*& data, node*& parentNode)
{
	parentNode = nullptr;
	node* currentNode = first;

	while (currentNode != nullptr && !(currentNode->key == key && !strcmp(currentNode->data, data)))
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
