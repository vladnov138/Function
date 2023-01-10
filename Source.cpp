#include <iostream>
#include <vector>

#include "./Models/Function.h"
#include "./Models/Parabola.h"
#include "./Models/Polinom.h"
#include "./Models/Exponenta.h"

using namespace std;

int main() {
	vector<double> vec;
	vec.push_back(20.0 / 7.0);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(-4);
	vec.push_back(-1);
	vec.push_back(2);
	vec.push_back(2);
	Polinom<double> a(vec);
	cout << a.min_f(-1, 0);
}