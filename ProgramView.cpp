#include "ProgramView.h"
#include "Models/Hiperbola.h"
#include "Models/Parabola.h"
#include "Models/Exponenta.h"
#include "Models/Polinom.h"


void ProgramView::ask_func_type(std::string type) {
	std::cout << "������� ��� �������: Parabola, Hiperbola, Exponenta, Polinom" << std::endl;
	std::cin >> type;
	for (int i = 0; i < type.length(); i++)
		type[i] = tolower(type[i]);
	if (type == "parabola" || type == "hiperbola" || type == "exponenta" || type == "polinom")
		show_input(points);
	else
		std::cout << "�� ���������� �������" << std::endl;
}

void ProgramView::show_input(std::vector<double> points) {
	if (type != "polinom") {
		std::cout << "������� ����������� K" << std::endl;
		std::cin >> k;
	}
	else {
		std::cout << "������� ����������� �������� ����� ������" << std::endl;
		std::string input_points;
		std::cin >> input_points;
		std::regex rgx(R"(\d+)");
		for (std::sregex_token_iterator it{ type.begin(), type.end(), rgx }, end;
			it != end; it++) {
			points.push_back(std::stod(*it));
		}
	}
	ask_func();
}

void ProgramView::ask_func() {
	std::cout << "�������� ��������� �������: min_f, max_f, f, dif, integral" << std::endl;
	std::string func;
	std::cin >> func;
	if (func == "min_f" || func == "max_f") {
		std::string points;
		std::cout << "������� ��������: " << std::endl;
		std::cin >> x1 << x2;
		if (func == "min_f")
			
	}
}