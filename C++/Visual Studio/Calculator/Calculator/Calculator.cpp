// Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<char> textInput;
void write_vector(vector<char> &s);

int main()
{
	char input;
	while (cin >> input)
		textInput.push_back(input);
	write_vector(textInput);
    return 0;
}

void write_vector(vector<char> &s) {
	for (auto x = 0; x < s.size(); ++x) {
		cout << s[x] << " ";
	}
}
