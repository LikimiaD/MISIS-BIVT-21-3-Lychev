#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

double f(const std::vector<double>& x) {
    return std::pow(x[0] + x[1], 2) + std::pow(std::sin(x[0] + 2), 2) + std::pow(x[1], 2);
}

std::vector<double> simplex_method(double tol, int max_iter) {
    std::vector<std::vector<double>> simplex = {
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
    };
    int iterations = 0;
    int function_calls = 0;
    const double alpha = 1.0;
    const double gamma = 2.0;
    const double rho = 0.5;
    const double sigma = 0.5;

    while (iterations < max_iter) {
        std::sort(simplex.begin(), simplex.end(), [&](const std::vector<double>& a, const std::vector<double>& b) {
            return f(a) < f(b);
        });
        function_calls += 3;

        std::vector<double> centroid = {0.0, 0.0};
        for (int i = 0; i < simplex.size() - 1; ++i) {
            centroid[0] += simplex[i][0];
            centroid[1] += simplex[i][1];
        }
        centroid[0] /= (simplex.size() - 1);
        centroid[1] /= (simplex.size() - 1);

        std::vector<double> xr = {centroid[0] + alpha * (centroid[0] - simplex.back()[0]),
                                  centroid[1] + alpha * (centroid[1] - simplex.back()[1])};
        function_calls++;

        if (f(xr) < f(simplex[0])) {
            std::vector<double> xe = {centroid[0] + gamma * (xr[0] - centroid[0]),
                                      centroid[1] + gamma * (xr[1] - centroid[1])};
            function_calls++;
            if (f(xe) < f(xr)) {
                simplex.back() = xe;
            } else {
                simplex.back() = xr;
            }
        } else if (f(xr) < f(simplex[simplex.size() - 2])) {
            simplex.back() = xr;
        } else {
            std::vector<double> xc = {centroid[0] + rho * (simplex.back()[0] - centroid[0]),
                                      centroid[1] + rho * (simplex.back()[1] - centroid[1])};
            function_calls++;
            if (f(xc) < f(simplex.back())) {
                simplex.back() = xc;
            } else {
                for (int i = 1; i < simplex.size(); ++i) {
                    simplex[i] = {simplex[0][0] + sigma * (simplex[i][0] - simplex[0][0]),
                                  simplex[0][1] + sigma * (simplex[i][1] - simplex[0][1])};
                }
                function_calls += simplex.size() - 1;
            }
        }

        double range = f(simplex.front()) - f(simplex.back());
        if (std::abs(range) < tol) {
            break;
        }
        iterations++;
    }

    std::cout << "Final position: (" << simplex[0][0] << ", " << simplex[0][1] << ")" << std::endl;
    std::cout << "Function value: " << f(simplex[0]) << std::endl;
    std::cout << "Number of function calls: " << function_calls << std::endl;
    std::cout << "Number of iterations: " << iterations << std::endl;

    return simplex[0];
}

int main() {
    double tolerance = 1e-6;
    int max_iterations = 200;
    simplex_method(tolerance, max_iterations);
    return 0;
}
