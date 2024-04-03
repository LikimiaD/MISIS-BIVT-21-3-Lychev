#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

int func_calls = 0;
int iterations = 0;

double f(double x1, double x2) {
    func_calls++;
    return std::pow(x1, 3) + std::pow(x2, 2) - x1 * x2 - 2 * x1 + 3 * x2 - 4;
}

std::vector<double> grad(double x1, double x2) {
    func_calls += 2;
    return {3 * std::pow(x1, 2) - x2 - 2, 2 * x2 - x1 + 3};
}

std::vector<double> gradientDescent(double x1_init, double x2_init, double learning_rate, int max_iters, double tolerance) {
    std::vector<double> x = {x1_init, x2_init};
    std::vector<double> x_cord, y_cord, z_cord;
    
    while (iterations < max_iters) {
        auto g = grad(x[0], x[1]);
        if (std::sqrt(g[0]*g[0] + g[1]*g[1]) < tolerance) {
            break;
        }
        
        x[0] -= learning_rate * g[0];
        x[1] -= learning_rate * g[1];
        
        x_cord.push_back(x[0]);
        y_cord.push_back(x[1]);
        z_cord.push_back(f(x[0], x[1]));
        
        iterations++;
    }

    std::ofstream x_file("bin/x_vals_method2.txt"), y_file("bin/y_vals_method2.txt"), z_file("bin/z_vals_method2.txt");
    for (size_t i = 0; i < x_cord.size(); i++) {
        x_file << x_cord[i] << std::endl;
        y_file << y_cord[i] << std::endl;
        z_file << z_cord[i] << std::endl;
    }

    return x;
}

int main() {
    double x1_init = 0;
    double x2_init = 0;
    double learning_rate = 0.01;
    int max_iters = 10000;
    double tolerance = 1e-5;

    auto result = gradientDescent(x1_init, x2_init, learning_rate, max_iters, tolerance);

    std::cout << "Optimal solution: (" << result[0] << ", " << result[1] << ")" << std::endl;
    std::cout << "Optimal function value: " << f(result[0], result[1]) << std::endl;
    std::cout << "Function calls: " << func_calls << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;

    system("python3 method2.py");

    return 0;
}