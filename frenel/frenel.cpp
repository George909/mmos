// frenel.cpp: определяет точку входа для приложения.
//

#define _USE_MATH_DEFINES // for C++
#include <cmath>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <complex>
#include <vector>
#include <tuple>

#include <string>
#include <string_view>

struct params {
	double lambda;
	double d;
	size_t nx1, ny1;
	size_t nx2, ny2;
	double size_x1, size_y1;
	double size_x2, size_y2;

	double a, b;
	std::string filename;
};

template<typename functor>
void frenel(std::vector<std::complex<double>>& input, params& prms, std::vector<std::complex<double>>& output, functor func);

std::tuple<size_t, size_t> index_to_xy(size_t index, size_t w) {
	return { index % w + 1, index / w + 1 };
}

//params read_params(int argc, char** argv);
//void save_image(std::vector<std::complex<double>>& field);
//void save_params(params& prms);

int main() {
	std::vector<std::complex<double>> input;
	params prms;

	return 0;
}

template<typename functor> 
void frenel(std::vector<std::complex<double>>& input, params& prms, std::vector<std::complex<double>>& output, functor func) {
	using namespace std::complex_literals;

	auto coef = 1i * M_PI / prms.d / prms.lambda;
	auto c([=](double x, double y) -> std::complex<double> {
		return std::exp(2i * M_PI * prms.d / prms.lambda) * std::exp(coef * (x*x + y*y));
	});

	auto term([=](size_t output_index) {
		auto [x2, y2] = index_to_xy(output_index, w);
		return [=](size_t input_index) {
			auto [x1, y1] = index_to_xy(input_index, w);
			return func(x1, y1) * std::exp(coef * (x1 * x1 + y1 * y1)) * std::exp(-2. * coef * (x1 * x2 + y1 * y2));
		}
	});

	auto sum([=](size_t output_index) {
		//return std::transform_reduce()
	})
}

