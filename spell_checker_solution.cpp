#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() 
{
	ifstream file;
	ifstream dictionary;

	setlocale(LC_ALL, "en_US.UTF-8");
	file.open("C:\\Vanya\\Docs\\Spell-Checker\\input.txt");

	string word; 

	while (file >> word)
	{
		//TODO
	}

	return 0;
}