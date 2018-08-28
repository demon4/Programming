/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Word2Num
 * @created     : Tuesday Jul 31, 2018 01:17:49 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{ //TODO: make this program but for every number like five thousand three hundred and seventy five ---
    string input;
    cout << "Please enter a word for it to be converted to the corresponding number and wise versa(eg: two -> 2, 2 -> two):" << endl;
    cout << " > ";
    while(cin >> input){
        if(input == "zero"){
                cout << " <0>" << endl;
        }else if(input == "one"){
                cout << " <1>" << endl;
        }else if(input == "two"){
                cout << " <2>" << endl;
        }else if(input == "three"){
                cout << " <3>" << endl;
        }else if(input == "four"){
                cout << " <4>" << endl;
        }else if(input == "five"){
                cout << " <5>" << endl;
        }else if(input == "six"){
                cout << " <6>" << endl;
        }else if(input == "seven"){
                cout << " <7>" << endl;
        }else if(input == "eight"){
                cout << " <8>" << endl;
        }else if(input == "nine"){
                cout << " <9>" << endl;
        }else if(input == "1"){
                cout << " <one>" << endl;
        }else if(input == "2"){
                cout << " <two>" << endl;
        }else if(input == "3"){
                cout << " <three>" << endl;
        }else if(input == "4"){
                cout << " <four>" << endl;
        }else if(input == "5"){
                cout << " <five>" << endl;
        }else if(input == "6"){
                cout << " <six>" << endl;
        }else if(input == "7"){
                cout << " <seven>" << endl;
        }else if(input == "8"){
                cout << " <eight>" << endl;
        }else if(input == "nine"){
                cout << " <nine>" << endl;
        }else if(input == "0"){
                cout << " <zero>" << endl;
        }else{
                cout << " <Input Error> " << endl;
        }
        cout << " > ";
    }

    return 0;
}

