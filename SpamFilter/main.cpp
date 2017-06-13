#include<iostream>
#include<fstream>

#include"Trie.h"

using namespace std;

int main()
{
	Trie alpha;

	ifstream input("file.txt");
	ifstream vocabulary("vocabulary.txt");

	alpha.insertViaFile(vocabulary);
	
	alpha.searchInFile(input);

	return 0;
}
