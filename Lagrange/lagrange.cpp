#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

double interpolation(double x);

int main() {
    double x = 0.0;
    std::cout << "Enter the number: ";
    std::cin >> x;
    std::cout << "D)Result [W(" << x << ")] = " << interpolation(x) << "\n";
    return 0;
}

double interpolation(double x) {
    
    std::fstream read;
    read.open("MN-1.txt");

    if (!read.is_open()) {
        std::cerr << "Error";
        exit(EXIT_FAILURE);
    }

    int size;
    read >> size;
    std::cout << "A) Number of nodes: " << size << "\n";
    
    std::vector<double> node(size, 0);
    std::vector<double> value(size, 0);
    std::vector<double> L(size, 0);
    
    std::cout << "B)\n";
    
    for (int i = 0; i < size; i++) {
        read >> node[i];
        read >> value[i];
        std::cout << "W(" << node[i] << ") = " << value[i] << "\n";
    }
    
    for (int i = 0; i < size; i++) {
        L[i] = 1.0;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                if (node[i] == node[j]) {
                    std::cerr << "Division by 0";
                    exit(EXIT_FAILURE);
                }
                L[i] *= (x - node[j]) / (node[i] - node[j]);
            }
        }
    }

    double val = 0.0;

    for (int i = 0; i < size; i++) {
        val += value[i] * L[i];
    }

    std::cout << "C)Point of interpolation: " << x << "\n";
    
    read.close();
    
    return val;
}