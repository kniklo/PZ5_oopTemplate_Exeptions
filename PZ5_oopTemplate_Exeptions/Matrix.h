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
	int _rows, _cols;
	T _converted;

	bool convert(string st)
	{		
		bool res = true;
		if (st == "")
		{
			res = false;
		}
		else if (typeid(T) == typeid(int))
		{
			try
			{
				_converted = stoi(st);
			}
			catch (exception& exept)
			{				
				res = false;
			}			
		}
		else if (typeid(T) == typeid(float))
		{
			try
			{
				_converted = stof(st);
			}
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
		T _converted;
	}
	~Matrix()
	{
		{
			delete[] _m; //удаляем массив - освобождаем память, занятую динамическим массивом
		}
	}	
	friend istream& operator>> (istream& in, Matrix& m)	
	{	
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		SHORT pos_x, pos_y;
		cout << "Enter rows number:\n";		
		cin >> m._rows;		
		cout << "Enter cols number:\n";
		cin >> m._cols;
		cin.ignore(1, '\n');
		m._m = new T * [m._rows];		
		string st;		
		for (int i = 0; i < m._rows; i++)
		{
			m._m[i] = new T[m._cols];
			for (int j = 0; j < m._cols; j++)
			{				
				do
				{			
					pos_x = 5 + j * 10;
					pos_y = 5 + i;
					pos = { pos_x , pos_y };
					SetConsoleCursorPosition(hConsole, pos);
					getline(cin, st);
					if (m.convert(st))
					{
						m._m[i][j] = m._converted;
						break;
					}
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
};