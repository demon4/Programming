/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : First name and Age
 * @created     : Tuesday Jul 24, 2018 18:21:09 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Please enter you first name and age:\n";
    string first_name;
    int age;
    cin >> first_name;
    cin >> age;
    cout << "Hello, " << first_name << "(" << age << ")\n";
}

