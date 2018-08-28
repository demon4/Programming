/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Input Calculator
 * @created     : Tuesday Jul 24, 2018 18:43:05 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Enter an expression ('+','-','*','/')" << endl;
    double numA;
    char Operator;
    double numB;
    double result;
    cout << ": ";
    cin >> numA >> Operator >> numB;
    switch(Operator){
	    case '+': result = numA + numB; break;
	    case '-': result = numA - numB; break;
	    case '*': result = numA * numB; break;
	    case '/': result = numA / numB; break;
    }
    
    cout << "= " << result << endl;
    return 0;
}

