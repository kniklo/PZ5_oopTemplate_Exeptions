#pragma once
#include "Matrix.h"
using namespace std;

int main()
{
	// объявляем матрицу со значениями int
	Matrix<int> m1;
	cout << "Enter first matrix";
	_getch();
	// перегруженный оператор ввода матрицы
	cin >> m1;
	cout << endl;
	// перегруженный оператор вывода матрицы
	cout << m1;
	cout << endl;

	// демонстрация обработки исключения
	// запрос индексов row, col для вывода элемента с такими индексами
	// при превышении размеров матрицы, вызывается исключение
	int i, j;
	cout << "Enter row index";	
	cin >> i;
	cout << "Enter col index";
	cin >> j;
	try
	{	
		// перегруженный оператор скобки ( )
		cout << m1(i, j);
	}
	catch (exception& exept)
	{			
		cout << exept.what();
	}
	//перегруженный оператор присваивания матрицы числу
	m1 = 12;
	cout << endl << m1;
	//перегруженный оператор сложения матрицы с числом
	m1 = m1 + 7;
	// ввод второй матрицы
	Matrix<int> m2;
	cout << "Enter second matrix";
	_getch();
	cin >> m2;	
	// демонстрация перегруженного оператора сложения двух матриц
	// при несовпадении размеров, вызывается исключение
	try
	{
		m1 = m1 + m2;		
	}
	catch (exception& exept)
	{
		cout << exept.what();
	}
	cout << endl << m1;
	_getch();
}