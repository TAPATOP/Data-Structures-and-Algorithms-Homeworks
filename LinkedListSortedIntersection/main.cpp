/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 6.1
* @compiler VC
*
*/


//
// /brief
// This program implements a very simple linked list, creates two linked lists of that same type using variables for easier testing
// and then sorts their intersection into a new dynamically allocated list using list_sort().
// /struct node
// Nodes which are used to create a very basic linked list. It doesnt even have any methods( including a user- defined destructor)
// because it's just a makeshift list that exists only to show that list_sort() works.
// /list_sort()
// Takes two addressess of the first elements of two lists. Dynamically creates a new list and includes all the elements that are
// present in both given lists(intersection). Keep in mind that the new list does not save multiple copies of the same value( e.g. does not
// contain nodes holding the same data) since that's what I understand by "intersection". Returns the address of the first node
// of the new list.
//

#include <iostream>

struct node
{
	node* next;
	double data;
};

node* list_sort(node* firstList, node* secondList)
{
	node* firstListCurrent = firstList;
	node* secondListCurrent = secondList;

	node* newList = new node();
	node* newListCurrent = newList;
	bool newListIsEmpty = 1;

	while (firstListCurrent != nullptr)
	{
		while (secondListCurrent != nullptr)
		{
			if (firstListCurrent->data == secondListCurrent->data)
			{
				if (newListIsEmpty)
				{
					newList->data = firstListCurrent->data;
					newListIsEmpty = 0;
					break;
				}
				node* newNode = new node();
				newNode->data = firstListCurrent->data;

				node* parent = nullptr;

				newListCurrent = newList;

				while (newListCurrent != nullptr && newListCurrent->data <= newNode->data)
				{
					parent = newListCurrent;
					newListCurrent = newListCurrent->next;
				}

				if (newListCurrent != nullptr && newListCurrent->data == newNode->data)
				{
					delete newNode;
					break;
				}

				if (parent != nullptr && parent->data == newNode->data)
				{
					delete newNode;
					break;
				}

				if (parent == nullptr)
				{
					newList = newNode;
				}
				else
				{
					parent->next = newNode;
				}

				if (newListCurrent == nullptr)
				{
					parent->next = newNode; // redundant but more readable(?)
				}
				else
				{
					newNode->next = newListCurrent;
				}

				break;
			}
			secondListCurrent = secondListCurrent->next;
		}
		secondListCurrent = secondList;
		firstListCurrent = firstListCurrent->next;
	}

	if (newListIsEmpty)
	{
		delete newList;
		return nullptr;
	}

	return newList;
}

int main()
{
	node firstList, secondList;

	double valueOne1 = 2;
	double valueOne2 = 1;
	double valueOne3 = 4;
	double valueOne4 = 3;
	double valueOne5 = 9.1;
	
	double valueTwo1 = 3;
	double valueTwo2 = 2;
	double valueTwo3 = 1;
	double valueTwo4 = 9.1;
	double valueTwo5 = 0;

	firstList.data = valueOne1;
	firstList.next = &(node());
	firstList.next->data = valueOne2;

	firstList.next->next = &(node());
	firstList.next->next->data = valueOne3;

	firstList.next->next->next = &(node());
	firstList.next->next->next->data = valueOne4;

	firstList.next->next->next->next = &(node());
	firstList.next->next->next->next->data = valueOne5;

	
	secondList.data = valueTwo1;
	secondList.next = &(node());
	secondList.next->data = valueTwo2;
	
	secondList.next->next = &(node());
	secondList.next->next->data = valueTwo3;
	
	secondList.next->next->next = &(node());
	secondList.next->next->next->data = valueTwo4;
	
	secondList.next->next->next->next = &(node());
	secondList.next->next->next->next->data = valueTwo5;

	node* newList = list_sort(&firstList, &secondList);
	node* newListCurrent = newList;
	
	while (newListCurrent != nullptr)
	{
		std::cout << newListCurrent->data << std::endl;
		newListCurrent = newListCurrent->next;
	}

	return 0;
}