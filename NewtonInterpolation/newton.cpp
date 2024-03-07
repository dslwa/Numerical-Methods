#include <iostream>
#include <vector>
#include <fstream>

double newtonIntrpolation(double x, const std::string& filename) {

    int size;

    std::fstream read;
    read.open(filename);

    read >> size;

    std::vector<double> nodes(size, 0);
    std::vector<double> values(size, 0);

    for (int i = 0; i < size; i++) {
        read >> nodes[i];
        read >> values[i];
    }

    std::vector<std::vector<double>> grid(size, std::vector<double>(size, 0));

    for (int i = 0; i < size; i++) {
        grid[i][0] = values[i];
    }

    for (int j = 1; j < size; j++) {
        for (int i = 0; i < size - j; i++) {
            grid[i][j] = (grid[i + 1][j - 1] - grid[i][j - 1]) / (nodes[i + j] - nodes[i]);
        }
    }


    std::cout << "Number of Nodes: " << size << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << "W(" << nodes[i] << ")= " << values[i] << "\n";
    }

    std::cout << "Point of interpolation: " << x << "\n";
    
    double factor = 1.0;
    double res = 0.0;
    for (int i = 0; i < nodes.size(); i++) {
        res += factor * grid[0][i];
        factor *= (x - nodes[i]);
    }

    for (int i = 0; i < size; i++)
        std::cout << "B(" << i << ") = " << grid[0][i] << "\n";
    
    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            std::cout << grid[i][j] << "\t";
        }
        std::cout << "\n";
    }*/

    read.close();

    return res;
 }


int main() {
    std::cout << "RESULT W(2.5)= " << newtonIntrpolation(2.5, "MN-2-p1.txt") << "\n";
    std::cout << "RESULT W(3.5)=" << newtonIntrpolation(3.5, "MN-2-p1.txt") << "\n";
    std::cout << "RESULT W(-1)= " << newtonIntrpolation(-1, "MN-2-p2.txt") << "\n";
    std::cout << "RESULT W(2)= " << newtonIntrpolation(2, "MN-2-p2.txt");
	return 0;
}
