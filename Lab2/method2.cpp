#include <cmath>
#include <iostream>

double fx(const double x) { return (x - 1) * exp(-pow(x, 2) / 2.0); }
double dfx(const double x) {
  return exp(-pow(x, 2) / 2.0) - x * (x - 1) * exp(-pow(x, 2) / 2.0);
}
double ddfx(const double x) { return (x * x - 3 * x + 1) * exp(-x * x / 2.0); }
void print(const double& xStar, const double& fStar, const double& k) {
  std::cout << "Root found at: " << xStar << " with function value: " << fStar
            << " after " << k << " iterations." << std::endl;
}
void solve(const double a0, const double b0, const double epsilon) {
  double xk = (a0 + b0) / 2;
  double xStar;
  double fStar;
  int k = 0;

  while (true) {
    double fPrimeXk = dfx(xk);
    double fDoublePrimeXk = ddfx(xk);

    if (std::abs(fPrimeXk) <= epsilon) {
      xStar = xk;
      fStar = fx(xk);
      break;
    } else if (std::abs(fDoublePrimeXk) > 0) {
      xk = xk - fPrimeXk / fDoublePrimeXk;
    } else {
      std::cerr << "Second derivative is nonpositive, method fails."
                << std::endl;
      return;
    }
    k++;
    if (k > 100) {
      std::cerr << "Too many iterations, method fails." << std::endl;
      return;
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