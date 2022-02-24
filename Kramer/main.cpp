#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;


//���������� ������� matrix ��� row-�� ������ � col-���� �������, ��������� � newMatrix
void getMatrixWithoutRowAndCol(int** matrix, int size, int row, int col, int** newMatrix) {
	int offsetRow = 0; //�������� ������� ������ � �������
	int offsetCol = 0; //�������� ������� ������� � �������
	for (int i = 0; i < size - 1; i++) {
		//���������� row-�� ������
		if (i == row) {
			offsetRow = 1; //��� ������ ��������� ������, ������� ���� ����������, ������ �������� ��� �������� �������
		}

		offsetCol = 0; //�������� �������� �������
		for (int j = 0; j < size - 1; j++) {
			//���������� col-�� �������
			if (j == col) {
				offsetCol = 1; //��������� ������ �������, ��������� ��� ���������
			}

			newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
		}
	}
}


int matrixDet(int** matrix, int size) {
	int det = 0;
	int degree = 1; // (-1)^(1+j) �� ������� ������������

	//������� ������ �� ��������
	if (size == 1) {
		return matrix[0][0];
	}
	//������� ������ �� ��������
	else if (size == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		//������� ��� ������ � �������
		int** newMatrix = new int* [size - 1];
		for (int i = 0; i < size - 1; i++) {
			newMatrix[i] = new int[size - 1];
		}

		//������������ �� 0-�� ������, ���� ����� �� ��������
		for (int j = 0; j < size; j++) {
			//������� �� ������� i-� ������ � j-�� �������
			//��������� � newMatrix
			getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

			//����������� �����
			//�� �������: ����� �� j, (-1)^(1+j) * matrix[0][j] * minor_j (��� � ���� ����� �� �������)
			//��� minor_j - �������������� ����� �������� matrix[0][j]
			// (�������, ��� ����� ��� ������������ ������� ��� 0-�� ������ � j-�� �������)
			det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
			//"�����������" ������� ���������
			degree = -degree;
		}

		//������ ������ �� ������ ���� ��������(�����!)
		for (int i = 0; i < size - 1; i++) {
			delete[] newMatrix[i];
		}
		delete[] newMatrix;
	}

	return det;
}

void showMatrix(int** arr,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void change(int n, int** arr, int* arr2,int s)
{
	int tmp;
	for (int i = 0; i < n; i++)
	{
		tmp = arr[i][s];
		arr[i][s] = arr2[i];
		arr2[i] = tmp;
	}
}
void func(int n, int** arr, int* arr2)
{
	int tmp;
	int det = matrixDet(arr, n);
	bool flag = false;
	for (int i = 0; i < n; i++)
	{
		
			int detX = 0;
			
			    change(n, arr, arr2,i);
				showMatrix(arr, n);
				detX = matrixDet(arr, n);
				cout <<"detX= "<< detX<<endl;
				cout << "X" << i << "=" << (float)detX / det<<endl;
				change(n, arr, arr2,i);



			
		

		
	}
}
int main()
{
	int n;
	cin >> n;
	///cin >> d;
	int** arr = new int* [n];
	int* arr2 = new int[n];
	ifstream ff("file.txt");
	ifstream ff2("file2.txt");
	for (int i = 0; i < n; i++) arr[i] = new int [n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ff >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout<< arr[i][j]<<" ";
		}
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < n; i++)
	{
		ff2 >> arr2[i];
	}

	for (int i = 0; i < n; i++)
	{
		cout<< arr2[i]<<" ";
	}
	cout << endl;

	func(n, arr, arr2);
	cout << endl;
	cout << matrixDet(arr, n);
	

	

	

	return 0; 
}