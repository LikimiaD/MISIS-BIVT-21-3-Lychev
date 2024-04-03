#include <cmath>
#include <iostream>
#include <vector>

double f(double x1, double x2) {
    return std::pow(x1 + x2, 2) + std::pow(std::sin(x1 + 2), 2) + std::pow(x2, 2);
}

double df_x1(double x1, double x2) {
    return 2 * (x1 + x2) + 2 * std::sin(x1 + 2) * std::cos(x1 + 2);
}

double df_x2(double x1, double x2) {
    return 2 * (x1 + x2) + 2 * x2;
}

std::vector<double> grad(double x1, double x2) {
    return {df_x1(x1, x2), df_x2(x1, x2)};
}

std::vector<std::vector<double>> hesse(double x1, double x2) {
    return {
        {2 + 2 * std::cos(x1 + 2) * std::cos(x1 + 2) - 2 * std::sin(x1 + 2) * std::sin(x1 + 2), 2},
        {2, 4}
    };
}

std::vector<double> newtonMethodWithStepAdjustment(double x1, double x2, double tolerance) {
    std::vector<double> x = {x1, x2};
    int maxIterations = 1000;
    int iteration = 0;
    
    while (iteration < maxIterations) {
        auto g = grad(x[0], x[1]);
        auto H = hesse(x[0], x[1]);
        double det = H[0][0] * H[1][1] - H[0][1] * H[1][0];
        
        if (std::fabs(det) < 1e-6) {
            std::cerr << "Determinant is too close to zero. The Hessian may be singular." << std::endl;
            break;
        }
        
        std::vector<double> H_inv_g = {
            (H[1][1] * g[0] - H[0][1] * g[1]) / det,
            (-H[1][0] * g[0] + H[0][0] * g[1]) / det
        };
        
        std::vector<double> x_new = {
            x[0] - H_inv_g[0],
            x[1] - H_inv_g[1]
        };
        
        double diff = std::sqrt(std::pow(x_new[0] - x[0], 2) + std::pow(x_new[1] - x[1], 2));
        
        if (diff < tolerance) {
            std::cout << "Converged in " << iteration << " iterations." << std::endl;
            return x_new;
        }
        
        x = x_new;
        iteration++;
    }
    
    std::cout << "Max iterations reached." << std::endl;
    return x;
}

int main() {
    double tolerance = 0.0001;
    
    auto result1 = newtonMethodWithStepAdjustment(2, -1, tolerance);
    std::cout << "Starting from (2, -1): (" << result1[0] << ", " << result1[1] << "), "
              << "f = " << f(result1[0], result1[1]) << std::endl;
    
    auto result2 = newtonMethodWithStepAdjustment(0, 0, tolerance);
    std::cout << "Starting from (0, 0): (" << result2[0] << ", " << result2[1] << "), "
              << "f = " << f(result2[0], result2[1]) << std::endl;
    
    return 0;
}
