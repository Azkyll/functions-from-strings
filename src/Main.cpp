#include <functions.hpp>

using namespace functions;

int main()
{

	std::vector<std::string> exp_2cos = { "exp", "2cos", "x" };
	func_dd exp_2cos_x = fromBuffer(exp_2cos);

	func_dd double_cos = [](double x) { return 2 * std::cos(x); };
	func_dd exp_2cos_reference = compose2(functions::exp, double_cos);

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << exp_2cos_x(i) << "\n"
				  << exp_2cos_reference(i) << std::endl;
	}



	return 0;
}