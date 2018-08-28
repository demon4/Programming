/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Repeted Words
 * @created     : Wednesday Jul 25, 2018 00:53:47 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Please enter different words (exit by (ctrl+z)+enter) aka EOF:" << endl;
    string prev = " ";
    string curr;
    while(cin>>curr){
            if(prev == curr){
                    cout << "repeated: " << curr << endl;
            }
    prev = curr;
    }
    return 0;
}

