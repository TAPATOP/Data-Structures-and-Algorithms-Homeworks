
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
	void insertViaFile(std::ifstream&);

	int searchInFile(std::ifstream&);

	~Trie();
private:
	short giveLetterToHead(char letter, int index);// the reason this is of type short is to return error codes which is more than what bool can support
	void statusHandler(short statusCode);
	void deactivateHeads();
	bool areLeftHeadsWorking(int index);
	int valueCollector(unsigned int index);

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
	Node rootNode;

	Node** headNodes;			   
	int* lastValues;			   
	bool* isWorking;				   
	bool* hasReachedAnEnd;		   
	int indexOfLastActivatedHead;  
	bool* valueCollected;
};
char decapitalize(char);// used to make sure all letters are small before they are checked for in the trie
bool isWhitespace(char);// delimeters are whatever ' ' can be replaced by and still match a dictionary word
bool isWordSeparator(char);// whatever means a word should be counted. no idea which are those is whatsoever
bool notLetterNorWhitespace(char);
int charArrToInt(char* word);
//void bufferHandler(char* buffer, unsigned int& buffersize, unsigned int bufferPos, unsigned int maxBufferSize);
