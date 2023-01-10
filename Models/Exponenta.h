#pragma once
#include "Function.h"
#include "Math.h"

template <class T, class X>
class Exponenta :
    public Function<T, X>
{
private:
	T k;
public:
	Exponenta();
	Exponenta(T k);
	double f(X x) override;
	double min_f(X x1, X x2) override;
	double max_f(X x1, X x2) override;
	double integral(X x) override;
	double dif(X x) override;
	void set_k(T k) override;
	T get_k() override;
};

template <class T, class X>
Exponenta<T, X>::Exponenta(T k) {
	set_k(k);
}

template <class T, class X>
void Exponenta<T, X>::set_k(T k) {
	this->k = k;
}

template <class T, class X>
T Exponenta<T, X>::get_k() {
	return k;
}

template <class T, class X>
double Exponenta<T, X>::f(X x) {
	double e = 1 + x;
	const int n = 30;
	Math math;
	for (int i = 2; i <= n; i++) {
		e += pow(x, i) / math.fact(i);
	}
	return k * e;
}

template <class T, class X>
double Exponenta<T, X>::integral(X x) {
	return k * log(x);
}

template <class T, class X>
double Exponenta<T, X>::dif(X x) {
	return -k * 1 / (x * x);
}


template <class T, class X>
double Exponenta<T, X>::min_f(X x1, X x2) {
	return f(x1) >= f(x2) ? f(x2) : f(x1);
}

template <class T, class X>
double Exponenta<T, X>::max_f(X x1, X x2) {
	return f(x1) >= f(x2) ? f(x1) : f(x2);
}