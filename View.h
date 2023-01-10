#pragma once
#include <string>
#include <vector>

class View
{
public:
	virtual void ask_func_type(std::string type) = 0;
	virtual void show_input(std::vector<double> point) = 0;
	virtual void ask_func(std::string func) = 0;
	virtual void input_points(std::vector<double> points) = 0;
};

