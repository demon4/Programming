/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Compare First and second name
 * @created     : Wednesday Jul 25, 2018 00:35:13 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Please enter your first and second namesn\n";
    string first;
    string second;
    cin >> first >> second;
    if(first == second){
            cout << "that is the same name" << endl;
    }
    if(first < second){
            cout << first << " is alphabetically before " << second << endl;
    }
    if(first > second){
            cout << first << " is alphabetically after " << second << endl; 
    }
    
    return 0;
}

