/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : First name and age v2
 * @created     : Tuesday Jul 24, 2018 18:55:39 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Please enter your first name and age:\n"; 
    string name = "???";
    int age = -1;
    cin >> name >> age;
    cout << "Hello, " << name << "(" << age << ")" << endl;
    return 0;
}

