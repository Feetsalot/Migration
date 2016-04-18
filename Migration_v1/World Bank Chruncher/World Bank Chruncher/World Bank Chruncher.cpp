// World Bank Chruncher.cpp : Defines the entry point for the console application.
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



vector<vector<string>> ReadWorldFile(string feild) {
	ifstream myfile;
	myfile.exceptions(ifstream::badbit);
	string path;
	string line;
	vector<vector<string>> feildData;
	

	
		path = ("World_Bank/" + feild + ".txt");

		try {
			(myfile.open(path));
			getline(myfile, line);
			while (getline(myfile, line)) {
				if (line == " ") {
					break;
				}
				// every line is a country of a certian year for the feild of the file
				int pos;
				string country;
				string value;
				vector<string> years;
				years.insert(years.begin(),{ "1990", "2000", "2006", "2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015" });
				pos = line.find("\t");
				
				// the country name is after the second tab
				line.erase(0, pos + 1);
				pos = line.find("\t");
				line.erase(0, pos + 1);
				pos = line.find("\t");
				country = line.substr(0, pos);
				line.erase(0, pos + 1);
				
				// A data Value for ever year from this point.
				// years: 1990, 2000, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015
				pos = line.find("\t");
				line.erase(0, pos + 1);
				for (int i = 0; i < years.size(); i++) {
					// this is too erase the country code
					

					pos = line.find("\t");
					if (pos == -1) {
						// the end of the line is hit.
						continue;
					}

					
					
					value = line.substr(0, pos);// example value : 45.06
					line.erase(0, pos + 1);
					if (onlyNumbers(value) == ".." || onlyNumbers(value) == "") { // When there is no value the value is ..
						continue;
					}
					
					feildData.push_back({ trimmed(country), onlyNumbers(value),years[i] });
				}
			}
		}
		catch (ifstream::failure e) {
			cout << "Could Not Read File" << endl;
		}
	cout << path << endl;

	return feildData;
}


int main()
{
	string plug;

	vector<vector<string>> codex1;
	vector<vector<string>> codex2;


	codex1 = ReadWorldFile("GINI");
	codex2 = ReadWorldFile("Poor_Growth");

	ofstream output;
	output.open("results.txt");
	for (int i = 0; i < codex1.size(); i++) {
		output << " Country Name: " + codex1.at(i).at(0) + " ;Value: " + codex1.at(i).at(1) + " ;Year: " + codex1.at(i).at(2) + "\n";

	}
	output.close();
	output.open("results2.txt");
	for (int i = 0; i < codex2.size(); i++) {
		output << " Country Name: " + codex2.at(i).at(0) + " ;Value: " + codex2.at(i).at(1) + " ;Year: " + codex2.at(i).at(2) + "\n";

	}

	//cin >> plug;

	return 0;
}