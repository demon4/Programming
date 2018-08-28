/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : constexpr
 * @created     : Sunday Aug 12, 2018 07:57:41 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
constexpr int maxo = 17;
const int sa = 10;
int useConstExpr(int n);
int useConst(int n);

int main() 
{

    cout << useConstExpr(4) << " " << useConst(7) << endl;
    return 0;
}

int useConstExpr(int n){
    return maxo+n; 
}
int useConst(int n){
    return sa+n;
}

