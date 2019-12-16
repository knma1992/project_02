#include "stdafx.h"
#pragma warning(disable:4786)
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;


int main()
{
	int num_rows, num_cols, n = 0;

	cout << "Insert desired amount of rows: ";
	cin >> num_rows;
	cout << "\n Insert desired amount of coloums: ";
	cin >> num_cols;

	/*
... Stuff where you get input from the user, specifically the num of rows and cols
... Say these vals were stored in 2 ints num_rows and num_cols
*/
	std::vector<std::vector<int> > mat(num_rows, std::vector<int>(num_cols));
	for (int i = 0; i < num_rows; i++) {
		mat[i].resize(num_cols); // this will allow you to now just use [][] to access stuff
	}
	for (int i = 0; i < num_cols; i++)
	{
		for (int j=0; j < num_rows; j++)
		{
			mat[i][j] = n;
			n++;
		}
	}

	for (int i = 0; i < num_cols; i++)
	{
		for (int j = 0; j < num_rows; j++)
		{
			cout << mat[i][j];
			cout << " ";
		}
		cout << "\n";
	}

	

}

