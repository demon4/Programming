// Enumerations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

enum class Color {
	red, blue, green
};
enum class Traffic_Light {
	green, yellow, red
};
Traffic_Light& operator++(Traffic_Light& t);
void printTrafficLight(Traffic_Light& t);



Traffic_Light light = Traffic_Light::red;

int main()
{
	for (;;) {	 //idk wtf i have created 
		printTrafficLight(++light);
		cin.get();
	}

    return 0;
}
void printTrafficLight(Traffic_Light& t) { // aka endless recursive function 
	switch (t)
	{
	case Traffic_Light::green:
		cout << "The Light is Green" << endl;
	case Traffic_Light::red:
		cout << "The Light is Red" << endl;
	case Traffic_Light::yellow:
		cout << "The Light is Yellow" << endl;
	}

}
Traffic_Light& operator++(Traffic_Light& ts) {
	switch (ts)
	{
	case Traffic_Light::green:	return ts = Traffic_Light::yellow;
	case Traffic_Light::yellow:	return ts = Traffic_Light::red;
	case Traffic_Light::red:	return ts = Traffic_Light::green;
	}
}
