#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include <ctime>
using namespace std;

bool find(string a, vector <string> arr);
void toLowercase(string &s);
void getCurrentTime(int sec);

int main(int argc, char* argv[]) 
{
	getCurrentTime(time(NULL));

	setlocale(LC_ALL, ".UTF-8");

	string path = "input.txt";
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

	if (argc == 2) 
	{
		path = argv[1];
	}

	file.open(path);
	if (!file.is_open()) 
	{
		cout << "Ошибка! Файл с именем " << path << " не найден..." << endl;
		return 1;
	}

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

	getCurrentTime(time(NULL));

	double programm_runtime = (double) clock() / CLOCKS_PER_SEC; 
	cout << fixed << setprecision(2) << "На выполнение программы понадобилось " << programm_runtime << " секунд" << endl;
 
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

void getCurrentTime(int sec) 
{
	int current_time = sec % (24 * 3600);
	int hours = (current_time / 3600 + 3) % 24;
	int minutes = (current_time % 3600) / 60;
	int seconds = current_time % 60;
	cout << setfill('0') << setw(2) << hours;
	cout << ":"; 
	cout << setfill('0') << setw(2) << minutes;
	cout << ":"; 
	cout << setfill('0') << setw(2) << seconds;
	cout << endl;
	return;
} 