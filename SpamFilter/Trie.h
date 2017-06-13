#pragma once

#include<fstream>
#include<iostream>

using namespace std;

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

	void insert(char* word, int number);// make sure whatever is passed here is a legit word/phrase composited of spaces and small Latin letters only
	void insertViaFile(ifstream&);

	int searchInFile(ifstream&);

	~Trie();

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
	Node* currentNode;
	int lastValue;

	short giveLetterToTree(char);// the reason this is of type short is to return error codes which is more than what bool can support
};
char decapitalize(char);// used to make sure all letters are small before they are checked for in the trie
bool isWhitespace(char);// delimeters are whatever ' ' can be replaced by and still match a dictionary word
bool isWordSeparator(char);// whatever means a word should be counted. no idea which are those is whatsoever
bool notLetterNorWhitespace(char);
int charArrToInt(char* word);
