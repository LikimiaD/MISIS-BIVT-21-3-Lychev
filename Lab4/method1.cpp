#include <cmath>
#include <iostream>

double f(double x1, double x2, int& functionCalls) {
  functionCalls++;
  return std::pow(x1 + x2, 2) + std::pow(std::sin(x1 + 2), 2) + std::pow(x2, 2);
}

void gradient(double x1, double x2, double& grad_x1, double& grad_x2,
              int& functionCalls) {
  functionCalls++;
  grad_x1 = 2 * (x1 + x2) + 2 * (std::sin(x1 + 2) * std::cos(x1 + 2));
  grad_x2 = 2 * (x1 + x2) + 2 * x2;
}

void heavy_ball_method(double alpha, double beta, double x1, double x2,
                       double tolerance) {
  double prev_x1 = x1, prev_x2 = x2;
  double grad_x1, grad_x2;
  double velocity_x1 = 0, velocity_x2 = 0;
  int functionCalls = 0, iterations = 0;

  do {
    gradient(x1, x2, grad_x1, grad_x2, functionCalls);

    velocity_x1 = beta * velocity_x1 - alpha * grad_x1;
    velocity_x2 = beta * velocity_x2 - alpha * grad_x2;

    prev_x1 = x1;
    prev_x2 = x2;
    x1 += velocity_x1;
    x2 += velocity_x2;

    std::cout << "Iteration " << iterations + 1 << ": x1 = " << x1
              << ", x2 = " << x2 << ", f(x1, x2) = " << f(x1, x2, functionCalls)
              << std::endl;

    iterations++;

  } while (std::sqrt(std::pow(prev_x1 - x1, 2) + std::pow(prev_x2 - x2, 2)) >
           tolerance);

  std::cout << "Minimum at x1: " << x1 << ", x2: " << x2
            << ", f(x1, x2): " << f(x1, x2, functionCalls) << std::endl;
  std::cout << "Total function calls: " << functionCalls
            << ", Total iterations: " << iterations << std::endl;
}

int main() {
  double alpha = 0.01;
  double beta = 0.9;
  double tolerance = 1e-5;

  double x1 = -1.5;
  double x2 = 2.5;

  heavy_ball_method(alpha, beta, x1, x2, tolerance);

  return 0;
}
