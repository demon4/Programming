#include "stdafx.h"
#include "Vector.h"
#include <cmath>
#include <iostream>
using namespace std;

double sqrt_sum(Vector& v) {
	double sum = 0;
	for (int i = 0; i != v.size(); ++i) {
		sum += sqrt(v[i]);
	}
	return sum;
}

int main() {
	Vector v(3);
	for (int i = 0; i != v.size(); ++i) {
		cin >> v[i];
	}
	cout << sqrt_sum(v);
}