#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

double f(double x1, double x2) {
    return pow(x1, 3) + pow(x2, 2) - x1 * x2 - 2 * x1 + 3 * x2 - 4;
}

std::vector<double> gradient(double x1, double x2) {
    double dfdx1 = 3 * pow(x1, 2) - x2 - 2;
    double dfdx2 = 2 * x2 - x1 + 3;
    return {dfdx1, dfdx2};
}

std::vector<double> gradient_descent(double x1, double x2, double gamma, double epsilon, int max_iters, int &func_evals, int &iterations, double &error) {
    std::vector<double> x = {x1, x2};
    std::vector<double> grad;
    func_evals = 0;

    std::ofstream x_file("bin/x_vals_method1.txt");
    std::ofstream y_file("bin/y_vals_method1.txt");

    for (iterations = 0; iterations < max_iters; ++iterations) {
        grad = gradient(x[0], x[1]);
        func_evals += 2;
        double grad_magnitude = sqrt(pow(grad[0], 2) + pow(grad[1], 2));
        error = grad_magnitude;

        if (grad_magnitude < epsilon) {
            break;
        }

        x_file << x[0] << std::endl;
        y_file << x[1] << std::endl;

        x[0] = x[0] - gamma * grad[0];
        x[1] = x[1] - gamma * grad[1];
        func_evals++;
    }

    x_file.close();
    y_file.close();

    return x;
}

int main() {
    double initial_x1 = 0;
    double initial_x2 = 0;
    double step_size = 0.01;
    double tolerance = pow(10, -2);
    int max_iterations = 1000;
    int function_evaluations, iterations;
    double error;

    std::vector<double> minimum = gradient_descent(initial_x1, initial_x2, step_size, tolerance, max_iterations, function_evaluations, iterations, error);
    std::cout << "Оптимальное решение: (" << minimum[0] << ", " << minimum[1] << ")" << std::endl;
    std::cout << "Оптимальное значение функции: " << f(minimum[0], minimum[1]) << std::endl;
    std::cout << "Количество вычислений функции: " << function_evaluations << std::endl;
    std::cout << "Число итераций: " << iterations << std::endl;
    std::cout << "Погрешность: " << error << std::endl;

    system("python3 method1.py");

    return 0;
}
