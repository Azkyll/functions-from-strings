#include <functional>
#include <iostream>

#define ZERO 48
#define ONE 49
#define NINE 57
#define LETTER_a 97
#define LETTER_z 122
#define LETTER_x 120
#define FULL_STOP 46





namespace functions
	{
	constexpr double PI = 3.141592653589793238462643;

	typedef std::function<double(double)> func_dd;
	func_dd id = [](double x) { return x; };

	func_dd exp = [](double x) { return std::exp(x); };
	func_dd log = [](double x) { return std::log(x); };

	func_dd cos = [](double x) { return std::cos(x); };
	func_dd sin = [](double x) { return std::sin(x); };
	func_dd tan = [](double x) { return std::tan(x); };

	func_dd cosh = [](double x) { return 0.5 * (std::exp(x) + std::exp(-x)); };
	func_dd sinh = [](double x) { return 0.5 * (std::exp(x) - std::exp(-x)); };
	func_dd tanh = [](double x) { return sinh(x) / cosh(x); };


	template <typename F0, typename... F>
	class Composer2
	{
		F0 f0_;
		Composer2<F...> tail_;

	public:
		Composer2(F0 f0, F... f) :
			f0_(f0),
			tail_(f...)
		{}

		template <typename T>
		T operator()(const T& x) const
		{
			return f0_(tail_(x));
		}
	};

	template <typename F>
	class Composer2<F>
	{
		F f_;

	public:
		Composer2(F f) :
			f_(f)
		{}

		template <typename T>
		T operator()(const T& x) const
		{
			return f_(x);
		}
	};

	template <typename... F>
	Composer2<F...> compose2(F... f)
	{
		return Composer2<F...>(f...);
	}

	inline std::string isolateInner(std::string s)
	{
		uint16_t start;
		uint16_t end;
		bool isRParenthesisDone = false;

		for (size_t i = s.length(); i != 0; i--)
		{
			char current = s[i - 1];
			if (current == ')')
				if (!isRParenthesisDone)
				{
					end = i - 1;
					isRParenthesisDone = true;
				}

			if (current == '(')
				start = i - 1;
		}

		return s.substr(start, end - start + 1);
	}

	inline std::string isolateOuter(std::string s)
	{
		uint16_t end;

		for (size_t i = s.length(); i != 0; i--)
		{
			char current = s[i - 1];

			if (current == '(')
				end = i - 1;
		}

		return s.substr(0, end + 1);
	}

	inline func_dd fromString(std::string input)
	{
		func_dd selected_function = functions::id;

		// provide function string as ax or f(x)
		if (input == "x")
		{
			return selected_function;
		}

		std::string buffer = "";
		double numBuffer = 0;
		bool inDecimals = false;
		uint decimalDepth = 1;

		for (size_t i = 0; i < input.length(); i++)
		{
			char c = input[i];
			if (c >= ZERO && c <= NINE)
			{
				if (inDecimals)
				{
					numBuffer += std::pow(0.1, decimalDepth) * (c - ZERO);
					decimalDepth++;
				}
				else
				{
					numBuffer = 10 * numBuffer + c - ZERO;
				}
			}

			if (c == FULL_STOP)
			{
				inDecimals = true;
			}

			if (c >= LETTER_a && c <= LETTER_z)
			{
				buffer.push_back(c);
			}

		}

		if (buffer == "x")
			selected_function = functions::id;


		if (buffer == "exp")
			selected_function = functions::exp;

		if (buffer == "log")
			selected_function = functions::log;


		if (buffer == "cos")
			selected_function = functions::cos;

		if (buffer == "sin")
			selected_function = functions::sin;

		if (buffer == "tan")
			selected_function = functions::tan;


		if (buffer == "cosh")
			selected_function = functions::cosh;

		if (buffer == "sinh")
			selected_function = functions::sinh;

		if (buffer == "tanh")
			selected_function = functions::tanh;

		if (numBuffer == 0 && buffer != "x")
		{
			numBuffer += 1;
		}

		return [numBuffer, selected_function](double x)
		{
			return numBuffer * selected_function(x);
		};
	}

	inline func_dd fromBuffer(std::vector<std::string> inputBuffer)
	{
		func_dd current_function = functions::id;
		for (size_t i = inputBuffer.size(); i > 0; i--)
		{
			current_function = compose2(fromString(inputBuffer[i - 1]), current_function);
		}
		return current_function;

	}

}
