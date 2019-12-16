// Greedy-Router.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "stdafx.h"
#pragma warning(disable:4786)
#include <iostream>
#include <vector>

using std::vector;
using namespace std;

#define N  10
#define M  10


class net
 {
public:

	int index;
	vector<int> x;
	vector<int> y;

	net(int a, int b, int c)
	{
		index = a;
		x.push_back(b);
		y.push_back(c);
	}
	void add_point(int x_cord,int y_cord)
	{
		x.push_back(x_cord);
		y.push_back(y_cord);
		return;
	}
	void print_net()
	{
		cout << endl << endl<< "Net Number:" << index << "\n";
		cout << "X-Pos  | Y-Pos" << endl;
		for (int ii = 0; ii < y.size(); ii++)
		{
			cout << "[" << ii << "]=" << x.at(ii);
			cout << "   [" << ii << "]=" << y.at(ii) << endl;
		}
		return;

	}
};

	
class matrix
{
public:
	int** grid;
	const int rows;
	const int cols;

	matrix(int height, int width);
	~matrix();
	void print();
	void insert_net(net Nx);

};


matrix::matrix(int height, int width) : rows(height), cols(width)// constructor
{
	grid = new int* [height];
	for (int i = 0; i < height; i++)
	{
		grid[i] = new int[width];
	}

	for (int x = 0; x < this->rows; x++)
		for (int y = 0; y < this->cols; y++)
			this->grid[x][y] = 0;
}

void matrix::print()
{
	for (int i = 0; i < this->rows; i++)
	{
		cout << "\n";
		for (int j = 0; j < this->cols; j++)
		{
			cout << grid[i][j] << " ";
		}
	}

}

matrix::~matrix()// destructor
{
	for (int i = 0; i < rows; i++)
		delete[] grid[i];
	delete[] grid;
}

void matrix::insert_net(net Nx)
{
	for (int i = 0; i < Nx.x.size();i++)
	{
		if (this->grid[Nx.x.at(i)][Nx.y.at(i)] == 0)
			this->grid[Nx.x.at(i)][Nx.y.at(i)] = Nx.index;
		else
			cout << " Fehler Anschlusspunkt Überschneidung ";
	}
}


void add_net(vector<net> &Net, int index, int x ,int y) // fuegt Netz in Vector ein 
{
	net temp(index,x,y);
	Net.push_back(temp);
}

int main()
{
	vector<net> Net; // Vector aus Netzen 
	matrix	grid(N, M); // erstellt Raster der groesse NxM 

	add_net(Net, 1, 0, 4);// Basis Netz 1
	add_net(Net, 2, 0, 1);// Basis Netz 2
	add_net(Net, 3, 0, 6);// Basis Netz 3
	add_net(Net, 4, 0, 8);// Basis Netz 4

	Net.at(0).add_point(5, 0); // fügt Anschlusspunkt in Netz hinzu
	Net.at(0).add_point(9, 2);
	Net.at(1).add_point(9, 4);
	Net.at(2).add_point(9, 6);
	Net.at(3).add_point(5, 9);
	Net.at(3).add_point(9, 7);
	
	// Netze werden in Matrix eingefuegt
	for (int i =0; i<Net.size();i++)
	{
		grid.insert_net(Net.at(i));
	}
	
	grid.print();
	Net.at(0).print_net();
	






}