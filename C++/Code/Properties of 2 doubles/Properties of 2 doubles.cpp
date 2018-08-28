/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Properties of 2 doubles
 * @created     : Friday Jul 27, 2018 13:33:55 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    double a = 0; 
    double b = 0; // using tenary operator ((condition) ? true-clause : false-clause) like ((a > b) ? a : b) aka short if statment
    cout << "Enter two doubles and this program will display different properties (a & b) \n > ";
    while(cin >> a >> b){ //enter first int then seperate with a space to enter second int
            cout << endl << " a = " << a << endl;
            cout << endl << " b = " << b << endl;
            if(a == b){
                cout << " (a and b) is of the equal value" << endl;
                cout << endl << " > ";
                continue;
            }
            cout << endl << " " << ((a > b) ? "a" : "b") << "(" << ((a > b) ? a : b) << ")" << " is the biggest" << endl; 
            cout << endl << " " << ((a < b) ? "a" : "b") << "(" << ((a < b) ? a : b) << ")" << " is the smallest" << endl;
            cout << endl << " " << "Sum of a(" << a << ")" << " + " << "b(" << b << ") " << "= " << a + b << endl;
            cout << endl << " " << "Difference of " << ((a > b) ? "a" : "b") << "(" << ((a > b) ? a : b) << ")" << " - " << ((a < b) ? "a" : "b") << "(" << ((a < b) ? a : b) << ")" << " = " << ((a > b) ? a : b) - ((a < b) ? a : b) << endl; 
            cout << endl << " " << "Product of a(" << a << ")" << " * " << "b(" << b << ") " << "= " << a * b << endl;
            cout << endl << " " << "Division of " << ((a > b) ? "a" : "b") << "(" << ((a > b) ? a : b) << ")" << " / " << ((a < b) ? "a" : "b") << "(" << ((a < b) ? a : b) << ")" << " = " << ((a > b) ? a : b) / ((a < b) ? a : b) << endl; 
            cout << endl << " > ";
    }
    return 0;
}

