#include <cmath>
#include <iostream>
#include <string>

void print(const std::string& ptr, const double& value) {
  std::cout << ptr << " value is: " << value << std::endl;
}

double fx(const double& x) { return -x * exp(-2 * x); }

void solve(double& a, double& b, const double& epsilon) {
  int iter = 0;
  double delta = epsilon / 2;

  while ((b - a) / 2 >= epsilon) {
    double x_1 = (a + b) / 2 - delta;
    double x_2 = (a + b) / 2 + delta;

    double f_x1 = fx(x_1);
    double f_x2 = fx(x_2);

    if (f_x1 < f_x2) {
      b = x_2;
    } else {
      a = x_1;
    }
    iter++;
  }
  double x_star = (a + b) / 2;
  double f_star = fx(x_star);

  print("X*", x_star);
  print("F*", f_star);
  print("Iterations", iter);
}

int main() {
  double a = -2.0;
  double b = 6.0;
  double epsilon = 0.001;
  solve(a, b, epsilon);
  return 0;
}