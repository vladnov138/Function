#include "ProgramView.h"
#include "Models/Hiperbola.h"
#include "Models/Parabola.h"
#include "Models/Exponenta.h"
#include "Models/Polinom.h"


void ProgramView::ask_func_type(std::string type) {
	std::cout << "Введите тип функции: Parabola, Hiperbola, Exponenta, Polinom" << std::endl;
	std::cin >> type;
	for (int i = 0; i < type.length(); i++)
		type[i] = tolower(type[i]);
	if (type == "parabola" || type == "hiperbola" || type == "exponenta" || type == "polinom")
		show_input(points);
	else
		std::cout << "Не разпознана функция" << std::endl;
}

void ProgramView::show_input(std::vector<double> points) {
	if (type != "polinom") {
		std::cout << "Введите коэффициент K" << std::endl;
		std::cin >> k;
	}
	else {
		std::cout << "Введите коэффиценты полинома через пробел" << std::endl;
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
	std::cout << "Доступны следующие функции: min_f, max_f, f, dif, integral" << std::endl;
	std::string func;
	std::cin >> func;
	if (func == "min_f" || func == "max_f") {
		std::string points;
		std::cout << "Введите диапазон: " << std::endl;
		std::cin >> x1 << x2;
		if (func == "min_f")
			
	}
}