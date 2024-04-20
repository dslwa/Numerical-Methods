#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#define ITERATION 5

std::vector<std::vector<float>> readFile(std::string filename){
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) {
		std::cerr << "Unable to read a file!";
		EXIT_FAILURE;
	}
	int size;
	file >> size;
	std::vector<std::vector<float>> M(size, std::vector<float>(size + 1, 0));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size + 1; j++) {
			file >> M[i][j];
		}
	}
	file.close();
	return M;
}

void printVector(std::vector<float> v) {
	int g = 0;
	for (float i : v) {
		std::cout << "X[" << g++ << "]=" << i << " \n";
	}
}

void printMatrix(std::vector <std::vector<float>> matrix) {
	int n = matrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

std::vector<float> constructVector(std::vector<std::vector<float>>& M) {
	int n = M.size();
	std::vector<float> B(n, 0);
	for (int i = 0; i < n; i++) {
		int j = n;
		B[i] = M[i][n];
	}
	return B;
}

bool isDiagonallyDominant(std::vector<std::vector<float>> A) {
	int size = A.size();
	for (int i = 0; i < size; i++) {
		int sum = 0;
		for (int j = 0; j < size; j++) {
			if (i != j)
				sum += fabs(A[i][j]);
		}
		if (A[i][i] > sum) {
			std::cout << "Matrix is diagonally dominant\n";
			return true;
		}
	}
	std::cout << "Matrix is not diagonally dominant, can't use Jacobi method";
	return false;
}


void LDU(std::vector<std::vector<float>> &A, int n, std::vector<std::vector<float>>& L, std::vector<std::vector<float>> &D, std::vector<std::vector<float>> &U) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i > j)
				L[i][j] = A[i][j];
			else if (i == j)
				D[i][j] = A[i][j];
			else
				U[i][j] = A[i][j];
		}
	}
}

std::vector<std::vector<float>> LUaddition(std::vector<std::vector<float>>& L, std::vector<std::vector<float>>& U) {
	int size = L.size();
	std::vector<std::vector<float>> LU(size, std::vector<float>(size, 0));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			LU[i][j] = L[i][j] + U[i][j];
		}
	}
	return LU;
}

std::vector<std::vector<float>> Inverse(const std::vector<std::vector<float>>& D) {
	int size = D.size();
	std::vector<std::vector<float>> Dinversed(size, std::vector<float>(size, 0)); 

	for (int i = 0; i < size; i++) {
		if (D[i][i] == 0) {
			std::cerr << "Zero diagonal element found, matrix is not invertible.\n";
			throw std::runtime_error("Matrix is uninvertible.");
		}
		Dinversed[i][i] = 1 / D[i][i]; 
	}
	return Dinversed;
}

int JacobiMethod(std::vector<std::vector<float>>& A,std::vector<float>& B, std::vector<std::vector<float>>& Dinversed, 
	std::vector<std::vector<float>>& LU, int iters, std::vector<float> &X, std::vector<float> &X_old)
{
	int n = A.size();
	int iter;
	for (iter = 0; iter < iters; iter++) {
		for (int i = 0; i < n; i++) {
			float sum = 0.0;
			for (int j = 0; j < n; j++) {
				sum += LU[i][j] * X_old[j];
			}
			X[i] = Dinversed[i][i] * (B[i] - sum);
		}
		X_old = X;
	}
	return iter;

}


int JacobiMethod2(std::vector<std::vector<float>>& A, std::vector<float>& B, int n, std::vector<std::vector<float>>&Dinversed,
std::vector<std::vector<float>>& LU, float epsilon, std::vector<float>& X)
{
	std::vector<float> X_old(n, 0.0);
	std::vector<float> error(n, 100000.0);
	
	int iter = 0;
	while (true) {
		for (int i = 0; i < n; i++) {
			float sum = 0.0;
			for (int j = 0; j < n; j++) {
				if (i != j)
					sum += LU[i][j] * X_old[j];
			}
			X[i] = Dinversed[i][i] * (B[i] - sum);
		}
		bool flag = true;
		for (int i = 0; i < n; i++) {
			error[i] = fabs(X[i] - X_old[i]);
			if (error[i] > epsilon)
				flag = false;
			X_old[i] = X[i];
		}

		if (flag) {
			std::cout << "Solution:\n";
			printVector(X);
			std::cout << "Computed errror for each X:\n";
			printVector(error);
			break;
		}
		iter++;
		if (iter > 1000) {
			std::cout << "Jacobi do not executed after 1000 interations\n";
			break;
		}
	}
	return iter;
}
int main() {
	std::cout << "EXCERCISE 1\n";
	std::vector<std::vector<float>> A = readFile("RURL_Jacobi_dane1.txt");
	int size = A.size();
	std::cout << "Initial MATRIX\n";
	printMatrix(A);
	
	std::vector<float> B = constructVector(A);
	std::cout << "\nVector B: ";
	for (float A : B) {
		std::cout << A << " ";
	}
	std::cout << "\n";
	
	bool DiagonallyDominant = isDiagonallyDominant(A);
	
	if (DiagonallyDominant == false)
		return 1;

	std::vector<std::vector<float>> L(size, std::vector<float>(size, 0));
	std::vector<std::vector<float>> D(size, std::vector<float>(size, 0));
	std::vector<std::vector<float>> U(size, std::vector<float>(size, 0));

	LDU(A, size, L, D, U);
	
	std::cout << "L+U Matrix\n";
	std::vector < std::vector<float>> LU = LUaddition(L, U);
	printMatrix(LU);
	std::cout << "\n";
	std::vector<std::vector<float>> Dinversed = Inverse(D);
	std::cout << "Inversed Diagonal Matrix\n";
	printMatrix(Dinversed);

	std::vector<float> X(size, 0.0);
	std::vector<float> X_old(size, 0.0);

	int iters = JacobiMethod(A, B, Dinversed, LU, ITERATION, X, X_old);

	std::cout << "Solution after " << ITERATION << " iterations\n";
	std::cout << "Vector X: \n";
	printVector(X);


	std::cout << "EXERCISE 2" << "\n";
	float epsilon1 = 0.001;
	float epsilon2 = 0.000001;
	fill(X.begin(), X.end(), 0.0);
	fill(X_old.begin(), X_old.end(), 0.0);

	std::cout << "Jacobi for epsilon = " << epsilon1 << ":\n";
	int iterations1 = JacobiMethod2(A, B, size, Dinversed, LU, epsilon1, X);
	std::cout << "Num of iterations: " << iterations1 + 1 << "\n";

	fill(X.begin(), X.end(), 0.0);
	fill(X_old.begin(), X_old.end(), 0.0);

	std::cout << "Jacobi for epsilon = " << epsilon2 << ":\n";
	int iterations2 = JacobiMethod2(A, B, size, Dinversed, LU, epsilon2, X);
	std::cout << "Num of iterations: " << iterations2 + 1 << "\n";
	return 0;
}