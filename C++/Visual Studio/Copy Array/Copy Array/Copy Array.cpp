// Copy Array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int v1[10] = { 0,1,2,3,4,5,6,7,8,9};
	int v2[10];
	cout << "Before" << endl << "v1 = ";
	for (auto x : v1) {
		cout << v1[x];
	}
	cout << endl << "v2 = null";
	cout << endl << "After" << endl;
	for (auto i = 0; i != 10; ++i) {
		v2[i] = v1[i];
	}
	cout << "v1 = ";
	for (auto x : v1) {
		cout << v1[x];
	}
	cout << endl << "v2 = ";
	for (auto x : v2) {
		cout << v2[x];
	}
	cin.get();
    return 0;
}

