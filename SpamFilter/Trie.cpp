#include "Trie.h"


Trie::Trie()
{
	currentNode = &rootNode;
	lastValue = 0;
}

void Trie::insert(char* entry, int number)
{
	unsigned short index;

	for (int i = 0; entry[i]; i++)
	{
		if (entry[i] == ' ')
		{
			index = 0;
		}
		else
		{
			index = entry[i] - 96;
		}
		// 
		// decides which letter we're checking for( 0th position of array next is ' ')
		//

		if (currentNode->next[index] == nullptr)
		{
			currentNode->next[index] = new Node();// creates new node if one hadn't already been created
		}

		currentNode = currentNode->next[index];
	}

	currentNode->endOfWord = true;
	currentNode->value = number;
	currentNode = &rootNode;
}
//
// whatever is passed for "entry" must be a legit word/phrase composited of spaces and small Latin letters only
//

void Trie::insertViaFile(ifstream& file)
{
	unsigned const int maxSizeOfLine = 5000;
	// reason for this const is to easily make changes in case they are needed, 
	//hopefully we won't need more than 5000 character long dictionary entries

	char* input = new char [maxSizeOfLine];
	char* word = new char[maxSizeOfLine]();
	char* number = new char[20]();

	unsigned int wordSize = 0;
	unsigned int numberSize = 0;

	while (true)
	{
		file.getline(input, maxSizeOfLine);

		for (int i = 0; input[i]; i++)
		{
			if (input[i] != ' ')
			{
				if (input[i] >= 'a' && input[i] <= 'z')
				{
					word[wordSize] = input[i];
					wordSize++;
					if (input[i + 1] == ' ')
					{
						word[wordSize] = ' ';
						wordSize++;
					}
				}
				else
				{
					number[numberSize] = input[i];
					numberSize++;
				}
			}
		}
		// entire part above is responsible for separating words from values

		word[wordSize-1] = '\0';
		number[numberSize] = '\0';
		wordSize = 0;
		numberSize = 0;
		// the above 4 lines are responsible for resetting the buffers

		insert(word, charArrToInt(number));

		if (file.eof()) break;
		file.clear();
	}
}
//
//	enriches the vocabulary using a properly formatted file
// 	does not work for phrases whose words are separated by more than one whitespace character
//

int Trie::searchInFile(ifstream& file)
{
	char letter;
	short errCode;
	unsigned long long int addressForRecheck = 0;

	while (file.get(letter))
	{
		//vvvvvvvv the part below operates using a letter vvvvvv
		errCode = giveLetterToTree(decapitalize(letter));

		if (errCode == 1 && addressForRecheck == 0)
		{
			char temp = file.peek();
			while (temp >= 97 && temp <= 122 && !file.eof())
			{
				file.get(temp);
			}
		}
		//
		//if (lastValue != 0)
		//{
		//	//cout << "Also, here, your value is:" << lastValue << endl;
		//	lastValue = 0;
		//}
		if (errCode != 0)
		{
			if (errCode == -1 && addressForRecheck == 0)
			{
				addressForRecheck = file.tellg();
				//cout << "Address saved!" << endl;
			}
			if ((errCode == 2 || errCode == 1) && addressForRecheck != 0)
			{
				file.seekg(addressForRecheck);
				addressForRecheck = 0;
				//cout << "Address loaded!" << endl;
			}
			if ((errCode == -2 || errCode == 3) && addressForRecheck != 0)
			{
				addressForRecheck = 0;
			}

			if ((errCode == -2 || errCode == 2 || errCode == 1) && lastValue != 0)
			{
				cout << "HELLO YES THIS IS VALUE:" << lastValue << endl;
				lastValue = 0;
			}
		}
		//
		////cout << lastValue << endl;
	}
	giveLetterToTree(' ');
	cout << "FINAALLL:" << lastValue << endl;
	return 0;
}

Trie::~Trie()
{
}

short Trie::giveLetterToTree(char letter)
{
	if (notLetterNorWhitespace(letter))// anything that (isn't a number && is not a delimeter) is skipped
	{
		if (currentNode->endOfWord)
		{
			lastValue = currentNode->value;// if it's a legit thing to do, this gets the value of an eventual word in the current node
		}
		currentNode = &rootNode;// go back to start of tree, since current letter can not be within the dictionary anyway, so no use searching down the current branch

		return 3;// error code without flushing nor address change
	}

	short index;
	if (isWhitespace(letter))
	{
		index = 0;
		if (currentNode->endOfWord == 1)
		{
			lastValue = currentNode->value;
			//cout << "Last value changed!" << endl;//maybe here
		}
	}
	else
	{
		if (letter >= 97 && letter <= 122)//might want to delete the if
		{
			index = letter - 96;
		}
	}

	if (currentNode->next[index])// if there is such a symbol in the node
	{
		currentNode = currentNode->next[index]; // move currentNode and wait for next letter
		//cout << (char)(index + 96) << endl;
		if (isWhitespace(letter))
		{
			return -1; // we have started searching for a phrase( since letter is a delimeter), so we have to save the current input address to recheck if the word is a standalone if phrase doesn't exist
		}
		return 0; // no error, word/phrase is matched
	}
	else
	{
		//cout << "Letter not found! Returning to root Node!" << endl;

		bool isAtEnd = currentNode->endOfWord;
		currentNode = &rootNode;
		if (isWhitespace(letter))
		{
			if (isAtEnd) return -2;
			return 2;// word ends and has no phrase, no flushing
		}
		else
		{
			return 1;// word doesn't match the given letter
		}
	}
}


char decapitalize(char letter)
{
	if (letter >= 65 && letter <= 90)
	{
		letter = letter + 32;
	}
	return letter;
}

bool isWhitespace(char letter)
{
	if (letter == ' ' || letter == '\n' || letter == '\t') return 1;
	return 0;
}
//
// delimeters are whatever ' ' can be replaced by and still match a dictionary word
//
bool isWordSeparator(char letter)
{
	if (!(letter>= 'a' && letter <= 'z'))
	{
		return 1;
	}
	return 0;
}

bool notLetterNorWhitespace(char letter)
{
	if ((letter < 97 || letter > 122) && !isWhitespace(letter))
	{
		return 1;
	}
	return 0;
}

int charArrToInt(char* word)//please dont try anything different than numbers here
{
	int number = 0;
	bool amNegative = 0;
	int i = 0;
	if (word[0] == '-')
	{
		amNegative = 1;
		i++;
	}
	for (; word[i]; i++)
	{
		number = number * 10 + (word[i] - 48);
	}
	if (amNegative)
	{
		number *= -1;
	}

	return number;
}