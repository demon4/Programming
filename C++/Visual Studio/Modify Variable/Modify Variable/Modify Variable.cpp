// Modify Variable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	auto x = 50;
	auto y = 40;
	x += y;
	++x;
	x -= y;
	--x;
	x *= y;
	x /= y;
	x %= y;
	// ((((((50+40)+1)-40)-1)*40)/40)%40 or 50+40+1-40-1*40/40%40
	cout << "x = " << x;
	cin.get();
	return 0;
}