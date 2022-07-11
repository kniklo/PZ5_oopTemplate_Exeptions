#pragma once
#include <iostream>
#include <typeinfo>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;


template <class T> //��������� ����� ���������
class Matrix
{
private:
	T** _m;	 //�������� ������ - ������������ ��������� ������, ���������� �������� ����������
	int _rows, _cols;	//������� �������
	T _converted;	//���������� ��� ��������������� �� ������ ��� ����� ��������� �������

	// ������� �������� ������������ ����� �������� �������
	bool convert(string st)
	{		
		bool res = true;
		// ���� ����� ������ ��������, ���������� false
		if (st == "")
		{
			res = false;
		}
		// ���� ��� ��������� ������� - int, ����� �������������� � int
		else if (typeid(T) == typeid(int))
		{
			try
			{
				//������� �������������� ��������� �������
				_converted = stoi(st);
			}
			// ��� ������ �����������, ������������ ���������� - ���������� false
			catch (exception& exept)
			{				
				res = false;
			}			
		}
		// ���� ��� ��������� ������� - float, ����� �������������� � float
		else if (typeid(T) == typeid(float))
		{
			try
			{
				//������� �������������� ��������� �������
				_converted = stof(st);
			}
			// ��� ������ �����������, ������������ ���������� - ���������� false
			catch (exception& exept)
			{
				res = false;
			}
		}		
		return res;
	}
public:
	// ����������� �� ���������: �������������� ������ ������, ������ ������������� � 0
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
			delete[] _m; //������� ������ - ����������� ������, ������� ������������ ��������
		}
	}	
	//������������� �������� �����
	friend istream& operator>> (istream& in, Matrix& m)	
	{	
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ������ �� ������� ������
		COORD pos;	// ����� ����� ������� �������
		SHORT pos_x, pos_y;	// ������� ������� �� x, y
		system("cls");	//������� ������
		cout << "Enter rows number:\n";		
		cin >> m._rows;		//������ ���������� ������
		cout << "Enter cols number:\n";
		cin >> m._cols;		//������ ���������� ��������
		cin.ignore(1, '\n');	// ������� �� ������ ����� ���������� enter
		m._m = new T * [m._rows];	//������� ������ ���������� �� ����� �������		
		string st;		
		for (int i = 0; i < m._rows; i++)
		{
			m._m[i] = new T[m._cols];	// ������� ������ ���������� �� �������
			for (int j = 0; j < m._cols; j++)
			{				
				do
				{	
					// ������� ������� � ������ ������� �� ������ ��� ��������� �����
					pos_x = 15 + j * 10;
					pos_y = 5 + i;
					pos = { pos_x , pos_y };
					SetConsoleCursorPosition(hConsole, pos);
					getline(cin, st);	// ������ �������� �������� �������
					// ������� �������������� �������� ��������
					if (m.convert(st))
					{	
						// ���� ���� - ���������
						m._m[i][j] = m._converted;
						break;
					}
					// ���� ��� - ������� ��������������� ������� � ����
					// �� ����� ������ ������� ������� � ������ ����� �������� ��������
					// �� esc - ������� �� ���������
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
	// ������������� �������� ������
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
	//������������� �������� ��������� �������� �� �������� ������ ������
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
	// ������������� ��������: ��� �������� ������� �������������� ��������� ��������
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
	// ������������� �������� �������� ������� � ������: ��� �������� ������� ������������ � ���� ������	
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
	// ������������� �������� �������� ���� ������
	// ����������� �������� �������� ������, ��� ������������ ���������� ����������
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