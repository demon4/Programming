// Array Increasment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int v[10] = { 0,1,2,3,4,5,6,7,8,9 };
	for (auto c : v) {
		cout << "[" << v[c] << "]";
	}
	cout << "\n";
	for (auto& x : v) {
		++x;
	}
	for (auto y = 0; y != 10; ++y) {
		cout << "[" << v[y] << "]";

	}
	cin.get();
    return 0;
}

