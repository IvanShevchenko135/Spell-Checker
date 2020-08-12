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
	setlocale(LC_ALL, ".UTF-8");

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
			word = regex_replace(word, yo_regex, "е");
			toLowercase(word);
			int n = word.size() - 1;
			if ((int)word[n] > 32 && (int)word[n] < 64)
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
	for (int i = 0; i < s.size();)
	{
		if ((int)s[i] < 97 && (int)s[i] > 64)
		{
			s[i] += 32;
			i++;
		}
		else if ((int)s[i] == -48)
		{
			if ((int)s[i + 1] < -96 && (int)s[i + 1] > -113) 
			{
				s[i + 1] += 32;
			}
			else if ((int)s[i + 1] < -80 && (int)s[i + 1] > -97)
			{
				s[i + 1] -= 32;
				s[i]++;
			}
			i += 2;
		}
		else i++;
	}
	return;
}