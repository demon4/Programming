/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : unsf conversion
 * @created     : Wednesday Jul 25, 2018 22:21:20 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    int a = 20000;
    char c = a;
    int b = c;
    if(a != b){
            cout << "osps!: " << a << "!=" << b << endl;
    }
    else{
            cout << "Wow! We have large characters" << endl;
    }
    return 0;
}

