#include <iostream>
#include <cmath>
#include <vector>
double func_sin(double x) {
    return sin(x);
}

double func_poly(double x) {
    return x * x + 2 * x + 5;
}

double func_exp(double x) {
    return exp(x);
}

double rectangle_method(double (*f)(double), double a, double b, int n)
{
    double s = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double xi = a + i * s;
        sum += f(xi + s * 0.5) * s;
    }

    return sum;
}

double trapezoid_method(double (*f)(double), double a, double b, int n) {
    double s = (b - a) / n;

    double result = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++)
    {
        double x = a + i * s;
        result += f(x);
    }
    ;
    return result * s;
}
/*
double simpson_method(double (*func)(double), double a, double b, int n) {
    double SUM = 0.;
    SUM = ((b -a) / 6) * (func(a) +  4* func((a+b)/2) + func(b));
    return SUM;
}
*/
double simpson_method(double (*func)(double), double a, double b, int n)
{
    double h = (b - a) / n;                    
    double wynik = 0.0;
    for (int i = 0; i < n; i++)
    {
        double xi = a + i * h;
        wynik += (func(xi) + 4 * func(xi + h / 2) + func(xi + h));
    }
    return (h / 6) * wynik;
}

double gaussian_quadrature(double (*f)(double), double a, double b, int size, std::vector<double> nodes, std::vector<double> weights)
{
    double result = 0;
    for (int i = 0; i < size; i++)
    {
        double t = (a + b) / 2 + ((b - a) / 2) * nodes[i];
        result += weights[i] * f(t);
    }

    return (b - a) / 2 * result;
}

int main() {
    double a = 0.5;
    double b = 5;
    int n = 4;

    std::cout << "Func: sin(x)\n";
    std::cout << "Area: <" << a << ", " << b << ">\n";
    std::cout << "Num of figures: " << n << "\n";
    std::cout << "Rectangle Method: " << rectangle_method(func_sin, a, b, n) << "\n";
    std::cout << "Trapezoid Method: " << trapezoid_method(func_sin, a, b, n) << "\n";
    std::cout << "Simpson method: " << simpson_method(func_sin, a, b, n) << "\n";
    

    std::cout << "Func: x^2 + 2x + 5\n";
    std::cout << "Area: <" << a << ", " << b << ">\n";
    std::cout << "Num of figures: " << n << "\n";
    std::cout << "Rectangle Method: " << rectangle_method(func_poly, a, b, n) << "\n";
    std::cout << "Trapezoid Method: " << trapezoid_method(func_poly, a, b, n) << "\n";
    std::cout << "Simpson method: " << simpson_method(func_poly, a, b, n) << "\n";

    std::cout << "Func: exp(x)\n";
    std::cout << "Area: <" << a << ", " << b << ">\n";
    std::cout << "Num of figures: " << n << "\n";
    std::cout << "Rectangle Method: " << rectangle_method(func_exp, a, b, n) << "\n";
    std::cout << "Trapezoid Method: " << trapezoid_method(func_exp, a, b, n) << "\n";
    std::cout << "Simpson method: " << simpson_method(func_exp, a, b, n) << "\n";


    
    std::vector<double> nodes1(2,0);
    nodes1[0] = -sqrt(3.0)/3;
    nodes1[1] = sqrt(3.0)/3;

    std::vector<double> weights1(2,0);
    weights1[0] = 1;
    weights1[1] = 1;

    std::vector<double> nodes2(3, 0);
    nodes2[0] = -0.774596;
    nodes2[1] = 0;
    nodes2[2] = 0.774596;

    std::vector<double> weights2(3, 0);
    weights2[0] = 5.0 / 9.0;
    weights2[1] = 8.0 / 9.0;
    weights2[2] = 5.0 / 9.0;

    std::vector<double> nodes3(4, 0);
    nodes3[0] = -1.0 / 35.0 * sqrt(525.0 + 70 * sqrt(30.0));
    nodes3[1] = -1.0 / 35.0 * sqrt(525.0 - 70 * sqrt(30.0));
    nodes3[2] = 1.0 / 35.0 * sqrt(525.0 - 70 * sqrt(30.0));
    nodes3[3] = 1.0 / 35.0 * sqrt(525.0 + 70 * sqrt(30.0));

    std::vector<double> weights3(4, 0);
    weights3[0] = 1 / 36.0 *(18 - sqrt(30.0));
    weights3[1] = 1 / 36.0 * (18 + sqrt(30.0));
    weights3[2] = 1 / 36.0 * (18 + sqrt(30.0));
    weights3[3] = 1 / 36.0 * (18 - sqrt(30.0));


    std::cout << "Func: sin(x)\n";
    std::cout << "Area: <" << 0.5 << ", " << 2.5 << ">\n";
    std::cout << "2 nodes: " << gaussian_quadrature(func_sin, 0.5, 2.5, 2, nodes1,weights1) << "\n";
    std::cout << "3 nodes: " << gaussian_quadrature(func_sin, 0.5, 2.5, 3, nodes2, weights2) << "\n";
    std::cout << "4 nodes: " << gaussian_quadrature(func_sin, 0.5, 2.5, 4, nodes3, weights3) << "\n";

    std::cout << "Func: x^2 + 2x + 5\n";
    std::cout << "Area: <" << 0 << ", " << 5 << ">\n";
    std::cout << "2 nodes: " << gaussian_quadrature(func_poly, 0.5, 5, 2, nodes1, weights1) << "\n";
    std::cout << "3 nodes: " << gaussian_quadrature(func_poly, 0.5, 5, 3, nodes2, weights2) << "\n";
    std::cout << "4 nodes: " << gaussian_quadrature(func_poly, 0.5, 5, 4, nodes3, weights3) << "\n";

    std::cout << "Func: exp(x)\n";
    std::cout << "Area: <" << 0 << ", " << 5 << ">\n";
    std::cout << "2 nodes: " << gaussian_quadrature(func_exp, 0.5, 5, 2, nodes1, weights1) << "\n";
    std::cout << "3 nodes: " << gaussian_quadrature(func_exp, 0.5, 5, 3, nodes2, weights2) << "\n";
    std::cout << "4 nodes: " << gaussian_quadrature(func_exp, 0.5, 5, 4, nodes3, weights3) << "\n";


    return 0;
}