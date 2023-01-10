#pragma once
#include "Function.h"
#include <cmath>

template <class T, class X>
class Hiperbola :
    public Function<T, X>
{
private:
	T k;
public:
	Hiperbola();
	Hiperbola(T k);
	double f(X x) override;
	double min_f(X x1, X x2) override;
	double max_f(X x1, X x2) override;
	double integral(X x) override;
	double dif(X x) override;
	void set_k(T k) override;
	T get_k() override;
};

template <class T, class X>
Hiperbola<T, X>::Hiperbola(T k) {
	set_k(k);
}

template <class T, class X>
void Hiperbola<T, X>::set_k(T k) {
	this->k = k;
}

template <class T, class X>
T Hiperbola<T, X>::get_k() {
	return k;
}

template <class T, class X>
double Hiperbola<T, X>::f(X x) {
	if (x == 0)
		throw ValueException();
	return k / x;
}

template <class T, class X>
double Hiperbola<T, X>::integral(X x) {
	return k * log(x);
}

template <class T, class X>
double Hiperbola<T, X>::dif(X x) {
	return -k * 1 / (x * x);
}


template <class T, class X>
double Hiperbola<T, X>::min_f(X x1, X x2) {
	return min(f(x1), f(x2));
}

template <class T, class X>
double Hiperbola<T, X>::max_f(X x1, X x2) {
	return max(f(x1), f(x2));
}