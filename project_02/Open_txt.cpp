#include <iostream> 
#include <fstream> 

using namespace std;

void main(void)
{
	const int BUFM = 80;
	char buffer[BUFM];

	ifstream infile("ISpruch.txt");	//ifstream: Stream class to read from file
	ofstream ofile("OSpruch.txt");	//ofstream: Stream class to write in file

	while (infile) {

		infile.getline(buffer, BUFM);
		//ofile << buffer << "\n";
		cout << buffer << "\n";

	}
}