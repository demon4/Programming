// Count Occurrences.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int count_x(char* p, char x);

int main()
{
	char arraie[5] = { 'a', 'r', 'a', 'a', 'a' };
	char* pointer = arraie;
	char target = 'a';
	
	cout << count_x(pointer, target) << endl;
    return 0;
}
int count_x(char* p, char x) {
	if (p == nullptr) return 0;
	int count = 0;
	for (; *p != 0; ++p) { // no need to use a init since its a defined pointer thats in the argfs of function 
		if (*p == x) {
			++count;
		}
	}
	return count;
}