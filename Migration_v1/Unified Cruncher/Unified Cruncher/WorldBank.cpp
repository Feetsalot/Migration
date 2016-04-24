#include "stdafx.h"

//using namespace std;

//using namespace std;

#include "WorldBank.h"
using namespace std;

WorldBank::WorldBank()
{
}


WorldBank::~WorldBank()
{
}

vector<vector<string>> WorldBank::ReadWorldBankFile(string feild) {
	ifstream myfile;
	myfile.exceptions(ifstream::badbit);
	string path;
	string line;
	vector<vector<string>> feildData;



	path = ("World_Bank/" + feild + ".txt");

	try {
		(myfile.open(path));
		getline(myfile, line);
		vector<string> years;
		while (line.find("YR") != -1) {
			years.push_back(line.substr(line.find("YR") + 2, 4));
			line.erase(0, line.find("YR") + 6);
		}

		while (getline(myfile, line)) {
			if (line == " ") {
				break;
			}
			// every line is a country of a certian year for the feild of the file
			int pos;
			string country;
			string value;

			pos = line.find("\t");

			// the country name is right before the first tab

			country = line.substr(0, pos);
			line.erase(0, pos + 1);

			country = utility::remove_char(country, '"');

			// A data Value for ever year from this point.
			// years: 1990, 2000, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015
			pos = line.find("\t");
			line.erase(0, pos + 1);
			pos = line.find("\t");
			line.erase(0, pos + 1);
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
				if (utility::onlyNumbers(value) == ".." || utility::onlyNumbers(value) == "") { // When there is no value the value is ..
					continue;
				}

				feildData.push_back({ utility::trimmed(country), utility::onlyNumbers(value),years[i] });
			}
		}
	}
	catch (ifstream::failure e) {
		cout << "Could Not Read File" << endl;
	}
	cout << path << endl;

	return feildData;
}
void WorldBank::writeBankData(string file, vector<vector<string>> codex) {
	ofstream output;
	output.open(file);
	for (int i = 0; i < codex.size(); i++) {
		output << " Country Name: " + codex.at(i).at(0) + " ;Value: " + codex.at(i).at(1) + " ;Year: " + codex.at(i).at(2) + "\n";
		cout << " Country Name: " + codex.at(i).at(0) + " ;Value: " + codex.at(i).at(1) + " ;Year: " + codex.at(i).at(2) + "\n";

	}
	output.close();
}
