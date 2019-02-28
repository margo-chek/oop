#include "pch.h"

using namespace std;
typedef double Matrix3x3[3][3];
const unsigned matrixSize = 3;

void PrintMatrix3x3(const Matrix3x3 matrix)
{
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
			cout << setw(15) << right << fixed << setprecision(3) << matrix[i][j];
		cout << "\n";
	}
}

double Calculate1Minor3x3(const Matrix3x3 matrix, int row, int col)
{
	double matrix2x2[2][2];
	int iDst = 0, jDst = 0;
	for (int iSrc = 0; iSrc < 3; iSrc++)
	{
		jDst = 0;
		if (iSrc != row)
		{
			for (int jSrc = 0; jSrc < matrixSize; jSrc++)
				if (jSrc != col)
					matrix2x2[iDst][jDst++] = matrix[iSrc][jSrc];
			iDst++;
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

void TransposeMatrix3x3(const Matrix3x3 src, Matrix3x3 dst)
{
	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
			dst[i][j] = src[j][i];
}

void BuildMinorMatrix3x3(const Matrix3x3 src, Matrix3x3 dst)
{
	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
		{
			dst[i][j] = Calculate1Minor3x3(src, i, j);
			if ((i + j) % 2)
				dst[i][j] *= -1;
		}
}

void MultiMatrix3x3ByNum(Matrix3x3 matrix, double number)
{
	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
			matrix[i][j] *= number;
}

bool InvertMatrix(const Matrix3x3 src, Matrix3x3 dst)
{
	double determinant = CalculateDeterminant3x3(src);
	if (fabs(determinant) < 0.1E-10)
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
	return move(strm);
}

bool GetMatrix3x3FromFile(Matrix3x3 matrix, const string & fileName)
{
	ifstream inFile = OpenFileForReading(fileName);
	if (!inFile)
		return false;

	for (int i = 0; i < matrixSize; i++)
	{
		string str;
		if (!getline(inFile, str))
			return false;
		istringstream row;
		row.str(str);
		for (int j = 0; j < matrixSize; j++)
		{
			row >> matrix[i][j];
			if (row.fail())
				return false;
		}
	}
	return true;
}

void MultiMatrix3x3(Matrix3x3 m1, Matrix3x3 m2, Matrix3x3 resultMatrix) //for checking
{
	for (int i = 0; i < matrixSize; i++)
		for (int j = 0; j < matrixSize; j++)
		{
			resultMatrix[i][j] = 0;
			for (int k = 0; k < matrixSize; k++)
				resultMatrix[i][j] += m1[i][k] * m2[k][j];
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
