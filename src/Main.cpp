#include <functions.hpp>

using namespace functions;

int main()
{

	std::vector<std::string> exp_2cos = { "exp", "2cos", "x" };
	func_dd exp_2cos_x = fromBuffer<double>(exp_2cos);

	func_dd double_cos = [](double x) { return 2 * std::cos(x); };
	func_dd exp_2cos_reference = compose2(functions::exp<double>, double_cos);

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << exp_2cos_x(i) << "\n"
				  << exp_2cos_reference(i) << std::endl;
	}

	std::cout << std::endl;

	func_ff exp_2cos_f = fromBuffer<float>(exp_2cos);

	func_ff double_cos_f = [](float x) { return 2 * std::cos(x); };
	func_ff exp_2cos_freference = compose2(functions::exp<float>, double_cos_f);

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << exp_2cos_f(i) << "\n"
				  << exp_2cos_freference(i) << std::endl;
	}


	return 0;
}