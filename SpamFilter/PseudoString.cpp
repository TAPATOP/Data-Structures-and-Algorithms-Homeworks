#include "PseudoString.h"


PseudoString::PseudoString()
{
	text = new char[1];
	//text[1] = NULL;
	size = 0;
}

PseudoString::PseudoString(char useMe)
{
	text = new char[2];
	text[0] = useMe;
	size++;
	text[size] = '\0';
}

PseudoString::PseudoString(char* useMe)
{
	int futureSize = 0;
	for (futureSize; useMe[futureSize]; futureSize++);

	text = new char[futureSize + 1];

	for (int i = 0; i < futureSize; i++)
	{
		text[i] = useMe[i];
	}

	text[futureSize] = NULL;
	size = futureSize;
}


PseudoString::PseudoString(PseudoString& oldOne)
{
	//delete[] text;

	size = oldOne.size;
	text = new char[size + 1];

	for (int i = 0; i < size; i++)
	{
		text[i] = oldOne.text[i];
	}

	text[size] = NULL;
}
//
// constructors end here
//

int PseudoString::getSize() const
{
	return size;
}

char* PseudoString::getText() const
{
	return text;
}
//
// getters end here
//

void PseudoString::setText(char* input)
{
	short newSize = 0;

	for (; input[newSize]; newSize++);

	delete[] text;
	text = new char[newSize + 1];
	size = newSize;

	for (int i = 0; i < newSize; i++)
	{
		text[i] = input[i];
	}

	text[newSize] = NULL;
}

PseudoString operator+(PseudoString const &left, PseudoString const &right) // not functional yet, should also swap the left/ right thingies
{
	PseudoString newOne;
	int newSize = 0;

	newOne.text = new char[right.size + left.size + 1];
	int i = 0;

	for (i; i < left.size; i++)
	{
		newOne.text[i] = left.text[i];
		newSize++;
	}

	for (i = 0; i < right.size; i++)
	{
		newOne.text[newSize] = right.text[i];
		newSize++;
	}

	newOne[newSize] = NULL;
	newOne.size = newSize;

	return newOne;
}
//
// operator + for PS
//

PseudoString operator+(PseudoString const& left, char const& right)
{
	PseudoString newOne;
	int newSize = 0;

	newOne.text = new char[left.size + 1 + 1];
	int i = 0;

	for (; i < left.size; i++)
	{
		newOne.text[i] = left.text[i];
		newSize++;
	}

	newOne.text[newSize] = right;
	newSize++;

	newOne[newSize] = NULL;
	newOne.size = newSize;

	return newOne;
}
PseudoString operator+(PseudoString const& left, char* const& right)
{
	PseudoString newOne;
	unsigned int newSize = 0;
	unsigned int rightSize = 0;
	unsigned int leftSize = left.size;

	for (; right[rightSize]; rightSize++);

	newOne.text = new char[leftSize + rightSize + 1];
	unsigned int i = 0;

	for (; i < leftSize; i++)
	{
		newOne.text[i] = left.text[i];
	}

	newSize = leftSize;

	unsigned int endSize = leftSize + rightSize;

	for (i=0; i < rightSize; i++)
	{
		newOne.text[newSize] = right[i];
		newSize++;
	}

	newOne[newSize] = NULL;
	newOne.size = newSize;

	return newOne;
}
PseudoString operator+(char const& left, PseudoString const& right)
{
	PseudoString newOne;
	int newSize = 0;

	newOne.text = new char[1 + right.size + 1];
	int i = 0;

	newOne.text[0] = left;
	newSize++;

	for (i = 0; i < right.size; i++)
	{
		newOne.text[newSize] = right.text[i];
		newSize++;
	}

	newOne[newSize] = NULL;
	newOne.size = newSize;

	return newOne;

}

void PseudoString::operator+=(PseudoString const& right)
{
	*this = *this + right;
}
void PseudoString::operator+=(char const& right)
{
	*this = *this + right;
}
void PseudoString::operator+=(char* const& right)
{
	*this = *this + right;
}
PseudoString& PseudoString::operator=(PseudoString const & Other)
{

	if( Other.size!=0) delete[] text;

	size = Other.size;
	text = new char[size + 1];

	for (int i = 0; i < size; i++)
	{
		text[i] = Other.text[i];
	}

	text[size] = NULL;

	return *this;
}
//
// = operator for PS
//
PseudoString& PseudoString::operator=(char const & Other)
{
	delete[] text;
	text = new char[2];
	text[0] = Other;
	text[1] = '\0';
	size = 1;

	return *this;
}
//
// operator for single char( yes, it deletes whatever was there prior)
//
PseudoString& PseudoString::operator=(char* const & Other)
{
	delete[] text;

	int futureSize = 0;

	for (futureSize; Other[futureSize]; futureSize++);

	text = new char[futureSize + 1];

	for (int i = 0; i < futureSize; i++)
	{
		text[i] = Other[i];
	}

	size = futureSize;
	text[size] = NULL;

	return *this;
}
//
// = operator for char*
//

ostream& operator<<(ostream& out, PseudoString& me)
{
	out << me.getText();
	return out;
}
//
// << operator
//
istream& operator>>(istream& input, PseudoString& me)
{
	char* a = new char [20];
	input >> a;
	me.setText(a);
	return input;
}
//
// >> operator
//

char PseudoString::operator [](int index) const
{
	return text[index];
}
char& PseudoString::operator[](int index)
{
	return text[index];
}
//
// [] overloading
//

bool operator== (const PseudoString &c1, const PseudoString &c2)
{
	if (c1.getSize() != c2.getSize()) return 0; // there is no sense in comparing arrays with different sizes
	
	int size = c1.getSize();

	for (int i = 0; i < size; i++)
	{
		if (c1[i] != c2[i]) return 0;
	}
	return 1;
}
//
// == for other PSs
//
bool operator== (const PseudoString &c1, const char* &c2)
{
	int c2Size = 0;

	for (c2Size; c2[c2Size]; c2Size++);
	{
		if (c1.getSize() != c2Size) return 0; // there is no sense in comparing arrays with different sizes
	}

	int size = c1.getSize();

	for (int i = 0; i < size; i++)
	{
		if (c1[i] != c2[i]) return 0;
	}
	return 1;
}
//
// == for char array
//

// TO DO





bool operator== (const PseudoString &c1, const char &c2)
{
	if (c1.getSize() != 1) return 0; // there is no sense in comparing arrays with different sizes

		if (c1[0] != c2) return 0;

	return 1;
}
//
// == for a char
//

bool operator!= (const PseudoString &c1, const PseudoString &c2)
{
	return !(c1 == c2);
}
bool operator!= (const PseudoString &c1, const char &c2)
{
	return !(c1 == c2);
}
bool operator!= (const PseudoString &c1, const char* &c2)
{
	return !(c1 == c2);
}

PseudoString::~PseudoString()
{
	delete[] text;
	text = new char[1];
	size = 0;
}

//
// class functions end here
//

double pstod(PseudoString& word)
{
	int actualNumber = 0;
	int i = 0;
	short flag = 1;

	if (word[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (word[i] != '.' && i < word.getSize())
	{
		actualNumber = actualNumber*10 + (int)(word[i]) - 48;
		i++;
	}
    
	double decimalPart = 0;
	i++;
	int power = 1;

	while (i < word.getSize())
	{
		double addMe = (int)word[i] - 48;

		for (int m = 0; m < power && addMe != 0; m++)
		{
			addMe /= 10;
		}
		decimalPart += addMe;
		i++;
		power++;
	}

	return flag * (actualNumber + decimalPart);
}


int psToInt(PseudoString& word)//please dont try anything different than numbers here
{
	return charArrToInt(word.getText());
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
PseudoString to_PseudoString(double const& d)
{
	char c[20];
	sprintf_s(c, "%lf", d);
	return c;
}