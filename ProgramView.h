#pragma once
#include "View.h"
#include <iostream>
#include <regex>

class ProgramView :
    public View
{
private:
    std::vector<double> points;
    std::string type;
    std::vector<double> points;
    int k;
    double x;
    double x1, x2;
public:
    void ask_func_type(std::string type) override;
    void show_input(std::vector<double> points) override;
    void ask_func() override;
    void input_points() override;
};

