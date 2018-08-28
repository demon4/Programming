/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : miles2km
 * @created     : Thursday Jul 26, 2018 15:56:41 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void converter(double &num, string &unit);
int main() 
{
    cout << "Enter a number in miles or kilometer then specify which unit it is (km, miles):" << endl;
    double num;
    string unit;
    while(cin >> num >> unit){
        converter(num, unit);
        cout << num << " " << unit << endl; 
    }
    return 0;
}
void converter(double &num, string &unit){
    if(unit == "km"){
        num /= 1.609;
        unit = "miles ";
    }
    else if(unit == "miles"){
        num *= 1.609;
        unit = "km ";
    }
    else{
        num = 0;
        unit = "invalid input";
    }
}
