#include <cmath>
#include <iostream>
#include <string>

void print(const std::string& ptr, const double& value) {
  std::cout << ptr << " value is: " << value << std::endl;
}

double fx(const double& x) { return -x * exp(-2 * x); }

void solve(const double& a, const double& b, const double& epsilon,
           const double& delta_x) {
  int iter = 0;

  double x_1 = (a + b) / 2;
  double x_2 = x_1 + delta_x;
  double x_3 = 0.0;
  double x_m = 0.0;

  double f_x1 = fx(x_1);
  double f_x2 = fx(x_2);
  double f_x3 = 0.0;
  double f_m = 0.0;

  if (f_x1 > f_x2) {
    x_3 = x_1 + 2 * delta_x;
  } else {
    x_3 = x_1 - delta_x;
  }

  f_x3 = fx(x_3);

  while (1) {
    double a_1 = (f_x2 - f_x1) / (x_2 - x_1);
    double a_2 = 1 / (x_3 - x_2) *
                 ((f_x3 - f_x1) / (x_3 - x_1) - (f_x2 - f_x1) / (x_2 - x_1));

    if (a_2 == 0.0) {
      break;
    }

    double x_new = (x_1 + x_2) / 2 - a_1 / (2 * a_2);
    double f_new = fx(x_new);

    if (!(a <= x_new && x_new <= b)) {
      x_new = x_new < a ? a : b;
    }

    f_m = std::min(std::min(f_x1, f_x2), std::min(f_x1, f_x3));
    x_m = f_m == f_x1 ? x_1 : f_m == f_x2 ? x_2 : x_3;

    if (std::abs(f_m - f_new) <= epsilon && std::abs(x_m - x_new) <= epsilon) {
      break;
    }

    if (x_new < x_m) {
      x_1 = x_new;
      x_2 = x_m;
      x_3 = (x_m + delta_x / 2);
    } else {
      x_1 = (x_m - delta_x / 2);
      x_2 = x_m;
      x_3 = x_new;
    }
    f_x1 = fx(x_1);
    f_x2 = fx(x_2);
    f_x3 = fx(x_3);
    iter++;
  }

  print("X*", x_m);
  print("F*", f_m);
  print("Iterations", iter);
}

int main() {
  double a = -2.0;
  double b = 6.0;
  double epsilon = 0.001;
  double delta_x = 0.001;
  solve(a, b, epsilon, delta_x);
  return 0;
}