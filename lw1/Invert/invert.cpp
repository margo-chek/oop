#include "pch.h"

using namespace std;

const unsigned matrixSize = 3; //unsigned - неотрицательные значения
typedef double Matrix3x3[matrixSize][matrixSize]; // typedef - придать станд.типу новое имя и потом его использовать как стандартное


void PrintMatrix3x3(const Matrix3x3 matrix) //15-ширина поля,вправо,фиксир,3 знака после плав.запятой
{
	for (size_t row = 0; row < matrixSize; row++)//size_t - беззнаковый целочисленный тип
	{
		for (size_t col = 0; col < matrixSize; col++)
			cout << setw(15) << right << fixed << setprecision(3) << matrix[row][col];//setw - устанавливает ширину поля, которая будет использоваться в выходных операциях
		cout << "\n";
	}
}

double Calculate1Minor3x3(const Matrix3x3 matrix, size_t row, size_t col)
{
	double matrix2x2[2][2];
	size_t rowDst = 0, colDst = 0;
	for (size_t rowSrc = 0; rowSrc < matrixSize; rowSrc++)
	{
		colDst = 0;
		if (rowSrc != row)
		{
			for (size_t colSrc = 0; colSrc < matrixSize; colSrc++)
				if (colSrc != col)
					matrix2x2[rowDst][colDst++] = matrix[rowSrc][colSrc];
			rowDst++;
		}
	}
	return matrix2x2[0][0] * matrix2x2[1][1] - matrix2x2[0][1] * matrix2x2[1][0];
}

double CalculateDeterminant3x3(const Matrix3x3 matrix)
{
	double  det = 0;
	det += matrix[0][0] * Calculate1Minor3x3(matrix, 0, 0);
	det -= matrix[0][1] * Calculate1Minor3x3(matrix, 0, 1);
	det += matrix[0][2] * Calculate1Minor3x3(matrix, 0, 2);
	return det;
}

void BuildMinorMatrix3x3(const Matrix3x3 src, Matrix3x3 dst) // матрица алгебр.дополнений
{
	for (size_t row = 0; row < matrixSize; row++)
		for (size_t col = 0; col < matrixSize; col++)
		{
			dst[row][col] = Calculate1Minor3x3(src, row, col);
			if ((row + col) % 2)
				dst[row][col] *= -1;
		}
}

void TransposeMatrix3x3(const Matrix3x3 src, Matrix3x3 dst)
{
	for (size_t row = 0; row < matrixSize; row++)
		for (size_t col = 0; col < matrixSize; col++)
			dst[row][col] = src[col][row];
}

void MultiMatrix3x3ByNum(Matrix3x3 matrix, double number)
{
	for (size_t row = 0; row < matrixSize; row++)
		for (size_t col = 0; col < matrixSize; col++)
			matrix[row][col] *= number;
}

bool InvertMatrix(const Matrix3x3 src, Matrix3x3 dst)
{
	double determinant = CalculateDeterminant3x3(src);
	if (fabs(determinant) < 0.1E-10) // fabs вычисляет абсолютное значение (модуль)
		return false;

	Matrix3x3 minor;
	BuildMinorMatrix3x3(src, minor);
	TransposeMatrix3x3(minor, dst);
	MultiMatrix3x3ByNum(dst, 1 / determinant);
	return true;
}

ifstream OpenFileForReading(const string & fileName)
{
	ifstream strm(fileName);
	if (!strm.is_open())
	{
		cout << "Failed to open " << fileName << "\n";
	}
	return strm; 
}

bool GetMatrix3x3FromFile(Matrix3x3 matrix, const string & fileName)
{
	ifstream inFile = OpenFileForReading(fileName);
	if (!inFile)
		return false;

	for (size_t row = 0; row < matrixSize; row++)
	{
		string str;
		if (!getline(inFile, str))
			return false;
		istringstream rowIstr;
		rowIstr.str(str);
		for (size_t col = 0; col < matrixSize; col++)
		{
			rowIstr >> matrix[row][col];
			if (rowIstr.fail())
				return false;
		}
	}
	return true;
}

void MultiMatrix3x3(Matrix3x3 m1, Matrix3x3 m2, Matrix3x3 resultMatrix) //for checking
{
	for (size_t row = 0; row < matrixSize; row++)
		for (size_t col = 0; col < matrixSize; col++)
		{
			resultMatrix[row][col] = 0;
			for (size_t k = 0; k < matrixSize; k++)
				resultMatrix[row][col] += m1[row][k] * m2[k][col];
		}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: invert.exe <matrix file>\n";
		return 1;
	}

	Matrix3x3 matrix;
	if (!GetMatrix3x3FromFile(matrix, argv[1]))
	{
		cout << "Something's gone wrong while reading matrix.\n";
		return 1;
	}

	Matrix3x3 matrixInverted;
	if (!InvertMatrix(matrix, matrixInverted))
	{
		cout << "Determinant = 0. Inverted matrix doesn't exist.\n";
		return 0;
	}

	PrintMatrix3x3(matrixInverted);

	return 0;
}
