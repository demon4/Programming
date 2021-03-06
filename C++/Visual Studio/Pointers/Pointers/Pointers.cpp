// Pointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	char v[6] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	char* p = &v[3]; //points to the addr of v[3] by usding &(addr symbol)
	char ps = v[3];

	// now if we change pointer p then the array v will change instead of the copy bcs we are refrencing by addr;
	*p = 'f';
	ps = 'e';

	cout << v[3] << endl;
	cin.get();

	return 0;
}
