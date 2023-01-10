#pragma once
#include "Function.h"
#include <vector>
#include <queue>

template <class X>
class Polinom
{
public:
	std::vector<X> x_vector;
	int power;
	double fastpow();
	int sturm(X x1, X x2);
public:
	Polinom();
	Polinom(std::vector<X> x_vector);
	double f(X x);
	double min_f(X x1, X x2);
	double max_f(X x1, X x2);
	std::vector<X> integral(X x, X C = 0);
	std::vector<X> dif();
	Polinom<X> operator % (Polinom a);
	void operator = (Polinom a);
};

template <class X>
Polinom<X>::Polinom(std::vector<X> x_vector) {
	for (int i = 0; i < x_vector.size(); i++)
		this->x_vector.push_back(x_vector[i]);
	power = x_vector.size() - 1;
}

template <class X>
double Polinom<X>::f(X x) {
	double y = 0;
	for (int i = 0; i < x_vector.size() - 1; i++) 
		y += x_vector[i] * pow(x, power - i);
	y += x_vector[x_vector.size() - 1];
	return y;
}

template <class X>
std::vector<X> Polinom<X>::integral(X x, X C) {
	std::vector<X> result;
	for (int i = 0; i < x_vector.size(); i++)
		result.push_back(x_vector[i] * pow(x, power - i + 1) / (power - i + 1));
	result.push_back(C);
	return result;
}

template <class X>
std::vector<X> Polinom<X>::dif() {
	std::vector<X> result;
	for (int i = 0; i < x_vector.size() - 1; i++)
		result.push_back(x_vector[i] * (power - i));
	return result;
}

template <class X>
double Polinom<X>::min_f(X x1, X x2) {
	std::vector<X> x_dif = dif();
	Polinom dif_polinom(x_dif);
	switch (power) {
	case 0:
		return x_vector[0];
	case 1:
		return f(x1) >= f(x2) ? f(x2) : f(x1);
	case 2:
		double d = x_dif[1] * x_dif[1] - 4 * x_dif[0] * x_dif[2];
		if (d < 0)
			throw ValueException();
		double min_val = f(x1) >= f(x2) ? f(x2) : f(x1);
		double point1_extreme = (-x_dif[1] - sqrt(d)) / (2 * x_dif[0]);
		if (point1_extreme >= x1 && point1_extreme <= x2 ||
			point1_extreme >= x2 && point1_extreme <= x1) {
			min_val = min_val >= f(point1_extreme) ? f(point1_extreme) : min_val;
		}
		double point2_extreme = (-x_dif[1] + sqrt(d)) / (2 * x_dif[0]);
		if (point1_extreme != point2_extreme && point2_extreme >= x1 && point2_extreme <= x2 ||
			point2_extreme >= x2 && point2_extreme <= x1) {
			min_val = min_val >= f(point2_extreme) ? f(point2_extreme) : min_val;
		}
		return min_val;
	}
	if (dif_polinom.power >= 3) {
		std::vector<X> x_values;
		std::queue<X> areas;
		X xn1 = x1;
		X xn2 = x2;
		int k = dif_polinom.sturm(x1, x2);
		while (x_values.size() != k) {
			X x_new = (xn1 + xn2) / 2;
			if (abs(dif_polinom.f(x_new)) <= 0.0001) {
				x_values.push_back(x_new);
				if (dif_polinom.sturm(xn1, xn2) == 1 && x_values.size() != k) {
					if (!areas.empty()) {
						xn1 = areas.front();
						areas.pop();
						xn2 = areas.front();
						areas.pop();
						x_new = (xn1 + xn2) / 2;
					}
				}
			}
			if (x_values.size() != k && dif_polinom.sturm(x_new, xn2) && dif_polinom.sturm(xn1, x_new)) {
				areas.push(x_new);
				areas.push(x2);
			}
			if (dif_polinom.sturm(xn1, x_new))
				xn2 = x_new;
			else if (dif_polinom.sturm(x_new, xn2))
				xn1 = x_new;
		}
		double min_val = f(x1) >= f(x2) ? f(x2) : f(x1);
		for (int i = 0; i < x_values.size(); i++) {
			min_val = f(x_values[i]) <= min_val ? f(x_values[i]) : min_val;
		}
		return min_val;
	}
}

template <class X>
int Polinom<X>::sturm(X x1, X x2) {
	int k1 = 0, k2 = 0;
	int last_sign1 = f(x1) >= 0 ? 1 : -1, 
		last_sign2 = f(x2) >= 0 ? 1 : -1;
	std::vector<X> dif_values = dif();
	Polinom dif_polinom(dif_values);
	if (last_sign1 * dif_polinom.f(x1) < 0) k1++;
	if (last_sign2 * dif_polinom.f(x2) < 0) k2++;
	last_sign1 = dif_polinom.f(x1) >= 0 ? 1 : -1;
	last_sign2 = dif_polinom.f(x2) >= 0 ? 1 : -1;
	Polinom temp = Polinom(*this) % dif_polinom;
	if (last_sign1* temp.f(x1) < 0) k1++;
	if (last_sign2* temp.f(x2) < 0) k2++;
	last_sign1 = temp.f(x1) >= 0 ? 1 : -1;
	last_sign2 = temp.f(x2) >= 0 ? 1 : -1;
	while (temp.power != 0 && dif_polinom.power != 0) {
		Polinom ttemp = temp;
		temp = dif_polinom % temp;
		dif_polinom = ttemp;
		if (last_sign1 * temp.f(x1) < 0) k1++;
		if (last_sign2 * temp.f(x2) < 0) k2++;
		last_sign1 = temp.f(x1) >= 0 ? 1 : -1;
		last_sign2 = temp.f(x2) >= 0 ? 1 : -1;
	}
	return k1 - k2;
}

template <class X>
Polinom<X> Polinom<X>::operator %(Polinom a) {
	std::vector<X> x_result = x_vector;
	int zeros_counter = 0;
	for (int i = 0; x_vector.size() - zeros_counter >= a.x_vector.size(); i++) {
		double div = a.x_vector[0] / x_result[i];
		for (int j = 0; j < a.x_vector.size(); j++) {
			x_result[j + i] -= a.x_vector[j] / div;
			if (abs(x_result[j + i]) <= 0.0001 && abs(x_vector[j + i]) > 0.0001) zeros_counter++;
		}
	}
	std::vector<X> res;
	for (int i = 0; i < x_result.size(); i++)
		if (!(res.size() == 0 && abs(x_result[i]) <= 0.0001))
			res.push_back(x_result[i] * -1);
	return Polinom<X>(res);
}

template <class X>
void Polinom<X>::operator = (Polinom a) {
	x_vector = a.x_vector;
	/*for (int i = 0; i < a.x_vector.size(); i++)
		x_vector[i] = a.x_vector[i];*/
	power = a.power;
}

template <class X>
double Polinom<X>::max_f(X x1, X x2) {
	std::vector<X> x_dif = dif();
	Polinom dif_polinom(x_dif);
	switch (power) {
	case 0:
		return x_vector[0];
	case 1:
		return f(x1) >= f(x2) ? f(x1) : f(x2);
	case 2:
		double d = x_dif[1] * x_dif[1] - 4 * x_dif[0] * x_dif[2];
		double max_val = f(x1) >= f(x2) ? f(x1) : f(x2);
		if (d >= 0) {
			double point1_extreme = (-x_dif[1] - sqrt(d)) / (2 * x_dif[0]);
			if (point1_extreme >= x1 && point1_extreme <= x2 ||
				point1_extreme >= x2 && point1_extreme <= x1) {
				max_val = max_val >= f(point1_extreme) ? max_val : f(point1_extreme);
			}
			double point2_extreme = (-x_dif[1] + sqrt(d)) / (2 * x_dif[0]);
			if (point1_extreme != point2_extreme && point2_extreme >= x1 && point2_extreme <= x2 ||
				point2_extreme >= x2 && point2_extreme <= x1) {
				max_val = max_val >= f(point2_extreme) ? max_val : f(point2_extreme);
			}
		}
		return max_val;
	}
	if (dif_polinom.power >= 3) {
		std::vector<X> x_values;
		std::queue<X> areas;
		X xn1 = x1;
		X xn2 = x2;
		int k = dif_polinom.sturm(x1, x2);
		while (x_values.size() != k) {
			X x_new = (xn1 + xn2) / 2;
			if (abs(dif_polinom.f(x_new)) <= 0.0001) {
				x_values.push_back(x_new);
				if (dif_polinom.sturm(xn1, xn2) == 1 && x_values.size() != k) {
					if (!areas.empty()) {
						xn1 = areas.front();
						areas.pop();
						xn2 = areas.front();
						areas.pop();
						x_new = (xn1 + xn2) / 2;
					}
				}
			}
			if (x_values.size() != k && dif_polinom.sturm(x_new, xn2) && dif_polinom.sturm(xn1, x_new)) {
				areas.push(x_new);
				areas.push(x2);
			}
			if (dif_polinom.sturm(xn1, x_new))
				xn2 = x_new;
			else if (dif_polinom.sturm(x_new, xn2))
				xn1 = x_new;
		}
		double max_val = f(x1) >= f(x2) ? f(x1) : f(x2);
		for (int i = 0; i < x_values.size(); i++) {
			max_val = f(x_values[i]) <= max_val ? max_val : f(x_values[i]);
		}
		return max_val;
	}
}