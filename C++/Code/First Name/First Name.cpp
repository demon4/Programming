/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : First Name
 * @created     : Monday Jul 23, 2018 20:54:35 Coordinated Universal Time
 */

#include <string>
#include <iostream>
using namespace std;

int main() 
{
    cout << "Please enter your first name (followed by 'enter'):\n";
    string first_name;
    cin >> first_name;
    cout << "Hello, " << first_name << "!\n";
    return 0;
}

