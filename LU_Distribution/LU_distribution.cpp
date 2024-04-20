#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

std::vector<std::vector<double>> readData(std::string filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int n;
    fileStream >> n;
    std::vector<std::vector<double>> grid(n, std::vector<double>(n + 1, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + 1; j++)
            fileStream >> grid[i][j];

    fileStream.close();
    return grid;
}

std::vector<double> calculateY(std::vector<std::vector<double>> L, std::vector<double> B, int n) {
    std::vector<double> Y(n, 0); 
    for (int i = 0; i < n; i++) {
        double sum = 0; 
        for (int j = 0; j < i; j++) {  
            sum += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - sum) / L[i][i];  
    }
    return Y;
}

void RozkladDoolittle(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& upper, std::vector<std::vector<double>>& lower, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double sum = 0; 
            for (int k = 0; k < i; k++) {
                sum += (lower[i][k] * upper[k][j]);
            }
            upper[i][j] = A[i][j] - sum;
        }
        for (int k = i; k < n; k++) {
            if (i == k) {
                lower[i][i] = 1;
            }
            else {
                double sum = 0;  
                for (int j = 0; j < i; j++) {
                    sum += (lower[k][j] * upper[j][i]);
                }
                lower[k][i] = (A[k][i] - sum) / upper[i][i];
            }
        }
    }
}

void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << std::fixed << std::setprecision(2) << val << "\t";
        }
        std::cout << std::endl;
    }
}


std::vector<double> solveLU(std::vector<std::vector<double>> U,std::vector<double> Y, int n) {
    std::vector<double> X(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        X[i] = Y[i];
        for (int j = i + 1; j < n; j++) {
            X[i] -= U[i][j] * X[j];
        }
        X[i] /= U[i][i];
    }
    return X;
}



int main() {
    std::vector<std::vector<double>> A = readData("RURL_dane2.txt");
    int n = A.size();
    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0));
    std::vector<std::vector<double>> U(n, std::vector<double>(n, 0));
    RozkladDoolittle(A, U, L, n);

    std::cout << "Matrix A\n";
    printMatrix(A);
    std::cout << "Matrix L:\n";
    printMatrix(L);

    std::cout << "\nMatrix U:\n";
    printMatrix(U);


    std::vector<double> B(n);
    for (int i = 0; i < n; i++) {
        B[i] = A[i][n];
    }

    std::vector<double>Y = calculateY(L, B, n);

    std::cout << "Wektor Y:\n";
    for (double val : Y) {
        std::cout << std::fixed << std::setprecision(2) << val << "\n";
    }
    std::cout << std::endl << std::endl;
 

    std::vector<double> X = solveLU(U, Y, n);

    std::cout << "Solution (x0 - xn) : \n";
   
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i << "=" << std::fixed << std::setprecision(2) << X[i] << "\n";
    }
    
    std::cout << "\n";


    return 0;
}