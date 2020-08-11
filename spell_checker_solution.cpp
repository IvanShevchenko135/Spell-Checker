#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
using namespace std;

bool find(string a, vector <string> arr);
void toLowercase(string &s);

int main() 
{
	std::setlocale(LC_ALL, ".UTF-8");

	string ch = "АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзиклмнопрстуфхцчшщъыьэюя"; //пр
	for (int i = 1; i < ch.size(); i += 2)
	{
		cout << (int)ch[i] << " " << (i + 1) / 2 - 31 << endl;
	}
	
	ifstream file;
	ifstream words;
	vector <string> dictionary;
	regex yo_regex("ё");
	
	string line;
	string word;

	words.open("russian_dictionary.txt");
	while (words >> word)
	{
		word = regex_replace(word, yo_regex, "е");
		dictionary.push_back(word);
	}
	words.close();

	sort(dictionary.begin() + 18850, dictionary.begin() + 19130);

	file.open("input.txt");

	vector <string> mistake;
	vector <int> row;
	vector <int> column;
 
	for (int i = 1; getline(file, line); i++)
	{
		stringstream line_stream(line);
		for (int j = 1; line_stream >> word; j++)
		{
			toLowercase(word);
			int n = word.size() - 1;
			if ((int)word[n] > 32 || (int)word[n] < 64)
			{
				word.pop_back();
			}
			if (find(word, dictionary) == false)
			{
				mistake.push_back(word);
				row.push_back(i);
				column.push_back(j);
			}
		}
	}

	file.close();

	int n = mistake.size();
	cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		cout << mistake[i] << " : " << row[i] << " : " << column[i] << endl;
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

void toLowercase(string &s)
{
	//TODO
}