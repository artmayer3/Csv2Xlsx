#include <iostream>
#include <fstream>
#include <string>
#include <OpenXLSX.hpp>

using namespace std;
using namespace OpenXLSX;

vector<string> split(string phrase, string delimiter)
{
	vector<string> list;
	string s = phrase;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos)
	{
		token = s.substr(0, pos);
		list.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	list.push_back(s);
	return list;
}

int Create(vector<string> input) 
{
    XLDocument doc;
    doc.create("./Result.xlsx");
    auto wks = doc.workbook().worksheet("Sheet1");

	int i = 1;
	for (auto &line : input)
	{
		auto a = split(line, ",");
		wks.row(i).values() = a;
		i++;
	}

    doc.save();
    doc.close();

    return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	string fname;
	cout << "Введите имя файла(.csv):" << endl;
	cin >> fname;

	ifstream file(fname);
	if (!file.is_open()) 
	{
		cout << "Ошибка: Файл не открыт!" << endl;
	}

	vector<string> input;
	if (file.is_open())
	{
		while (file.good())
		{
			string line;
			getline(file, line);
			input.push_back(line);
			cout << line << endl;
		}
	}
	file.close();
	Create(input);

	return 0;
}