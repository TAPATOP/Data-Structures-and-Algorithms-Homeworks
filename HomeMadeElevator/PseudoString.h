/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 2
* @compiler VC
*
*/

#pragma once
#include<iostream>

using namespace std;

class PseudoString
{
public:
	PseudoString();
	PseudoString(char);
	PseudoString(char*);
	PseudoString(PseudoString&);

	int getSize() const;
	char* getText() const;

	void setText(char*); 
	
	istream& getline(istream& is, string& str, char delim);
	istream& getline(istream& is, string& str);

	friend PseudoString operator+(PseudoString const& left, PseudoString const& right);
	friend PseudoString operator+(PseudoString const& left, char const& right);
	friend PseudoString operator+(char const& left, PseudoString const& right); 

	void operator+=(PseudoString const& right);
	void operator+=(char const& right);
	void operator+=(char* const& right);

	PseudoString& operator=(PseudoString const & Other);
	PseudoString& operator=(char const & Other);
	PseudoString& operator=(char* const & Other);

	friend ostream& operator<<(ostream& output, PseudoString& me);
	friend istream& operator>>(istream& intput, PseudoString& me);

	char operator [](int index) const;
	char & operator [](int index); 

	friend bool operator== (const PseudoString &c1, const PseudoString &c2);
	friend bool operator== (const PseudoString &c1, const char &c2);
	friend bool operator== (const PseudoString &c1, const char* &c2);

	friend bool operator!= (const PseudoString &c1, const PseudoString &c2);
	friend bool operator!= (const PseudoString &c1, const char &c2);
	friend bool operator!= (const PseudoString &c1, const char* &c2);

	~PseudoString();
	
private:
	char* text;
	int size;
};

double pstod(PseudoString&);
PseudoString to_PseudoString(double const& number);

