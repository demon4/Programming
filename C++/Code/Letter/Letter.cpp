/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Letter
 * @created     : Thursday Jul 26, 2018 13:05:42 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    cout << "Enter your recipients name:" << endl;
    string name;
    string friend_name;
    char friend_sex;
    string letter;
    cin >> name;
    cout << "Enter your friends name:" << endl;
    cin >> friend_name;
    cout << "Enter your friends gender(m, f, o(ther)):" << endl;
    cin >> friend_sex;
    letter += "Dear " + name + ", \n";
    letter += "   i hope i commit die soon, \npreferbly by reverse bear trap how bout u,\ndo you want commit die, if so how?\n";
    letter += "Have you seen " + friend_name + " lately?";
    if(friend_sex == 'm'){
            letter += "if so ask him to quik snek suicidos";
    }
    else if(friend_sex == 'f'){
            letter += "if so ask her to politly snek sucidos 0 pain 100% effective";
    }
    else{
            letter += "\nGo fukin die there is only 2 genders and if you think you are the third go ahead live your little snowflake fantasy and belive you are special you fukin usless human trash";
    }
            
    cout << letter << endl;

    return 0;
}

