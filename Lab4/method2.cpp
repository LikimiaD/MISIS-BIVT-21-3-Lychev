#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

double function(const std::vector<double>& x) {
  double x1 = x[0], x2 = x[1];
  return (x1 + x2) * (x1 + x2) + sin(x1 + 2) * sin(x1 + 2) + x2 * x2;
}

std::vector<double> gradient(const std::vector<double>& x) {
  double x1 = x[0], x2 = x[1];
  return {2 * (x1 + x2) + 2 * sin(x1 + 2) * cos(x1 + 2),
          2 * (x1 + x2) + 2 * x2};
}

std::vector<std::vector<double>> outer(const std::vector<double>& a,
                                       const std::vector<double>& b) {
  std::vector<std::vector<double>> result(a.size(),
                                          std::vector<double>(b.size()));
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b.size(); ++j) {
      result[i][j] = a[i] * b[j];
    }
  }
  return result;
}

std::vector<double> operator+(const std::vector<double>& a,
                              const std::vector<double>& b) {
  std::vector<double> result(a.size());
  for (size_t i = 0; i < a.size(); ++i) {
    result[i] = a[i] + b[i];
  }
  return result;
}

std::vector<double> operator-(const std::vector<double>& a,
                              const std::vector<double>& b) {
  std::vector<double> result(a.size());
  for (size_t i = 0; i < a.size(); ++i) {
    result[i] = a[i] - b[i];
  }
  return result;
}

std::vector<double> operator*(double scalar, const std::vector<double>& v) {
  std::vector<double> result(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    result[i] = scalar * v[i];
  }
  return result;
}

double dot(const std::vector<double>& a, const std::vector<double>& b) {
  double result = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    result += a[i] * b[i];
  }
  return result;
}

std::vector<double> mat_vec_mult(const std::vector<std::vector<double>>& mat,
                                 const std::vector<double>& vec) {
  std::vector<double> result(vec.size(), 0);
  for (size_t i = 0; i < mat.size(); ++i) {
    for (size_t j = 0; j < vec.size(); ++j) {
      result[i] += mat[i][j] * vec[j];
    }
  }
  return result;
}

// Алгоритм BFGS
std::vector<double> BFGS(std::vector<double> x, double tolerance,
                         int& iterations, int& functionCalls) {
  int n = x.size();
  std::vector<std::vector<double>> H(n, std::vector<double>(n, 0));
  for (int i = 0; i < n; i++) H[i][i] = 1;

  std::vector<double> grad_x = gradient(x);
  functionCalls = 1;
  iterations = 0;

  while (std::sqrt(dot(grad_x, grad_x)) > tolerance && iterations < 1000) {
    std::vector<double> p = mat_vec_mult(H, grad_x);
    for (double& pi : p) pi = -pi;

    double alpha = 0.01;

    std::vector<double> x_new = x + alpha * p;
    std::vector<double> grad_x_new = gradient(x_new);
    std::vector<double> s = x_new - x;
    std::vector<double> y = grad_x_new - grad_x;
    double ys = dot(y, s);
    double yy = dot(y, y);

    if (ys > std::numeric_limits<double>::epsilon()) {
      double rho = 1 / ys;
      std::vector<std::vector<double>> term1 = outer(s, s);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          H[i][j] += (rho * rho * yy * s[i] * s[j]) -
                     rho * (term1[i][j] + term1[j][i]);
        }
      }
    }

    x = x_new;
    grad_x = grad_x_new;
    iterations++;
    functionCalls += 2;
  }

  return x;
}

int main() {
  std::vector<double> x0 = {-1.5, 3};
  double tolerance = 1e-6;
  int iterations = 0;
  int functionCalls = 0;
  std::vector<double> min_point =
      BFGS(x0, tolerance, iterations, functionCalls);
  double min_value = function(min_point);

  std::cout << "Минимум найден в точке (" << min_point[0] << ", "
            << min_point[1] << ")\n";
  std::cout << "Значение функции в минимуме: " << min_value << std::endl;
  std::cout << "Количество вызовов функции: " << functionCalls << std::endl;
  std::cout << "Количество итераций: " << iterations << std::endl;

  return 0;
}
