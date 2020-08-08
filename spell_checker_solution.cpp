#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool find(string a, vector <string> arr);

int main() 
{
	ifstream file;
	ifstream words;
	vector <string> dictionary;
	setlocale(LC_ALL, "en_US.UTF-8");

	string word;

	words.open("C:\\Vanya\\Docs\\Spell-Checker\\russian_dictionary.txt");
	while (words >> word)
	{
		dictionary.push_back(word);
	}
	words.close();

	file.open("C:\\Vanya\\Docs\\Spell-Checker\\input.txt");
	while (file >> word)
	{
		//TODO
	}
	return 0;
}

bool find(string key, vector <string> arr)
{
	int l = 0, r = arr.size() - 1, c;

	while (l < r)
	{
		c = (l + r) / 2;
		if (arr[c] < key) l = c + 1;
		else r = c;
	}

	if (arr[l] == key) return true;
	else return false;
}