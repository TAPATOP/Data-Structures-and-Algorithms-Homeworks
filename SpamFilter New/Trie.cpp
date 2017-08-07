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

const short letterError = 69;

Trie::Trie()
{
	rootNode = new Node;
	numberOfWorkingHeads = 0;
}

// adds words to the dictionary
// whatever is passed for "entry" must be a legit word/phrase composited of spaces and small Latin letters only
void Trie::insert(char* entry, int value)
{
	Node* currentNode = rootNode;
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

//	enriches the vocabulary using a >>> properly formatted <<< file
void Trie::insert_via_file(std::ifstream& file)
{
	unsigned const int maxSizeOfLine = 1024;
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

// searches for vocabulary words into the files
int Trie::search_in_file(std::ifstream& file)
{
	const int readSize = 1024;
	char text[readSize + 1];
	int textIndex = 0;

	activate_head();

	while (!file.eof())
	{
		// READING PART //
		text[0] = '\0';
		textIndex = 0;

		file.read(text, readSize);

		text[file.gcount()] = '\0';

		// HEAD WORK PART //

		// iterates all the letters
		while (text[textIndex] != '\0') 
		{
			// gives the current letter to all heads
			for (int i = 0; i < numberOfWorkingHeads; i++) 
			{
				// no reason to pass a letter to a non- working head
				if (heads[i].isWorking)
				{
					if (isWhitespace(text[textIndex]))
					{
						pass_letter_to_head(i, ' ');
					}
					else
					{
						pass_letter_to_head(i, text[textIndex]);
					}
				}
			}

			if (isWhitespace(text[textIndex]))
			{
				activate_head();
			}

			textIndex++;
		}

		for (int i = 0; i < numberOfWorkingHeads; i++)
		{
			pass_letter_to_head(i, ' ');
		}
	}
	return 0;
}

Trie::~Trie()
{

}

// passes letter to heads[headIndex] and kills heads based on what happens next
void Trie::pass_letter_to_head(int headIndex, char letter)
{
	// i'd rather copy an address instead of the object itself
	head* currentHead = &heads[headIndex]; 

	// the index used to address the letters in Nodes
	short letterIndexInNode = transform_letter_to_index(letter); 

	if (letter == ' ')
	{
		// if the current Node is an ending; we do this check only now cause letter is a delimeter
		if (currentHead->nodeOfHead->endOfWord)
		{
			// sets value according to dictionary entry
			currentHead->lastValue = currentHead->nodeOfHead->value;

			// has recognized a word
			currentHead->hasRecognizedAWord = 1; 
			
			// deactivates all heads to the right because this head has already found a match of all the 
			// current letters
			for (int i = headIndex + 1; i < numberOfWorkingHeads; i++)
			{
				deactivate_head(i);
			}

			// sets the number of working heads
			numberOfWorkingHeads = headIndex + 1;
		}
	}

	// if there is an entry of the current sequence of letters
	if (currentHead->nodeOfHead->next[letterIndexInNode] != nullptr)
	{
		// move to the next node
		currentHead->nodeOfHead = currentHead->nodeOfHead->next[letterIndexInNode];
	}
	else
	{
		// eject the value the head has stored so far if it has recognized a word
		if (currentHead->hasRecognizedAWord && headIndex == 0)
		{
			std::cout << currentHead->lastValue << std::endl;


			// move all of the nodes after the current one to the left by copying them one. by. one. It's retarded
			// but it will do the job, for now at least
			for (int i = headIndex; i < numberOfWorkingHeads - 1; i++)
			{
				copy_head(i, i + 1);
			}

			// reduce the number of working heads since the current one got overwritten and the last one
			// can be found twice in the heads array now
			numberOfWorkingHeads--;

			// deactivates the last head, which has a copy right before it
			deactivate_head(numberOfWorkingHeads);

			//while (!(heads[headIndex].isWorking) && (numberOfWorkingHeads > headIndex))
			//{
			//	if (currentHead->hasRecognizedAWord)
			//	{
			//		std::cout << currentHead->lastValue << std::endl;
			//	}
			//
			//	for (int i = headIndex; i < numberOfWorkingHeads - 1; i++)
			//	{
			//		copy_head(i, i + 1);
			//	}
			//
			//	numberOfWorkingHeads--;
			//	deactivate_head(numberOfWorkingHeads);
			//}

			// if there is an active head on( or after) the location of the recently overwritten head
			if (numberOfWorkingHeads > headIndex)
			{
				// pass the command to the head on the current place, because search_in_file() will skip it
				pass_letter_to_head(headIndex, letter);
			}
		}
	}
}

// prepares another head for work
void Trie::activate_head()
{
	head* currentHead = &heads[numberOfWorkingHeads];

	currentHead->isWorking = 1;
	currentHead->nodeOfHead = rootNode;
	currentHead->lastValue = 0;
	currentHead->hasRecognizedAWord = 0;

	numberOfWorkingHeads++;
}

// stops the head from working
void Trie::deactivate_head(int index)
{
	heads[index].isWorking = 0;
}

// [a-z] and ' ' only; letterError otherwise
short Trie::transform_letter_to_index(char letter)
{
	if (letter == ' ') return 0;
	if (letter >= 'a' && letter <= 'z') return letter - 96;

	return letterError;
}

// copies heads[index2] to heads[index1]
void Trie::copy_head(int index1, int index2)
{
	head* head1 = &heads[index1];
	head* head2 = &heads[index2];

	head1->isWorking = head2->isWorking;
	head1->nodeOfHead = head2->nodeOfHead;
	head1->lastValue = head2->lastValue;
	head1->hasRecognizedAWord = head2->hasRecognizedAWord;
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
