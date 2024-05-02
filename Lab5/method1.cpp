#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <functional>

double f(const std::vector<double>& x) {
    return std::pow(x[0] + x[1], 2) + std::pow(sin(x[0] + 2), 2) + std::pow(x[1], 2);
}

std::vector<double> normalize(const std::vector<double>& v) {
    double norm = sqrt(v[0] * v[0] + v[1] * v[1]);
    return {v[0] / norm, v[1] / norm};
}

std::tuple<std::vector<double>, double, int, int> random_search(std::function<double(const std::vector<double>&)> func,
                                                                int iterations=1000, double gamma_initial=1.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1);

    std::vector<double> x_current = {d(gen), d(gen)};
    double f_current = func(x_current);
    int f_calls = 1;
    int unsuccessful_steps = 0;
    double gamma = gamma_initial;

    std::vector<double> h = normalize({d(gen), d(gen)});

    for (int i = 0; i < iterations; ++i) {
        if (unsuccessful_steps >= 7) {
            gamma /= 2;
            if (gamma < 0.001) {
                return {x_current, f_current, f_calls, i + 1};
            }
            unsuccessful_steps = 0;
        }

        std::vector<double> x_new = {x_current[0] - gamma * h[0], x_current[1] - gamma * h[1]};
        double f_new = func(x_new);
        f_calls++;

        if (f_new < f_current) {
            x_current = x_new;
            f_current = f_new;
        } else {
            unsuccessful_steps++;
            h = normalize({d(gen), d(gen)});
        }
    }

    return {x_current, f_current, f_calls, iterations};
}

int main() {
    auto result = random_search(f);
    std::vector<double> x = std::get<0>(result);
    double f_value = std::get<1>(result);
    int function_calls = std::get<2>(result);
    int iterations = std::get<3>(result);

    std::cout << "Final position: (" << x[0] << ", " << x[1] << ")" << std::endl;
    std::cout << "Function value: " << f_value << std::endl;
    std::cout << "Number of function calls: " << function_calls << std::endl;
    std::cout << "Number of iterations: " << iterations << std::endl;
    return 0;
}