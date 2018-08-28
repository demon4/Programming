/**
 * @author      : Jens (jens.swedish@gmail.com)
 * @file        : Money sizes
 * @created     : Tuesday Jul 31, 2018 01:53:09 Coordinated Universal Time
 */

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() 
{
    double pennies, nickels, dimes, quarters, half_dollars, whole_dollar;
    cout << "|V|Find out how much cash you have|V|" << endl;
    cout << " <How many pennies do you have?>: ";
    cin >> pennies;
    cout << " <How many nickels do you have?>: ";
    cin >> nickels;
    cout << " <How many dimes do you have?>: ";
    cin >> dimes;
    cout << " <How many quarters do you have?>: ";
    cin >> quarters;
    cout << " <How many half dollars do you have?>: ";
    cin >> half_dollars;
    cout << " <How many dollars do you have?>: ";
    cin >> whole_dollar;
    double cents = ((pennies)+(nickels*5)+(dimes*10)+(quarters*25)+(half_dollars*50)+(whole_dollar*100));
    double dollars = cents/100;
    cout << " <You have " << cents << " cents>" << endl << " <The total amount of money you have is ($" << dollars << ")>" << endl;
    return 0;
}

