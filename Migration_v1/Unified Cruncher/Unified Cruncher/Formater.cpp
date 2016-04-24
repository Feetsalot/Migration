#include "stdafx.h"

//using namespace std;

//using namespace std;
#include "Formater.h"

//using namespace utility;
using namespace std;


Formater::Formater()
{
	
}


Formater::~Formater()
{
}


 vector<Formater::formated_element> Formater::FormateFeilds(vector<vector<string>> feild1, vector<vector<string>> feild2) {
	vector<vector<string>> country_data1;
	vector<vector<string>> country_data2;

	vector<vector<string>> year_data;


	vector<Formater::formated_element> formated_data;
	// this function needs to take two series of data both in the same {countery,value , year}
	// it will then map the two series of data two each other if they were collected by the same country on the same year
	// the out put will be {country,{data1, data2, year},{data12,data24, year}}
	vector<vector<string>>::iterator c_it1 = feild1.begin();
	vector<vector<string>>::iterator c_it2 = feild2.begin();
	vector<vector<string>>::iterator next_it1 = feild1.begin();
	vector<vector<string>>::iterator next_it2 = feild2.begin();
	string next_country;
	bool notPaired = true;

	while (true) {
		next_it1 = utility::find_next_it(c_it1->at(0), c_it1, feild1.end());

		if (next_it1 == feild1.end()) {
			break;
		}

		c_it2 = utility::find_country_it(c_it1->at(0), c_it2, feild2.end());
		if (c_it2 == feild2.end()) {
			c_it1 = next_it1;
			c_it2 = next_it2;
			continue;
		}

		next_it2 = utility::find_next_it(c_it1->at(0), c_it2, feild2.end());

		country_data1.insert(country_data1.begin(), c_it1, next_it1);
		country_data2.insert(country_data2.begin(), c_it2, next_it2);

		if (country_data1.size() > country_data2.size()) {
			for (int i = 0; i < country_data2.size(); i++) {
				for (vector<vector<string>>::iterator it = country_data1.begin(); it != country_data1.end(); it++) {
					if (it->at(2) == country_data2.at(i).at(2)) {
						year_data.push_back({ it->at(1),country_data2.at(i).at(1),it->at(2) });
						break;
					}
				}
			}
		}
		else {
			for (int i = 0; i < country_data1.size(); i++) {
				for (vector<vector<string>>::iterator it = country_data2.begin(); it != country_data2.end(); it++) {
					if (it->at(2) == country_data1.at(i).at(2)) {
						year_data.push_back({ country_data1.at(i).at(1),country_data2.at(i).at(1),it->at(2) });
					}
				}
			}
		}
		if (!year_data.empty()) {
			formated_data.push_back({ country_data1.at(0).at(0),year_data });
		}
		year_data.clear();
		country_data1.clear();
		country_data2.clear();


		c_it1 = next_it1;
		c_it2 = next_it2;

	}
	//c += next_it - feild1.begin(); // increase c by the indexes traveled

	return formated_data;
}
 void Formater::writeFormatedData(string file,vector<Formater::formated_element> formated_data) {
	 ofstream output;
	 // formated.txt
	 output.open(file);
	 output << "{";
	 for (int i = 0; i < formated_data.size(); i++) {
		 if (i > 0) {
			 output << ",";
		 }
		 output << "{\"" + formated_data.at(i).country + "\""; // {country,
		 for (int j = 0; j < formated_data.at(i).points.size(); j++) {
			 // We want the factor first immigration secound
			 output << ",{" + formated_data.at(i).points.at(j).at(0) + "," + formated_data.at(i).points.at(j).at(1) + "," + formated_data.at(i).points.at(j).at(2) + "}"; // ,{data1,data2,year}
		 }
		 output << "}";
	 }
	 output << "}";
	 output.close();
 }
 