#pragma once
#include "Matrix.h"
using namespace std;

int main()
{
	// ��������� ������� �� ���������� int
	Matrix<int> m1;
	cout << "Enter first matrix";
	_getch();
	// ������������� �������� ����� �������
	cin >> m1;
	cout << endl;
	// ������������� �������� ������ �������
	cout << m1;
	cout << endl;

	// ������������ ��������� ����������
	// ������ �������� row, col ��� ������ �������� � ������ ���������
	// ��� ���������� �������� �������, ���������� ����������
	int i, j;
	cout << "Enter row index";	
	cin >> i;
	cout << "Enter col index";
	cin >> j;
	try
	{	
		// ������������� �������� ������ ( )
		cout << m1(i, j);
	}
	catch (exception& exept)
	{			
		cout << exept.what();
	}
	//������������� �������� ������������ ������� �����
	m1 = 12;
	cout << endl << m1;
	//������������� �������� �������� ������� � ������
	m1 = m1 + 7;
	// ���� ������ �������
	Matrix<int> m2;
	cout << "Enter second matrix";
	_getch();
	cin >> m2;	
	// ������������ �������������� ��������� �������� ���� ������
	// ��� ������������ ��������, ���������� ����������
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