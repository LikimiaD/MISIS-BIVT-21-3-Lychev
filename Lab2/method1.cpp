#include <cmath>
#include <iostream>

double fx(const double x) { return (x - 1) * exp(-pow(x, 2) / 2.0); }
double dfx(const double x) {
  return exp(-pow(x, 2) / 2.0) - x * (x - 1) * exp(-pow(x, 2) / 2.0);
}
void print(const double& xStar, const double& fStar, const double& k) {
  std::cout << "Root found at: " << xStar << " with function value: " << fStar
            << " after " << k << " iterations." << std::endl;
}
void solve(double a0, double b0, const double epsilon) {
  double k = 0;
  double xStar = 0;
  double fStar = 0;

  while (true) {
    double xMiddle = (a0 + b0) / 2;
    double fPrimeX = dfx(xMiddle);

    if (std::abs(fPrimeX) <= epsilon) {
      xStar = xMiddle;
      fStar = fx(xStar);
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
  print(xStar, fStar, k);
}

int main() {
  double a0 = -2;
  double b0 = 0;
  double epsilon = 0.0005;

  solve(a0, b0, epsilon);

  return 0;
}
