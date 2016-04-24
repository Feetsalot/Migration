#include "stdafx.h"

//using namespace std;

//using namespace std;

#include "OCED.h"

using namespace std;

OCED::OCED()
{
}


OCED::~OCED()
{
}

vector<vector<string>> OCED::ReadOCEDFile(string file) {
	ifstream myfile;
	myfile.exceptions(ifstream::badbit);
	string path;
	string line;
	vector<vector<string>> feildData;


	//OCED.csv
	path = (file);

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
			string secondCountry;
			string value;
			string year;
			string feild;

			pos = line.find("\t");
			country = line.substr(0, pos);
			line.erase(0, pos + 1);

			pos = line.find("\t");
			feild = line.substr(0, pos);
			line.erase(0, pos + 1);

			pos = line.find("\t");
			line.erase(0, pos + 1);

			pos = line.find("\t");
			secondCountry = line.substr(0, pos + 1);
			line.erase(0, pos + 1);

			pos = line.find("\t");
			year = line.substr(0, pos + 1);
			line.erase(0, pos + 1);

			pos = line.find("\t");
			value = line.substr(0, pos + 1);
			line.erase(0, pos + 1);

			if (pos == -1) {
				// the end of the line is hit.
				continue;
			}

			feildData.push_back({ utility::trimmed(utility::remove_char(feild,'\"')),utility::trimmed(utility::remove_char(country,'\"')), utility::trimmed(utility::remove_char(secondCountry,'\"')),utility::onlyNumbers(value),utility::onlyNumbers(year) });
		}
	}
	catch (ifstream::failure e) {
		cout << "Could Not Read File" << endl;
	}
	cout << path << endl;

	return feildData;
}