#include <cmath>
#include <iostream>

double fx(const double& x) { return (x - 1) * exp(-pow(x, 2) / 2.0); }

double dfx(const double& x) {
  return exp(-pow(x, 2) / 2.0) - x * (x - 1) * exp(-pow(x, 2) / 2.0);
}

void solve(double a0, double b0, const double epsilon) {
  int k = 0;
  int fx_counter = 0;
  int dfx_counter = 0;
  double xStar = 0;
  double fStar = 0;

  while (true) {
    double xMiddle = (a0 + b0) / 2;
    double fPrimeX = dfx(xMiddle);
    dfx_counter++;

    if (std::abs(fPrimeX) <= epsilon) {
      xStar = xMiddle;
      fStar = fx(xStar);
      fx_counter++;
      break;
    } else {
      k++;
      if (fPrimeX > 0) {
        b0 = xMiddle;
      } else {
        a0 = xMiddle;
      }
    }
  }

  std::cout << "Root found at: " << xStar << " with function value: " << fStar
            << " after " << k << " iterations." << std::endl;
  std::cout << "Function was called " << fx_counter << " times." << std::endl;
  std::cout << "Derivative was called " << dfx_counter << " times."
            << std::endl;
}

int main() {
  double a0 = -2;
  double b0 = 0;
  double epsilon = 0.0005;

  solve(a0, b0, epsilon);

  return 0;
}