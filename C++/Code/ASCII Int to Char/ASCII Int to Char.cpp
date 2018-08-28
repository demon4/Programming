/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : ASCII Int to Char
 * @created     : Wednesday Jul 25, 2018 21:17:23 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Input a number to display its ASCII value" << endl;
    int x;
    while(cin >> x){
       char c = x;
       cout << "The Number: " << x << " is a char(" << c << ")" << endl;
    }
    return 0;
}

