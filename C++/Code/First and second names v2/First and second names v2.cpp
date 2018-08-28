/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : First and second names v2
 * @created     : Wednesday Jul 25, 2018 00:28:53 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Please enter your first and second names:\n" << endl;
    string first;
    string second;
    cin >> first >> second;
    string name = first + ' ' + second;
    cout << "Hello, " << name << endl;
    return 0;
}

