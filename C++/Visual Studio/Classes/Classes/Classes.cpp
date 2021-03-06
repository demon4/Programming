// Classes.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
using namespace std;
double read_and_sum(int s);

class Vector {
public:
	Vector(int s) : elem{ new double[s] }, sz{ s } {}
	double& operator[](int i) { 
		if (i < 0||size() <= i) {
			throw out_of_range{ "Vector::operator[]" };
		}
		return elem[i];
	}
	int size() const { return sz; }
private:
	double* elem;
	int sz;
};

void f(Vector& v);

int main()
{
	Vector v(4);
	cout << read_and_sum(3) << endl;
	f(v);
	return 0;
}

double read_and_sum(int s) {
	Vector v(s);
	for (int i = 0; i != v.size(); ++i) {
		cin >> v[i];
	}
	double sum = 0;
	for (int i = 0; i != v.size(); ++i) {
		sum += v[i];
	}
	return sum;
}
void out_of_range_test(Vector& v) {
	try {
		v[v.size()] = 7;
	}
	catch(out_of_range){
		cerr << "error: out_of_range" << endl;
	}

}

