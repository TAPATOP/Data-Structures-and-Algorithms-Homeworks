#pragma once

////////////////
// Please consider this is not a fully working RBT, since it doesnt support self- balancing deletion, it
// uses a standard Binary Search Tree-tier deletion
////////////////

#include <iostream>

class BinarySortedTree
{
public:
	BinarySortedTree();

	void tree_insert(int key, void* data); // I don't really need to copy the data
	void vine_insert(int key, void* data); // builds a binary search tree whose nodes are right only

	~BinarySortedTree();
private:
	struct node
	{
		node(int key, void* data) : key(key) , data(data) {}

		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		void* data;
		int key;
	};

	node* first;
};

