/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Order Strings
 * @created     : Monday Jul 30, 2018 23:10:37 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<iomanip>
using namespace std;

int main() 
{
    // the best way of ordering objects is with std::sort(&array[0], &array[max]) and take inputs as a array this is a example on how to improve on Order Numbers program
    const int max_strings = 3;
    string cont[max_strings];
    cout << "Please enter three words to check the order:" << endl;
    cout << " > ";
    cin >> cont[0] >> cont[1] >> cont[2];
    sort(&cont[0], &cont[max_strings]);    
    for(auto i : cont){
            if(i == cont[sizeof(cont)/sizeof(cont[0]) - 1]){
                    cout << i << endl;
            }
            else{
                    cout << i << ", ";
            }
    }
    return 0;
}

