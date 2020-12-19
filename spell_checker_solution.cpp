#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include <ctime>
using namespace std;

regex yo_regex("ё");

vector<string> dictionary_vector;
set<string> dictionary_set;

bool find(string a);
bool type(string t);
bool isExist(string path);
void toLowercase(string &s);
void getCurrentTime(int sec);

struct mistake 
{
	string word;
	int row;
	int column;
};

class SpellChecker 
{
private: 
	string input_path = "input.txt";
	string dictionary_path = "dictionary.txt";
	bool vector_check = false;	
public:
	SpellChecker(string input_path, string dictionary_path, bool vector_check);
	vector <mistake> process();
};

int main(int argc, char *argv[])
{
	getCurrentTime(time(NULL));

	setlocale(LC_ALL, ".UTF-8");

	string path = "input.txt";
	bool vector_check;

	if (argc > 1) path = argv[1];
	if (argc > 2 && type(argv[2])) vector_check = true;

	SpellChecker Test(path, "russian_dictionary.txt", vector_check);
	vector <mistake> test_mistake = Test.process();

	int n = test_mistake.size();
	cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		cout << test_mistake[i].word << " : " << test_mistake[i].row << " : " << test_mistake[i].column << endl;
	}

	getCurrentTime(time(NULL));

	double programm_runtime = (double)clock() / CLOCKS_PER_SEC;
	cout << fixed << setprecision(2) << "На выполнение программы понадобилось " << programm_runtime << " секунд" << endl;

	return 0;
}

SpellChecker::SpellChecker(string input_path, string dictionary_path, bool vector_check) 
{
	if (isExist(input_path)) 
	{
		this->input_path = input_path;
	}
	else
	{
		cout << "Неверный путь к файлу!" << endl;
	}

	if (isExist(dictionary_path)) 
	{
		this->dictionary_path = dictionary_path;
	}
	else
	{
		cout << "Неверный путь к словарю!" << endl;
	}

	this->vector_check = vector_check;
}

vector <mistake> SpellChecker::process()
{
	ifstream file;
	ifstream words;

	string line;
	string word;

	words.open(dictionary_path);
	while (words >> word)
	{
		word = regex_replace(word, yo_regex, "е");
		if (vector_check == false)
			dictionary_set.insert(word);
		else
			dictionary_vector.push_back(word);
	}
	words.close();

	sort(dictionary_vector.begin(), dictionary_vector.end());

	file.open(input_path);

	vector <mistake> res;

	for (int i = 1; getline(file, line); i++)
	{
		stringstream line_stream(line);
		for (int j = 1; line_stream >> word; j++)
		{
			if (word == "–")
				continue;
			word = regex_replace(word, yo_regex, "е");
			int n = word.size() - 1;
			while ((int)word[n] > 32 && (int)word[n] < 64)
			{
				word.pop_back();
				n--;
			}
			while ((int)word[0] > 32 && (int)word[0] < 64)
			{
				word.erase(0, 1);
				n--;
			}
			if ((int)word[0] == -62)
			{
				word.erase(0, 2);
				n -= 2;
			}
			if ((int)word[n - 1] == -62)
			{
				word.pop_back();
				word.pop_back();
				n -= 2;
			}
			while ((int)word[n] > 32 && (int)word[n] < 64)
			{
				word.pop_back();
				n--;
			}
			while ((int)word[0] > 32 && (int)word[0] < 64)
			{
				word.erase(0, 1);
				n--;
			}
			toLowercase(word);
			if (vector_check == false)
			{
				if (dictionary_set.find(word) == dictionary_set.end())
				{
					mistake tmp;

					tmp.word = word;
					tmp.row = i;
					tmp.column = j;
					
					res.push_back(tmp);
				}
			}
			else
			{
				if (!find(word))
				{
					mistake tmp;

					tmp.word = word;
					tmp.row = i;
					tmp.column = j;
					
					res.push_back(tmp);
				}
			}
		}
	}
	file.close();

	return res;
}

bool find(string a)
{
	int l = 0, r = dictionary_vector.size() - 1, c;

	while (l < r)
	{
		c = (l + r) / 2;
		if (dictionary_vector[c] < a)
			l = c + 1;
		else
			r = c;
		if (a == "плечистый")
			cout << dictionary_vector[l] << endl;
	}

	if (dictionary_vector[l] == a)
		return true;
	else
		return false;
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
		else
			i++;
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

bool type(string t)
{
	if (t == "vector")
		return true;
	else
		return false;
}

bool isExist(string path)
{
    bool check = false;
    ifstream file(path);
 
    if(file.is_open())
        check = true;
 
    file.close();
    return check;
}