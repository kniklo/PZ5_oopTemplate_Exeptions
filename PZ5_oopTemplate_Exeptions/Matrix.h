#pragma once
#include <iostream>
#include <typeinfo>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;


template <class T> //шаблонный класс контейнер
class Matrix
{
private:
	T** _m;	 //свойство класса - динамический двумерный массив, содержащий элементы контейнера
	int _rows, _cols;	//размеры матрицы
	T _converted;	//переменная для конвертирования из строки при вводе элементов матрицы

	// функция проверки корректности ввода элемента матрицы
	bool convert(string st)
	{		
		bool res = true;
		// если ввели пустое значение, возвращаем false
		if (st == "")
		{
			res = false;
		}
		// если тип элементов матрицы - int, будем конвертировать в int
		else if (typeid(T) == typeid(int))
		{
			try
			{
				//пробуем конвертировать введенный элемент
				_converted = stoi(st);
			}
			// при ошибке конвертации, обрабатываем исключение - возвращаем false
			catch (exception& exept)
			{				
				res = false;
			}			
		}
		// если тип элементов матрицы - float, будем конвертировать в float
		else if (typeid(T) == typeid(float))
		{
			try
			{
				//пробуем конвертировать введенный элемент
				_converted = stof(st);
			}
			// при ошибке конвертации, обрабатываем исключение - возвращаем false
			catch (exception& exept)
			{
				res = false;
			}
		}		
		return res;
	}
public:
	// конструктор по умолчанию: инициализирует пустой массив, размер устанавливает в 0
	Matrix()
	{
		cout << "Default constructor of Matrix\n";		
		_m = new T * [0];
		_rows = 0;
		_cols = 0;
		T* _converted = new T;
	}
	~Matrix()
	{
		{
			delete[] _m; //удаляем массив - освобождаем память, занятую динамическим массивом
		}
	}	
	//перегруженный оператор ввода
	friend istream& operator>> (istream& in, Matrix& m)	
	{	
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // получаем ссылку на консоль вывода
		COORD pos;	// здесь будет позиция курсора
		SHORT pos_x, pos_y;	// позиция курсора по x, y
		system("cls");	//очистка экрана
		cout << "Enter rows number:\n";		
		cin >> m._rows;		//запрос количества рядков
		cout << "Enter cols number:\n";
		cin >> m._cols;		//запрос количества столбцов
		cin.ignore(1, '\n');	// удаляем из потока ввода оставшийся enter
		m._m = new T * [m._rows];	//создаем массив указателей на рядки матрицы		
		string st;		
		for (int i = 0; i < m._rows; i++)
		{
			m._m[i] = new T[m._cols];	// создаем массив указателей на столбцы
			for (int j = 0; j < m._cols; j++)
			{				
				do
				{	
					// перевод курсора в нужную позицию на экране для красивого ввода
					pos_x = 15 + j * 10;
					pos_y = 5 + i;
					pos = { pos_x , pos_y };
					SetConsoleCursorPosition(hConsole, pos);
					getline(cin, st);	// вводим значение элемента матрицы
					// пробуем конвертировать значение элемента
					if (m.convert(st))
					{	
						// если норм - заполняем
						m._m[i][j] = m._converted;
						break;
					}
					// если нет - выводим предупреждающую надпись и ждем
					// по любой кнопке стираем надпись и вводим новое значение элемента
					// по esc - выходим из программы
					else
					{	
						SetConsoleCursorPosition(hConsole, pos);
						SetConsoleTextAttribute(hConsole, 12);
						cout << "FAIL!!!";
						SetConsoleTextAttribute(hConsole, 15);
						int ch = _getch();
						SetConsoleCursorPosition(hConsole, pos);
						cout << "       ";
						if (ch == 27)
						{
							return in;
						}
					}
				} while (true);				
			}						
		}
		return in;
	}	
	// перегруженный оператор вывода
	friend ostream& operator<< (ostream& out, const Matrix& m)
	{		
		for (int i = 0; i < m._rows; i++)
		{
			for (int j = 0; j < m._cols; j++)
			{	
				cout.width(10);
				cout << m._m[i][j];
			}
			cout << endl;
		}
		return out;
	}
	//перегруженный оператор получения значения по индексам внутри скобок
	T& operator () (int row, int col)
	{
		if (row >= _rows or col >= _cols)
		{
			throw runtime_error("Out of matrix ranges");
		}
		else
		{
			return _m[row][col];
		}
	}
	// перегруженный оператор: все элементы матрицы приравниваются заданному значению
	Matrix& operator = (T value)
	{
		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _cols; j++)
			{
				_m[i][j] = value;
			}
		}
		return *this;
	}
	// перегруженный оператор сложения матрицы с числом: все элементы матрицы складываются с этим числом	
	Matrix& operator + (T value)
	{
		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _cols; j++)
			{
				_m[i][j] = _m[i][j] + value;
			}
		}
		return *this;
	}
	// перегруженный оператор сложения двух матриц
	// проверяется равность размеров матриц, при несовпадении вызывается исключение
	Matrix& operator + (const Matrix& m)
	{
		if (m._rows != _rows or m._cols != _cols)
		{
			throw runtime_error("Ranges of matrixes not equal");
		}
		else
		{
			for (int i = 0; i < _rows; i++)
			{
				for (int j = 0; j < _cols; j++)
				{
					_m[i][j] = _m[i][j] + m._m[i][j];
				}
			}
		}
		return *this;
	}
};