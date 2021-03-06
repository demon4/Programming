// Proceed Promt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

bool accept() {
	cout << "Do you want to proceed (y / n)?\n";
	char answer = 0;
	cin >> answer;
	if (answer == 'y') {
		return true;
	}
	return false;
}
bool accept2() {
	cout << "Do you want to proceed (y / n)?\n";
	char answer = 0;
	cin >> answer;
	switch (answer)
	{
	case 'y':
		return true;
	case 'n':
		return false;
	default:
		cout << "I'll take that for a no.\n";
		return false;
	}
}
bool accept3() {
	auto tries = 1;
	while (tries < 4)
	{
		cout << "Do you want to proceed (y / n)?\n";
		char answer = 0;
		cin >> answer;
		switch (answer)
		{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			cout << "I don't understand that.\n";
			++tries;
		}
	}
	cout << "I'll take that for a no.\n";
	return false;
}

int main()
{
	cout << accept() << endl;
	cout << accept2() << endl;
	cout << accept3() << endl;
	cin.get();
	return 0;
}