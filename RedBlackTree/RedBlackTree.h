#pragma once

////////////////
// Please consider this is not a fully working RBT, since it doesnt support self- balancing deletion, it
// uses a standard Binary Search Tree-tier deletion
////////////////

#include <iostream>

class RedBlackTree
{
public:
	RedBlackTree();

	void insert(int key, void* data); // I don't really need to copy the data

	~RedBlackTree();
private:
	struct node
	{
		node(int key, void* data) : key(key) , data(data) {}

		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		void* data;
		int key;

		bool isRed = 1; // if (isRed == 0) the node is black
	};

	node* first;
};

