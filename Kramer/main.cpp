#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;


//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
void getMatrixWithoutRowAndCol(int** matrix, int size, int row, int col, int** newMatrix) {
	int offsetRow = 0; //Смещение индекса строки в матрице
	int offsetCol = 0; //Смещение индекса столбца в матрице
	for (int i = 0; i < size - 1; i++) {
		//Пропустить row-ую строку
		if (i == row) {
			offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
		}

		offsetCol = 0; //Обнулить смещение столбца
		for (int j = 0; j < size - 1; j++) {
			//Пропустить col-ый столбец
			if (j == col) {
				offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
			}

			newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
		}
	}
}


int matrixDet(int** matrix, int size) {
	int det = 0;
	int degree = 1; // (-1)^(1+j) из формулы определителя

	//Условие выхода из рекурсии
	if (size == 1) {
		return matrix[0][0];
	}
	//Условие выхода из рекурсии
	else if (size == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		//Матрица без строки и столбца
		int** newMatrix = new int* [size - 1];
		for (int i = 0; i < size - 1; i++) {
			newMatrix[i] = new int[size - 1];
		}

		//Раскладываем по 0-ой строке, цикл бежит по столбцам
		for (int j = 0; j < size; j++) {
			//Удалить из матрицы i-ю строку и j-ый столбец
			//Результат в newMatrix
			getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

			//Рекурсивный вызов
			//По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
			//где minor_j - дополнительный минор элемента matrix[0][j]
			// (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
			det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
			//"Накручиваем" степень множителя
			degree = -degree;
		}

		//Чистим память на каждом шаге рекурсии(важно!)
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