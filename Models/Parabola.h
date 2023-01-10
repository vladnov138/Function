#pragma once
#include "Function.h"

template <class T, class X>
class Parabola :
    public Function<T, X>
{
private:
    T k;
public:
    Parabola(T k);
	double f(X x) override;
	double min_f(X x1, X x2) override;
	double max_f(X x1, X x2) override;
	double integral(X x) override;
	double dif(X x) override;
	void set_k(T k) override;
	T get_k() override;
};

template <class T, class X>
Parabola<T, X>::Parabola(T k) {
	set_k(k);
}

template <class T, class X>
void Parabola<T, X>::set_k(T k) {
	this->k = k;
}

template <class T, class X>
T Parabola<T, X>::get_k() {
	return k;
}

template <class T, class X>
double Parabola<T, X>::f(X x) {
	return k * x * x;
}

template <class T, class X>
double Parabola<T, X>::integral(X x) {
	return k * x * x * x / 3;
}

template <class T, class X>
double Parabola<T, X>::dif(X x) {
	return 2 * k * x;
}

template <class T, class X>
double Parabola<T, X>::min_f(X x1, X x2) {
	int point = 0;
	bool isPointExtremeMin = k > 0;
	bool isExtremePointIncluded = 
		x1 <= point && x2 >= point || x2 <= point && x1 >= point;
	
	
	if (isExtremePointIncluded && isPointExtremeMin)
		return f(point);
	return f(x1) <= f(x2) ? f(x1) : f(x2);
}

template <class T, class X>
double Parabola<T, X>::max_f(X x1, X x2) {
	int point = 0;
	bool isPointExtremeMax = k < 0;
	bool isExtremePointIncluded = x1 <= point && x2 >= point || x2 <= point && x1 >= point;
	if (isExtremePointIncluded && isPointExtremeMax)
		return f(point);
	return f(x1) >= f(x2) ? f(x1) : f(x2);
}

