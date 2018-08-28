/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Double to Int
 * @created     : Wednesday Jul 25, 2018 23:36:38 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Double To Int Conversion:" << endl;
    double d;
    while(cin >> d){
            cout << d << " trancuted to " << (int)d << endl;
    }
    return 0;
}

