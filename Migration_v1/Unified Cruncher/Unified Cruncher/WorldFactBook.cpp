#include "stdafx.h"


//using namespace std;

//using namespace std;

#include "WorldFactBook.h"

using namespace std;




WorldFactBook::WorldFactBook()
{
}


WorldFactBook::~WorldFactBook()
{
}



vector<vector<string>> WorldFactBook::ReadWorldFile(int feild, int date) {
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
				feildData.push_back({ utility::trimmed(country), utility::onlyNumbers(value) , to_string(date) });
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
				feildData.push_back({ utility::trimmed(country), utility::onlyNumbers(value) , to_string(date) });
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
				feildData.push_back({ utility::trimmed(country), utility::onlyNumbers(value) , utility::onlyNumbers(year) });
			}
		}
		catch (ifstream::failure e) {
			cout << "Could Not Read File" << endl;
		}
	}
	cout << path << endl;




	return feildData;
}

vector<vector<string>> WorldFactBook::createFeildCodex(int id, int start, int end) {
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

vector <vector<string>> WorldFactBook::createNonRepeatCodex(int id, int start, int end) {
	vector<string> country_years;
	vector<vector<string>> codex;
	vector<vector<string>> new_codex;
	codex = createFeildCodex(id, start, end);
	for (int i = 0; i < codex.size(); i++) {
		if (country_years.end() == find(country_years.begin(), country_years.end(), codex.at(i).at(0) + codex.at(i).at(2)))
		{
			cout << codex.at(i).at(0) + " " + utility::onlyNumbers(codex.at(i).at(1)) + " " + codex.at(i).at(2) << endl;
			new_codex.push_back(codex.at(i));
			country_years.push_back(codex.at(i).at(0) + codex.at(i).at(2));
		}
	}
	//this->codex = new_codex;
	return new_codex;
}

void WorldFactBook::printVisual(string file) {
	ofstream output;
	output.open("file");
	for (int i = 0; i < this->codex.size(); i++) {
		output << " Country Name: " + this->codex.at(i).at(0) + " ;Value: " + codex.at(i).at(1) + " ;Year: " + codex.at(i).at(2) + "\n";
	}
}

