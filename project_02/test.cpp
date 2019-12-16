/* gets example */
#include "stdafx.h"
#pragma warning(disable:4786)
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

int main()
{
	char string[256];
	cout << "Insert your full address: ";
	cin >> string;
	printf("Your address is: %s\n", string);
	return 0;
}