#include "Math.h"

double Math::fast_pow(double num, int power) {
	if (power == 0) 
		return 1;
	if (power % 2 == 0)
		return fast_pow(num * num, power / 2);
	return num * fast_pow(num, power - 1);
}

double Math::fact(double num) {
	if (num == 2)
		return 2;
	return num * fact(num - 1);
}