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

void swapColumns(std::vector<std::vector<double>>& matrix, int col1, int col2) {
    for (int i = 0; i < matrix.size(); i++) {
        std::swap(matrix[i][col1], matrix[i][col2]);
    }
}

std::vector<int> gaussCrout(std::vector<std::vector<double>>& matrix) {

    int n = matrix.size();
    std::vector<int> swappedColumns(matrix.size(), 0);
    for (int i = 0; i < n; i++) {
        int maxIndex = i;
        double maxVal = std::abs(matrix[i][i]);
        for (int k = i + 1; k < n; k++) {
            if (std::abs(matrix[k][i]) > maxVal) {
                maxVal = std::abs(matrix[k][i]);
                maxIndex = k;
            }
        }

        if (maxIndex != i) {
            swapColumns(matrix, i, maxIndex);

        }

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {
                double m = matrix[j][i] / matrix[i][i];
                for (int k = i; k <= n; k++) {
                    matrix[j][k] -= m * matrix[i][k];
                }
            }
        }
    }
    return swappedColumns;
}

void resultCrout(std::vector<std::vector<double>>& matrix, const std::vector<int>& swappedColumns) {

    int n = matrix.size();
    std::vector<double> res(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        res[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            res[i] -= matrix[i][j] * res[j];
        }
        res[i] /= matrix[i][i];
    }

    int g = swappedColumns.size();

    std::cout << "Result (x0 - xn):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << swappedColumns[i] << " = " << res[i] << "\n";
    }

}


void Gauss(std::vector<std::vector<double>>& grid) {
    int n = grid.size();
    for (int k = 0; k < n - 1; k++) {
        int maxRow = k;
        double maxVal = abs(grid[k][k]);

        for (int i = k + 1; i < n; i++) {
            if (abs(grid[i][k]) > maxVal) {
                maxVal = abs(grid[i][k]);
                maxRow = i;
            }
        }

        if (maxRow != k) {
            for (int j = k; j <= n; j++) {
                std::swap(grid[k][j], grid[maxRow][j]);
            }
        }
        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {
                double m = grid[j][i] / grid[i][i];
                for (int k = i; k <= n; k++) {
                    grid[j][k] -= m * grid[i][k];
                }
            }
        }
    }

}

void result(std::vector<std::vector<double>>& grid) {
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
    for (int i = 0; i < n; i++) {
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


    std::cout << "\nFile3\n";
    std::vector<std::vector<double>> Ex3 = readData("RURL_dane3.txt");
    std::cout << "BEFORE\n";
    dispalyMatrix(Ex2);
    Gauss(Ex2);
    std::cout << "AFTER\n";
    dispalyMatrix(Ex2);
    result(Ex2);
    std::cout << "\nFile2\n";
    std::vector<std::vector<double>> Ex4 = readData("RURL_dane2.txt");
    std::cout << "BEFORE\n";
    dispalyMatrix(Ex4);
    std::cout << "AFTER\n";
    std::vector<int> swappedColumns = gaussCrout(Ex4);
    dispalyMatrix(Ex4);
    result(Ex4);
    resultCrout(Ex4, swappedColumns);
    return 0;
}