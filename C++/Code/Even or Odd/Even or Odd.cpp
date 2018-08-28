/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Even or Odd
 * @created     : Tuesday Jul 31, 2018 00:44:07 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    int number;
    cout << "Enter number to check if it is Even or Odd: " << endl;
    cout << " > ";
    while(cin >> number){
        cout << " <";
        cout << ((number % 2) ? "Odd" : "Even") << ">" << endl;
        cout << " > ";
    }
    return 0;

}

