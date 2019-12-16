//Hasharray Uebungsaufgabe

#include <iostream>
#include <fstream> 
#include <deque>
#include <vector>
using namespace std;

void main(void)
{
	string word;
	char A;
	ifstream file;

	vector<deque<string>> deq2(211);
	
	int ii = 0;
	int temp_int = 0;
	int SI;
	int temp;

	file.open("Text.txt");	// Stream class to read from file

	while (file >> word)
	{
		while (word[ii] != '\0')
		{
			temp = (int)word[ii];
			if (((temp < 91) && (temp > 64)) || ((temp < 123) && (temp > 96)))
			{
				temp_int = temp_int + (int)word[ii];
			}
			else
			{
			
			}
			//cout << (int)word[ii] << ' ';
			ii++;
		}
		SI = temp_int % 211;
	
		//cout << "SI = " << SI << ' ';
		//cout << word << '\n';
		ii = 0;
		deq2[SI].push_back(word);
		temp_int = 0;
	}
	deque<string>::iterator pdeque;

	for (int n = 0; n < 210; n++)
	{
		
		for (pdeque = deq2[n].begin(); pdeque != deq2[n].end(); pdeque++)
		{
			cout << *pdeque << " ";
		}
		if (deq2[n].empty());
		else  cout << "\n"; 
	}	
}