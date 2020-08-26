#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include <ctime>
using namespace std;

unsigned long long p[100];

struct T_dictionary
{
	long long hash;
	string word;
};

bool find(string key, vector <T_dictionary> arr);
bool comp (T_dictionary a, T_dictionary b);
void toLowercase(string &s);
void getCurrentTime(int sec);

int main(int argc, char* argv[]) 
{
	getCurrentTime(time(NULL));

	setlocale(LC_ALL, ".UTF-8");

	string path = "input.txt";
	ifstream file;
	ifstream words;
	vector <T_dictionary> dictionary;
	regex yo_regex("ё");
	
	string line;
	string word;

	//Расчет степеней числа p (61)
	p[0] = 1;
	for (int i = 1; i < 100; i++)
	{
		p[i] = p[i - 1] * 61;
	}

	words.open("russian_dictionary.txt");
	while (words >> word)
	{
		word = regex_replace(word, yo_regex, "е");
		long long hash = 0;
		int n = word.size();
		for (int i = 0; i < n; i++)
		{
			hash += (int) word[i] * p[i];
		}
		T_dictionary tmp;
		tmp.hash = hash;
		tmp.word = word;
		dictionary.push_back(tmp);
	}
	words.close();

	sort(dictionary.begin(), dictionary.end(), comp);

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
			if (word == "–") continue;
			word = regex_replace(word, yo_regex, "е");
			toLowercase(word);
			int n = word.size() - 1;
			if ((int)word[n] > 32 && (int)word[n] < 64)
			{
				word.pop_back();
			}
			while ((int)word[n] == 46) word.pop_back();
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

bool find(string key, vector <T_dictionary> arr)
{
	int l = 0, r = arr.size() - 1, c;
	long long hash = 0;
	int n = key.size(); 
	for (int i = 0; i < n; i++) 
	{
		hash += (int) key[i] * p[i]; 
	}
	while (l < r)
	{
		c = (l + r) / 2; 
		if (arr[c].hash < hash) l = c + 1;
		else r = c; 
	}

	if (arr[l].hash == hash)
	{
		c = l;
		for (int l = c - 1; arr[l].hash == arr[c].hash; l--) 
		{
			if (arr[l].word == key) return true; 
		}
		for (int r = c; arr[r].hash == arr[c].hash; l++) 
		{
			if (arr[r].word == key) return true; 
		}
	}
	return false;
}

bool comp (T_dictionary a, T_dictionary b)
{
	return a.hash < b.hash;
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