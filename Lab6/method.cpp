#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double f(const vector<double>& x) {
    return x[0] - 2 * x[1] * x[1] + 4 * x[1];
}

vector<double> grad_f(const vector<double>& x) {
    return {1, -4 * x[1] + 4};
}

vector<double> projection(const vector<double>& x) {
    double lambda = (-3 * x[0] - 2 * x[1] - 6) / (9 + 4);
    return {x[0] + 3 * lambda, x[1] + 2 * lambda};
}

int main() {
    vector<double> x = {0, 0};
    double alpha = 0.1;
    int max_iter = 1000;
    double tol = 1e-6;
    int iter = 0;
    int func_calls = 0;
    
    for (int i = 0; i < max_iter; ++i) {
        vector<double> grad = grad_f(x);
        func_calls++;
        
        vector<double> x_new = {x[0] + alpha * grad[0], x[1] + alpha * grad[1]};
        x_new = projection(x_new);
        
        double diff = sqrt(pow(x_new[0] - x[0], 2) + pow(x_new[1] - x[1], 2));
        
        x = x_new;
        iter++;
        
        if (diff < tol) {
            break;
        }
    }
    
    cout << "Optimal point: (" << x[0] << ", " << x[1] << ")\n";
    cout << "Iterations: " << iter << "\n";
    cout << "Function calls: " << func_calls << "\n";
    
    return 0;
}