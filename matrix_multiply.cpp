#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>  // For throwing exceptions

using namespace std;

// Validate file content and check for errors
void validateFile(ifstream &file, const string &filename) {
    if (!file.is_open())
    {
        throw runtime_error("Error opening file: " + filename);
    }
}

// Read a matrix from a file with error handling
void readMatrixFromFile(const string &filename, vector<vector<int>> &matrix, int &rows, int &cols) 
{
    ifstream file(filename);
    validateFile(file, filename);

    if (!(file >> rows >> cols) || rows <= 0 || cols <= 0) {
        throw runtime_error("Invalid matrix dimensions in file: " + filename);
    }

    matrix.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
              if (!(file >> matrix[i][j])) {
                throw runtime_error("Invalid matrix element in file: " + filename);
            }
        }
    }
}

// Perform matrix multiplication
vector<vector<int>> multiplyMatrices(const vector<vector<int>> &matrixA, const vector<vector<int>> &matrixB, int rowsA, int colsA, int rowsB, int colsB) {
    if (colsA != rowsB) {
        throw runtime_error("Matrix multiplication not possible: number of columns in Matrix A != number of rows in Matrix B");
    }

    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    // Matrix multiplication using triple nested loop (0(n^3))
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            int sum = 0;
            for (int k = 0; k < colsA; ++k) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

// Print out matrix
void printMatrix(const vector<vector<int>> &matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    try {
        // Define matrices, rows, and columns
        vector<vector<int>> matrixA, matrixB;
        int rowsA, colsA, rowsB, colsB;

        // Read matrices from the specified file paths
        readMatrixFromFile("/Users/sina/Downloads/Merson Project/matrixA_test_cases.txt", matrixA, rowsA, colsA);
        readMatrixFromFile("/Users/sina/Downloads/Merson Project/matrixB_test_cases.txt", matrixB, rowsB, colsB);

        // Perform matrix multiplication
        vector<vector<int>> result = multiplyMatrices(matrixA, matrixB, rowsA, colsA, rowsB, colsB);

        //  matrix result (product)
        cout << "Resultant Matrix:" << endl;
        printMatrix(result, rowsA, colsB);
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
