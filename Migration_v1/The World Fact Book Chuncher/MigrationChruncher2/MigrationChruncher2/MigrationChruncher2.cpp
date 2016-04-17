// MigrationChruncher2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <functional> 
#include <cctype>
#include <locale>
#include <list>


using namespace std;
bool predicate(char c) {
	for (int i = 0; i < 10; i++) {
		if (c == '0' + i) {
			return false;
		}
	}
	if (c == '.') {
		return false;
	}
	return true;
}

string onlyNumbers(string s) {
	s.erase(std::remove_if(s.begin(), s.end(), predicate), s.end());
	return s;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}
// trim from start (copying)
static inline std::string ltrimmed(std::string s) {
	ltrim(s);
	return s;
}

// trim from end (copying)
static inline std::string rtrimmed(std::string s) {
	rtrim(s);
	return s;
}

// trim from both ends (copying)
static inline std::string trimmed(std::string s) {
	trim(s);
	return s;
}

vector<vector<string>> Format(vector<string> feildData) {
	vector<vector<string>> formatedData;

	return formatedData;

}

vector<vector<string>> ReadWorldFile(int feild, int date) {
	ifstream myfile;
	myfile.exceptions(ifstream::badbit);
	string path;
	string line;
	vector<vector<vector<float>>> worldList;
	vector<vector<string>> feildData;
	vector<vector<string>> data;
	worldList.resize(300);
	for (int i = 0; i < worldList.size(); i++) {
		worldList.at(i).resize(300);
		for (int j = 0; j < worldList.at(1).size(); j++) {
			//worldList.at(i).resize(15);
		}
	}

	if (2015 >date && date > 2010)
	{
		path = ("World_Factbook/" + to_string(date) + "/rankorder/rawdata_" + to_string(feild) + +".txt");
		try {
			(myfile.open(path));
			getline(myfile, line);
			//getline(myfile, line);
			int pos;
			pos = line.find("\t");
			line.erase(0, pos + 1);
			while (line.find("\t") != -1) {

				string country;
				string value;
				string year;
				/*pos = line.find("\t");
				line.erase(0, pos + 1);*/
				pos = line.find("\t");
				country = line.substr(0, pos);
				line.erase(0, pos + 1);
				pos = line.find("\t");
				value = line.substr(0, pos);
				line.erase(0, pos + 1);
				year = line.substr(0, 5);
				/*myfile >> line;

				myfile >> country;
				myfile >> line;
				myfile >> value;
				myfile >> year;*/
				feildData.push_back({ trimmed(country), onlyNumbers(value) , to_string(date) });
			}
		}
		catch (ifstream::failure e) {
			cout << "Could Not Read File" << endl;
		}
	}
	else if (2011 >date && date > 2008)
	{
		path = ("World_Factbook/" + to_string(date) + "/rankorder/rawdata_" + to_string(feild) + +".text");
		try {
			(myfile.open(path));
			getline(myfile, line);
			//getline(myfile, line);
			int pos;
			pos = line.find("\t");
			line.erase(0, pos + 1);
			while (line.find("\t") != -1) {

				string country;
				string value;
				string year;
				/*pos = line.find("\t");
				line.erase(0, pos + 1);*/
				pos = line.find("\t");
				country = line.substr(0, pos);
				line.erase(0, pos + 1);
				pos = line.find("\t");
				value = line.substr(0, pos);
				line.erase(0, pos + 1);
				year = line.substr(0, 5);
				/*myfile >> line;

				myfile >> country;
				myfile >> line;
				myfile >> value;
				myfile >> year;*/
				feildData.push_back({ trimmed(country), onlyNumbers(value) , to_string(date) });
			}
		}
		catch (ifstream::failure e) {
			cout << "Could Not Read File" << endl;
		}
	}

	else if (date <= 2008) {
		path = ("World_Factbook/" + to_string(date) + "/rankorder/" + to_string(feild) + "rank" + ".txt");

		try {
			(myfile.open(path));
			getline(myfile, line);
			getline(myfile, line);
			while (getline(myfile, line)) {
				int pos;
				string original = line;
				string country;
				string value;
				string year;
				pos = line.find("\t");
				if (pos == -1) {
					break;
				}

				line.erase(0, pos + 1);
				pos = line.find("\t");
				country = line.substr(0, pos);
				line.erase(0, pos + 1);
				pos = line.find("\t");
				value = line.substr(0, pos);
				line.erase(0, pos + 1);
				
				year = line.substr(0, 5);
				// In case there is no provided year
				if (year == " ") {
					year = to_string(99999); // we can't use this data if there is no year
				}
				// In case of October 2005 format
				if (line.length() > 12) {
					year = line.substr(5);
				}
				/*myfile >> line;



				myfile >> country;
				myfile >> line;
				myfile >> value;
				myfile >> year;*/
				feildData.push_back({ trimmed(country), onlyNumbers(value) , onlyNumbers(year)});
			}
		}
		catch (ifstream::failure e) {
			cout << "Could Not Read File" << endl;
		}
	}
	cout << path << endl;




	return feildData;
}

vector <vector<string>> createFeildCodex(int id, int start, int end) {
	vector<vector<string>> codex;
	vector<vector<string>> feildHolder;

	codex.resize(1000);

	for (int i = 0; i <= end - start; i++) {
		feildHolder = ReadWorldFile(id, start + i);
		codex.insert(codex.end(), feildHolder.begin(), feildHolder.end());
		cout << "Before RepetionFilter: " + to_string(codex.size()) << endl;

		sort(codex.begin(), codex.end());
		codex.erase(unique(codex.begin(), codex.end()), codex.end());

		cout << "After RepetionFilter: " + to_string(codex.size()) << endl;
		feildHolder.empty();
	}
	codex.erase(codex.begin());
	return codex;
}

vector <vector<string>> createNonRepeatCodex(int id, int start, int end) {
	vector<string> country_years;
	vector<vector<string>> codex;
	vector<vector<string>> new_codex;
	codex = createFeildCodex(id, start, end);
	for (int i = 0; i < codex.size(); i++) {
		if (country_years.end() == find(country_years.begin(), country_years.end(), codex.at(i).at(0) + codex.at(i).at(2)))
		{
			cout << codex.at(i).at(0) + " " + onlyNumbers(codex.at(i).at(1)) + " " + codex.at(i).at(2) << endl;
			new_codex.push_back(codex.at(i));
			country_years.push_back(codex.at(i).at(0) + codex.at(i).at(2));
		}
	}
	return new_codex;
}

int main()
{
	//Unemployment : 2129
	string plug;

	/*for (int i = 0; i < codex.size(); i++) {
	for (int j = 0; j < codex.at(i).size(); j++) {
	cout << codex.at(i).at(j).at(0) + " " + onlyNumbers(codex.at(i).at(j).at(1)) + " " + codex.at(i).at(j).at(2) << endl << endl;
	}
	}*/
	vector<vector<string>> codex;

	/*for (int i = 0; i < codex.size(); i++) {
	cout << codex.at(i).at(0) + " " + onlyNumbers(codex.at(i).at(1)) + " " + codex.at(i).at(2) << endl << endl;
	}*/
	codex = createNonRepeatCodex(2004, 2004, 2010);
	ofstream output;
	output.open("results.txt");
	for (int i = 0; i < codex.size(); i++) {
		output << " Country Name: " + codex.at(i).at(0) + " ;Value: " + codex.at(i).at(1) + " ;Year: " + codex.at(i).at(2) + "\n";

	}

	//cin >> plug;

	return 0;
}