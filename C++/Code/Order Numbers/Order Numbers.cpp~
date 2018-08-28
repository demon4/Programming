/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Order Numbers
 * @created     : Friday Jul 27, 2018 13:43:55 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    double number[3] = {};
    char type;
    double biggest;
    double smallest;
    double middle; 
    cout << "Please enter 3 numbers and specify order type (b(2s) s(2b) r(2r))" << endl;
    cout << " > ";
    cin >> number[0] >> number[1] >> number[2] >> type;
    if(number[0] == number[1] || number[1] == number[2] || number[2] == number[0] || type != 'b' || type != 's' || type != 'r'){
            cerr << " error: invalid input";
            return 0;
    }
    if(number[0] > number[1] && number[0] > number[2]){
           biggest = number[0];
    }
    if(number[1] > number[0] && number[1] > number[2]){
           biggest = number[1];
    }            
    if(number[2] > number[1] && number[2] > number[0]){
           biggest = number[2];
    }
    if(number[0] < number[1] && number[0] < number[2]){
           smallest = number[0];
    }
    if(number[1] < number[0] && number[1] < number[2]){
           smallest = number[1];
    }            
    if(number[2] < number[1] && number[2] < number[0]){
           smallest = number[2];
    }
    if(smallest == number[0] && biggest == number[2]){
           middle = number[1];
    }
    if(smallest == number[1] && biggest == number[2]){
           middle = number[0];
    }
    if(smallest == number[0] && biggest == number[1]){
           middle = number[2];
    }
    cout << "biggest = " << biggest << endl;
    cout << "middle = " << middle << endl;
    cout << "smallest = " << smallest << endl;
    cout << endl << " a = " << number[0] << endl 
         << endl << " b = " << number[1] << endl 
         << endl << " c = " << number[2] << endl
         << endl << " type = " << type;
    if(type == 'b'){
            cout << "Order: " << biggest << ", " << middle << ", " << smallest << ". " << endl;
    }
    if(type == 's'){
            cout << "Order: " << smallest << ", " << middle << ", " << biggest << ". " << endl;
    }
    if(type == 'r'){
            cout << "Order: " << middle << ", " << smallest << ", " << biggest << ". " << endl;
    }
    return 0;
}

