// Comparison Operators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int x = 50;
	int y = 20;

	if (x == y) {
		cout << "x equals y" << endl;
	}
	if (x != y) {
		cout << "x does not equal y" << endl;
	}

	if (x < y) {
		cout << "x is less than y" << endl;
	}

	if (x > y) {
		cout << "x is greater than y" << endl;
	}

	if (x <= y) {
		cout << "x is less than or equal to y" << endl;
	}

	if (x >= y) {
		cout << "x is greater than or equal to y" << endl;
	}

	cin.get();
	return 0;
}