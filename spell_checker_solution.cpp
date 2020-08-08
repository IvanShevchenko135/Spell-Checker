#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

bool find(string a, vector <string> arr);

int main() 
{
	setlocale(LC_ALL, "Russian");

	ifstream file;
	ifstream words;
	vector <string> dictionary;
	regex yo_regex("¸");
	string word;

	words.open("C:\\Vanya\\Docs\\Spell-Checker\\russian_dictionary.txt");
	while (words >> word)
	{
		word = regex_replace(word, yo_regex, "å");
		dictionary.push_back(word);
	}
	words.close();

	sort(dictionary.begin() + 18850, dictionary.begin() + 19130);

	file.open("C:\\Vanya\\Docs\\Spell-Checker\\input.txt");
	while (file >> word)
	{
		transform(word.begin(), word.end(), word.begin(), tolower);
		if ((int)word[word.size() - 1] > -1 || (int)word[word.size() - 1] < -32)
		{
			word.pop_back();
		}
		if (!find(word, dictionary))
		{
			cout << word << endl;
		}
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