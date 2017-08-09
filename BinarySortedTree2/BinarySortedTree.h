#pragma once

////////////////
// Please consider this is not a fully working RBT, since it doesnt support self- balancing deletion, it
// uses a standard Binary Search Tree-tier deletion
////////////////

#include <iostream>

class BinarySortedTree
{
private: struct node;

public:
	BinarySortedTree();

	void tree_insert(int key, void* data); // I don't really need to copy the data
	void vine_insert(int key, void* data); // builds a binary search tree whose nodes are right only

	void balance_DSW();

	~BinarySortedTree();
//private: TODO
public:
	void left_rotate(int key, void* data);

	// returns the parent node cause it's also needed( saves a pointer from each node)
	node* find_node(int key, void* data, node*& parentNode);
private:
	struct node
	{
		node(int key, void* data) : key(key), data(data) { nodesCount++; }

		~node() { nodesCount--; }

		node* left = nullptr;
		node* right = nullptr;
		void* data;
		int key;

		static int nodesCount;
	};

	node* first;
};

