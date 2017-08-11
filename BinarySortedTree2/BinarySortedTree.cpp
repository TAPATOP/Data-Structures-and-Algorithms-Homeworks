#include "BinarySortedTree.h"
template <typename T>
int BinarySortedTree<T>::node::nodesCount;

template class BinarySortedTree<char*>; // this way I avoid putting everything in the header
template class BinarySortedTree<int>;

template <typename T>
BinarySortedTree<T>::BinarySortedTree()
{
	first = nullptr;
	node::nodesCount = 0;
}

// inserts without rebalancing
template <typename T>
void BinarySortedTree<T>::add(int key, T& data)
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

template<typename T>
void BinarySortedTree<T>::search(int key, T & data)
{
	node* trash = nullptr; // TODO: overload
	if (find_node(key, data, trash) != nullptr)
	{
		std::cout << "true" << std::endl;
		return;
	}
	std::cout << "false" << std::endl;
}

template<typename T>
bool BinarySortedTree<T>::remove(int key, T& data)
{
	// find the target node and it's parent //

	node* nodeForDeletionParent = nullptr;
	node* nodeForDeletion = find_node(key, data, nodeForDeletionParent);

	if (nodeForDeletion == nullptr)
	{
		std::cout << "false" << std::endl;
		return 0;
	}

	node* nodeForReplacement = nodeForDeletion;
	node* nodeForReplacementParent = nodeForReplacement;

	// find the node that will replace the deleted one //

	if (nodeForDeletion->right != nullptr)
	{
		nodeForReplacement = nodeForDeletion->right;

		while (nodeForReplacement->left != nullptr)
		{
			nodeForReplacementParent = nodeForReplacement;
			nodeForReplacement = nodeForReplacement->left;
		}
	}

	// node rotations //

	// if we are trying to delete the root
	if (nodeForDeletion == first)
	{
		// if the root doesnt have a right node
		if (nodeForDeletion->right == nullptr)
		{
			first = nodeForDeletion->left;
		}
		// if the root's right node doesnt have a left node
		else if (nodeForReplacementParent == nodeForDeletion && nodeForReplacement->left == nullptr)
		{
			nodeForReplacement->left = nodeForDeletion->left;
			first = nodeForReplacement;
		}
		// if the root's right node has a left node
		else
		{
			nodeForReplacementParent->left = nodeForReplacement->right;
			first = nodeForReplacement;
			nodeForReplacement->left = nodeForDeletion->left;
			nodeForReplacement->right = nodeForDeletion->right;
		}
	}
	else
	{
		// if the node for deletion doesnt have a right node
		if (nodeForDeletion->right == nullptr)
		{
			if (nodeForDeletionParent->right == nodeForDeletion)
			{
				nodeForDeletionParent->right = nodeForDeletion->left;
			}
			else
			{
				nodeForDeletionParent->left = nodeForDeletion->left;
			}
		}
		// if the node for deletion has a right node that doesnt have a left node
		else if (nodeForDeletion == nodeForReplacementParent)
		{
			if (nodeForDeletionParent->right < nodeForDeletion)
			{
				nodeForDeletionParent->right = nodeForReplacement;
			}
			else
			{
				nodeForDeletionParent->left = nodeForReplacement;
			}
			nodeForReplacement->left = nodeForDeletion->left;
		}
		// if the node for deletion has a right node and that has a left node
		else
		{
			nodeForReplacementParent->left = nodeForReplacement->right;
			if (nodeForDeletionParent->right < nodeForDeletion)
			{
				nodeForDeletionParent->right = nodeForReplacement;
			}
			else
			{
				nodeForDeletionParent->left = nodeForReplacement;
			}
			nodeForReplacement->left = nodeForDeletion->left;
			nodeForReplacement->right = nodeForDeletion->right;
		}
	}

	// prevent cascade deletion and then delete //
	nodeForDeletion->left = nullptr;
	nodeForDeletion->right = nullptr;
	delete nodeForDeletion;

	std::cout << "true" << std::endl;
	return 1;
}

template<typename T>
void BinarySortedTree<T>::remove_all(int key)
{
	int counter = 0;

	while (remove(key))
	{
		counter++;
	}

	std::cout << counter << std::endl;
}

template <typename T>
void BinarySortedTree<T>::balance_DSW()
{
	if (first == nullptr)
	{
		// std::cout << "You're trying to balance a nonexistant tree" << std::endl;
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

	// this is the actual number of nodes on the lowest full level
	levelNodes--;

	// rotate the nodes that will find themselves on the lowest level //

	node* currentNode = first;
	node* nextNode = nullptr;
	for (int i = 0; i < remainingNodes; i++)
	{
		nextNode = currentNode->right->right;
		left_rotate(currentNode->key, currentNode->data);
		currentNode = nextNode;
	}
	// notice that now we always have 2^n - 1 nodes as the "vine", where "n" is the depth of the lowest full level

	// rotate the remaining nodes //
	int counter = 0;
	currentNode = first;
	while (levelNodes > 1)
	{
		levelNodes /= 2;
		counter = 0;

		currentNode = first;

		while (currentNode != nullptr && counter < levelNodes)
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
			counter++;

			currentNode = nextNode;
		}
	}
}

template <typename T>
BinarySortedTree<T>::~BinarySortedTree()
{
	if (first != nullptr) delete first;
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
		// std::cout << "This node doesnt exist bro" << std::endl;
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

	while (currentNode != nullptr && !(currentNode->key == key && currentNode->data == data))
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

template<typename T>
typename BinarySortedTree<T>::node* BinarySortedTree<T>::find_node(int key, node *& parentNode)
{
	parentNode = nullptr;
	node* currentNode = first;

	while (currentNode != nullptr && !(currentNode->key == key) )
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

template<typename T>
bool BinarySortedTree<T>::remove(int key)
{
	// find the target node and it's parent //

	node* nodeForDeletionParent = nullptr;
	node* nodeForDeletion = find_node(key, nodeForDeletionParent);

	if (nodeForDeletion == nullptr)
	{
		// std::cout << "Deletion node doesnt exist" << std::endl;
		return 0;
	}

	node* nodeForReplacement = nodeForDeletion;
	node* nodeForReplacementParent = nodeForReplacement;

	// find the node that will replace the deleted one //

	if (nodeForDeletion->right != nullptr)
	{
		nodeForReplacement = nodeForDeletion->right;

		while (nodeForReplacement->left != nullptr)
		{
			nodeForReplacementParent = nodeForReplacement;
			nodeForReplacement = nodeForReplacement->left;
		}
	}

	// node rotations //

	// if we are trying to delete the root
	if (nodeForDeletion == first)
	{
		// if the root doesnt have a right node
		if (nodeForDeletion->right == nullptr)
		{
			first = nodeForDeletion->left;
		}
		// if the root's right node doesnt have a left node
		else if (nodeForReplacementParent == nodeForDeletion && nodeForReplacement->left == nullptr)
		{
			nodeForReplacement->left = nodeForDeletion->left;
			first = nodeForReplacement;
		}
		// if the root's right node has a left node
		else
		{
			nodeForReplacementParent->left = nodeForReplacement->right;
			first = nodeForReplacement;
			nodeForReplacement->left = nodeForDeletion->left;
			nodeForReplacement->right = nodeForDeletion->right;
		}
	}
	else
	{
		// if the node for deletion doesnt have a right node
		if (nodeForDeletion->right == nullptr)
		{
			if (nodeForDeletionParent->key < nodeForDeletion->key)
			{
				nodeForDeletionParent->right = nodeForDeletion->left;
			}
			else
			{
				nodeForDeletionParent->left = nodeForDeletion->left;
			}
		}
		// if the node for deletion has a right node that doesnt have a left node
		else if (nodeForDeletion == nodeForReplacementParent)
		{
			if (nodeForDeletionParent->key < nodeForDeletion->key)
			{
				nodeForDeletionParent->right = nodeForReplacement;
			}
			else
			{
				nodeForDeletionParent->left = nodeForReplacement;
			}
			nodeForReplacement->left = nodeForDeletion->left;
		}
		// if the node for deletion has a right node and that has a left node
		else
		{
			nodeForReplacementParent->left = nodeForReplacement->right;
			if (nodeForDeletionParent->key < nodeForDeletion->key)
			{
				nodeForDeletionParent->right = nodeForReplacement;
			}
			else
			{
				nodeForDeletionParent->left = nodeForReplacement;
			}
			nodeForReplacement->left = nodeForDeletion->left;
			nodeForReplacement->right = nodeForDeletion->right;
		}
	}

	// prevent cascade deletion and delete //

	nodeForDeletion->left = nullptr;
	nodeForDeletion->right = nullptr;
	delete nodeForDeletion;

	return 1;
}
