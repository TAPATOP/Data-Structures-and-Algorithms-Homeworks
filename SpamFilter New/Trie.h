
/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 3
* @compiler VC
*
*/
#pragma once

#include<fstream>
#include<iostream>

/*
This trie is originally intended to support only insertion
of words into the dictionary and searching in text directly
from a file. Other options such as delete and search in short text
might be implemented if time allows it or if immediate need 
emerges.
*/
class Trie
{
public:

	Trie();

	void insert(char* word, int value);// make sure whatever is passed here is a legit word/phrase composited of spaces and small Latin letters only
	void insert_via_file(std::ifstream&);

	float search_in_file(std::ifstream&);

	~Trie();
private:
	void pass_letter_to_head(int headIndex, char letter);
	void activate_head();
	void deactivate_head(int index);

	short transform_letter_to_index(char letter);

	void copy_head(int index1, int index2);
private:
	struct Node
	{
		Node* next[27];
		int value = 0;
		bool endOfWord = 0;
		Node()
		{
			for (int i = 0; i < 27; i++)
			{
				next[i] = nullptr;
			}
		}
	};
	Node* rootNode;

	struct head
	{
		Node* nodeOfHead;
		int lastValue = 0;
		bool isWorking = 0;
		bool hasRecognizedAWord = 0;
	};

	static const int headsLimit = 100;
	head heads[headsLimit];
	int numberOfWorkingHeads;
	int collectedValue = 0;
};

char decapitalize(char);// used to make sure all letters are small before they are checked for in the trie
bool isWhitespace(char);// delimeters are whatever ' ' can be replaced by and still match a dictionary word
int charArrToInt(char* word);
//void bufferHandler(char* buffer, unsigned int& buffersize, unsigned int bufferPos, unsigned int maxBufferSize);
