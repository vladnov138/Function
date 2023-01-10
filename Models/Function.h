#pragma once

class ValueException {};

template <class T, class X>
class Function
{
protected:
	T k = 1;
public:
	virtual double f(X x) = 0;
	virtual double min_f(X x1, X x2) = 0;
	virtual double max_f(X x1, X x2) = 0;
	virtual double integral(X x) = 0;
	virtual double dif(X x) = 0;
	virtual void set_k(T k) = 0;
	virtual T get_k() = 0;
};

