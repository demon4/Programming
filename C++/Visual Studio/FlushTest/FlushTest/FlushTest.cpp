// FlushTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <ostream>      // std::flush
#include <fstream>      // std::ofstream

int main() {

	std::ofstream outfile("test.txt");

	for (int n = 0; n < 100; n++)
		outfile << n << std::flush;

	outfile.close();

	return 0;
}