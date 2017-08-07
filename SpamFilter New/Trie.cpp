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
#include "Trie.h"

const int headNumber = 100;

Trie::Trie()
{
	headNodes = new Node*[headNumber];
	lastValues = new int[headNumber];
	isWorking = new bool[headNumber];
	hasReachedAnEnd = new bool[headNumber];
	valueCollected = new bool[headNumber];
		
	for (int i = 0; i < headNumber; i++)
	{
		headNodes[i] = &rootNode;
		lastValues[i] = 0;
		isWorking[i] = 0;
		hasReachedAnEnd[i] = 0;
		valueCollected[i] = 1;
	}

	isWorking[0] = 1;
	indexOfLastActivatedHead = 0;
}

void Trie::insert(char* entry, int value)
{
	Node* currentNode = &rootNode;
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
		// decides which letter we're checking for( 0th position of array next is ' ', 1 = 'a', 2 = 'b'...)
		//

		if (currentNode->next[index] == nullptr)
		{
			currentNode->next[index] = new Node();// creates new node if one hasn't already been created
		}

		currentNode = currentNode->next[index];
	}

	currentNode->endOfWord = true;
	currentNode->value = value;
}
//
// whatever is passed for "entry" must be a legit word/phrase composited of spaces and small Latin letters only
//

void Trie::insertViaFile(std::ifstream& file)
{
	unsigned const int maxSizeOfLine = 5000;
	// reason for this const is to easily make changes in case they are needed, 
	// hopefully we won't need more than 5000 character long dictionary entries

	char input[maxSizeOfLine];
	char word[maxSizeOfLine];
	char value[20];

	unsigned int wordSize = 0;
	unsigned int valueSize = 0;

	while (true)
	{
		file.getline(input, maxSizeOfLine);
		input[file.gcount()] = '\0';

		for (int i = 0; input[i]; i++)
		{
			if (input[i] != ' ') // by definition the vocabulary will not have anything different from ' ', letters and numbers
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
					value[valueSize] = input[i];
					valueSize++;
				}
			}
		}
		// entire part above is responsible for separating words from values

		if(wordSize > 0) word[wordSize - 1] = '\0';

		value[valueSize] = '\0';
		wordSize = 0;
		valueSize = 0;
		insert(word, charArrToInt(value));
	
		input[0] = 0;
		word[0] = 0;
		value[0] = 0;
		// the above 4 lines are responsible for resetting the buffers

		


		if (file.eof()) break;
		file.clear();
	}
}
//
//	enriches the vocabulary using a properly formatted file
// 	does not work for phrases whose words are separated by more than one whitespace character
//

int Trie::searchInFile(std::ifstream& file)
{
	unsigned const int maxLineSize = 100000;
	bool symbolTracker = 0; // 0 for symbol, 1 for letter
	unsigned int wordCount = 0;
	char* newInput = new char[maxLineSize];
	char lastLetterOfInput = ' ';
	// if letter is indeed a letter, this becomes 1, if not, becomes 0
	// for each change a word is counted
	
	// 0 -> gate successfully passed
	// -1 -> whitespace gate passed, searching for phrase -> activate new head; GET VALUE
	// 1 -> letter gate not passed -> return last value and continue normal search with other heads [HEAD STOPS]
	// 2 -> whitespace gate not passed -> return last value and continue normal search [HEAD STOPS]
	// -2 -> whitespace not passed but node is END( e.g. complete match) -> get value and destroy all heads if all left ones are disabled
	// 3(1) -> given symbol is not a letter/whitespace -> end word, return value if existant [HEAD STOPS]
	short status;
	while (true)
	{

		file.getline(newInput, maxLineSize - 1);

		for (unsigned int i = 0; newInput[i]; i++)
		{
			if (newInput[i] < 'a' || newInput[i] > 'z')
			{
				if (symbolTracker == 1)
				{
					symbolTracker = 0;
					wordCount++;
				}
			}
			else
			{
				symbolTracker = 1;
			}

			for (int j = 0; j <= indexOfLastActivatedHead; j++)
			{
				if (isWorking[j])
				{
					status = giveLetterToHead(decapitalize(newInput[i]), j);
				}
			}

			if (isWhitespace(newInput[i]))
			{
				isWorking[++indexOfLastActivatedHead] = 1;
				
			}
			
			for (unsigned int j = 0; j <= indexOfLastActivatedHead; j++)
			{
				if (isWorking[j])
				{
					giveLetterToHead('5', j);
				}
			}
		}
		////cout << wordCount << endl; // almost working
		////cout << "AND THE LAST LETTER IS:" << lastLetterOfInput << endl;
		if (file.eof()) break;
		file.clear();
	}
	//giveLetterToHead(' ');
	////cout << "FINAALLL:" << lastValue << endl;
	////cout << "number of words is:" << wordCount << endl;
	return 0;
}

Trie::~Trie()
{
}
// if heads to the left aren't working and current head has stopped at an END, return the value
// if ^^^^ AND current head is at end of phrase AND next letter is a separator, KILL EVERYONE

// 0 -> gate successfully passed
// -1 -> whitespace gate passed, searching for phrase -(dealt with on the outside)> activate new head
// 1 -> letter gate not passed -()> return last value and continue normal search with other heads [HEAD STOPS] { should skip word somehow }
// 2 -> whitespace gate not passed -()> return last value and continue normal search [HEAD STOPS]
// -2 -> whitespace not passed but node is END( e.g. complete match) -> get value and destroy all heads if all left ones are disabled
// 3(1) -> given symbol is not a letter/whitespace -> end word, return value if existant [HEAD STOPS]
short Trie::giveLetterToHead(char letter, int i)
{
	if (notLetterNorWhitespace(letter))// anything that (isn't a number && is not a delimeter) is skipped
	{
		if (headNodes[i]->endOfWord)
		{
			lastValues[i] = headNodes[i]->value;// if it's a legit thing to do, this gets the value of an eventual word in the current node
			hasReachedAnEnd[i] = 1;
			isWorking[i] = 0;
		}
		headNodes[i] = &rootNode;// go back to start of tree, since current letter can not be within the dictionary anyway, so no use searching down the current branch

		//cout << "value saved: " << lastValues[i] << endl;
		valueCollected[i] = 0;

		return 1;// error code without flushing nor address change (used to be 3)
	}
	//
	// handled non- (letter/ whitespace)
	//



	short index;
	if (isWhitespace(letter))
	{
		index = 0;
		if (headNodes[i]->endOfWord == 1)
		{
			lastValues[i] = headNodes[i]->value;
			hasReachedAnEnd[i] = 1;
			valueCollected[0] = 0;
			////cout << "Last value changed!" << endl;//maybe here
		}
	}
	else
	{
		if (letter >= 97 && letter <= 122)//might want to delete the if
		{
			index = letter - 96;
		}
	}
	//
	// selected proper index to address the node array with
	//



	if (headNodes[i]->next[index])// if there is such a symbol in the node
	{
		headNodes[i] = headNodes[i]->next[index]; // move currentNode and wait for next letter

		if (isWhitespace(letter))
		{
			//cout << "value saved: " << lastValues[i] << endl;
			valueCollected[i] = 0;
			return -1;
		}
		//cout << letter << endl;
		return 0; // no error, word/phrase is matched
	}
	else
	{
		headNodes[i] = &rootNode;
		isWorking[i] = 0;

		if (isWhitespace(letter))
		{
			if (hasReachedAnEnd[i])
			{
				if (areLeftHeadsWorking(i))
				{
					//cout << "value saved: " << lastValues[i] << endl;
					valueCollected[i] = 0;
					return -2;
				}
				else
				{
					valueCollector(i);
					deactivateHeads();
					std::cout << lastValues[i] << std::endl; // case -2; part responsible for giving value
				}
			}
			//cout << "value saved: " << lastValues[i] << endl;
			valueCollected[i] = 0;
			return 2;// word ends and has no phrase
		}
		else
		{
			////cout << "value saved: " << lastValues[i] << endl; // migth be unneeded, bro
			//valueCollected[i] = 0;
			return 1;// word doesn't match the given letter; should save the value somehow
		}
	}
}

void Trie::statusHandler(short statusCode)
{

}

void Trie::deactivateHeads()
{
	for (int i = 0; i <= indexOfLastActivatedHead; i++)
	{
		headNodes[i] = &rootNode;
		lastValues[i] = 0;
		isWorking[i] = 0;
		hasReachedAnEnd[i] = 0;
		valueCollected[i] = 1;
	}
	indexOfLastActivatedHead = -1;
}

bool Trie::areLeftHeadsWorking(int index)
{
	for (int i = index; i >= 0; i--)
	{
		if (isWorking[i]) return 1;
	}
	return 0;
}

int Trie::valueCollector(unsigned int index)
{
	for (int i = 0; i < index; i++)
	{
		if (valueCollected[i] == 0)
		{
			std::cout << lastValues[i] << std::endl;
		}
	}
	return 0;
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
