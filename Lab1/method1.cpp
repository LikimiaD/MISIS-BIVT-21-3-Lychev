#include <cmath>
#include <iostream>
#include <string>

void print(const std::string& ptr, const double& value) {
  std::cout << ptr << " value is: " << value << std::endl;
}

double fx(const double& x) { return -x * exp(-2 * x); }

void solve(const double& a, const double& b, const double& epsilon) {
  int iter = 0;

  double h = (b - a) / 4;
  double x_0 = a;
  double f_x_0 = fx(x_0);

  while (1) {
    double x_1 = x_0 + h;
    double f_x_1 = fx(x_1);

    if (f_x_0 > f_x_1) {
      x_0 = x_1;
      f_x_0 = f_x_1;
      if (!(a < x_0 < b)) {
        break;
      }
    } else {
      h = -h / 4;
      if (std::abs(h) <= epsilon) {
        break;
      }
    }
    iter++;
  }
  print("X*", x_0);
  print("F*", f_x_0);
  print("Iterations", iter);
}

int main() {
  double a = -2.0;
  double b = 6.0;
  double epsilon = 0.001;
  solve(a, b, epsilon);
  return 0;
}