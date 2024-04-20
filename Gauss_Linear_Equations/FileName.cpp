#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

std::vector<std::vector<double>> readData(std::string filename) {
    std::fstream read;
    read.open(filename);
    int n;
    read >> n;
    std::vector<std::vector<double>> grid(n, std::vector<double>(n + 1, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            read >> grid[i][j];
   
    read.close();
    return grid;
}

void dispalyMatrix(std::vector<std::vector<double>>& grid) {
    int n = grid.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            std::cout << std::fixed << std::setprecision(2) << grid[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void Gauss(std::vector<std::vector<double>>& grid) {
    int n = grid.size();
    for (int i = 0; i < n; ++i) {
        if (grid[i][i] == 0) {
            std::cerr << "Error: 0\n";
        }
        for (int j = i + 1; j < n; j++) {
            double m = grid[j][i] / grid[i][i];
            for (int k = i; k <= n; k++) {
                grid[j][k] -= m * grid[i][k];
            }
        }
    }
}

void result(std::vector<std::vector<double>>& grid){
    int n = grid.size();
    std::vector<double> res(n, 0);
    for (int i = n - 1; i >= 0; i--) {
    res[i] = grid[i][n];
    for (int j = i + 1; j < n; j++) {
        res[i] -= grid[i][j] * res[j];
    }
        res[i] /= grid[i][i];
    }

    std::cout << "Result (x0 - xn):\n";
    for (int i = 0; i < n; ++i) {
    std::cout << "x" << i << " = " << res[i] << "\n";
}
}


int main() {
    
    std::cout << "File1\n";
    std::vector<std::vector<double>> Ex1 = readData("RURL_dane1.txt");
    std::cout << "BEFORE\n";
    dispalyMatrix(Ex1);
    Gauss(Ex1);
    std::cout << "AFTER\n";
    dispalyMatrix(Ex1);
    result(Ex1);

    std::cout << "\nFile2\n";
    std::vector<std::vector<double>> Ex2 = readData("RURL_dane2.txt");
    std::cout << "BEFORE\n";
    dispalyMatrix(Ex2);
    Gauss(Ex2);
    std::cout << "AFTER\n";
    dispalyMatrix(Ex2);
    result(Ex2);
    return 0;
}