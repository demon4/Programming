// Square.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
double square(double x) {
	return x * x;
}
void printSquare(double x) {
	cout << "the square of " << x << " is " << square(x) << "\n";
}

int main()
{
	printSquare(1.234);
	cin.get();
	return 0;
}