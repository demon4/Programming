// Arithmetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int x = 50;
	int y = 20;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "x + y = " << x + y << endl;
	cout << "x - y = " << x - y << endl;
	cout << "+x - +y = " << +x - +y << endl;
	cout << "x - (-y) = " << x - -y << endl;
	cout << "x * y = " << x * y << endl;
	cout << "x % y = " << x % y << endl;
	cin.get();
	return 0;
}