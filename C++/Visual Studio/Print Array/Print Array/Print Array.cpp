// Print Array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int v[10] = { 0,1,2,3,4,5,6,7,8,9 };
	cout << "Printing Array v[]" << endl;
	for (auto x : v) {
		cout << v[x];
	}
	cout << "\nDone";
	cin.get();
    return 0;
}

