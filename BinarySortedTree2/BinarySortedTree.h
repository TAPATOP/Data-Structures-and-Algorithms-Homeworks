#pragma once

////////////////
// Please consider this is not a fully working RBT, since it doesnt support self- balancing deletion, it
// uses a standard Binary Search Tree-tier deletion
////////////////

#include <iostream>

template <typename T>
class BinarySortedTree
{
private: struct node;

public:
	BinarySortedTree();

	void add(int key, T& data); // I don't really need to copy the data
	void vine_insert(int key, T& data); // builds a binary search tree whose nodes are right only

	void search(int key, T& data);

	void remove(int key, T& data);

	void balance_DSW();

	~BinarySortedTree();
private:
	void left_rotate(int key, T& data);

	// returns the parent node cause it might also be needed( saves a pointer from each node)
	node* find_node(int key, T& data, node*& parentNode);
private:
	struct node
	{
		node(int key, T& data) : key(key), data(data) { nodesCount++; }

		~node() { nodesCount--; }

		node* left = nullptr;
		node* right = nullptr;
		T data;
		int key;

		static int nodesCount;
	};

	node* first;
};

