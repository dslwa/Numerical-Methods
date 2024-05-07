#include <iostream>
#include <vector>
#include <cmath>  

long long factorial(int n) {
    if (n == 0) return 1;
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double binomialCoefficient(int n, int k) {
    long long num = factorial(n);
    long long denom = factorial(k) * factorial(n - k);
    return static_cast<double>(num) / denom; 
}


double factorialPolynomial(double x, int n) {
    if (n == 0) return 1;
    double result = 1;
    for (int j = 0; j < n; ++j) {
        result *= (x - j);
    }
    return result;
}

double gramPolynomial(int k, int n, double q) {
    double sum = 0.0;
    for (int s = 0; s <= k; ++s) {
        double term = pow(-1, s) * binomialCoefficient(k, s) * binomialCoefficient(k + s, s)
            * factorialPolynomial(q, s) / factorialPolynomial(n, s);
        sum += term;
    }
    return sum;
}


double computeCk(int k, int n, const std::vector<double>& Y) {
    double sum = 0.0;
    for (int i = 0; i <= n; ++i) {
        sum += Y[i] * gramPolynomial(k, n, i);
    }
    std::cout << "c_" << k << " = " << sum << "\n";
    return sum;
}


double computeSk(int k, int n) {
    double sum = 0.0;
    for (int i = 0; i <= n; ++i) {
        double val = gramPolynomial(k, n, i);
        sum += val * val;

    }
    std::cout << "s_" << k << " = " << sum << "\n";
    return sum;
}


double gramApproximation(const std::vector<double>& X, const std::vector<double>& Y, int degree, double x) {
    int n = X.size() - 1;
    double h = X[1] - X[0];  
    double q = (x - X[0]) / h;
    double result = 0.0;

    for (int k = 0; k <= degree; ++k) {
        double ck = computeCk(k, n, Y);
        double sk = computeSk(k, n);
        result += ck / sk * gramPolynomial(k, n, q);
    }
    return result;
}

int main() {
    std::vector<double> x_coordinates = { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<double> y_coordinates = { 2, 4, 3, 5, 6, 9, 11, 11 };

    std::cout << "Approximation at x = 2.5: " << gramApproximation(x_coordinates, y_coordinates, 1, 2.5) << "\n";
    std::cout << "Approximation at x = 6.5: " << gramApproximation(x_coordinates, y_coordinates, 1, 6.5) << "\n";

    return 0;
}