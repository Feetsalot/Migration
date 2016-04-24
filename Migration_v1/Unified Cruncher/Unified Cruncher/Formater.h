#pragma once
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
#include "Utility.h"


class Formater
{
public:
	Formater();
	~Formater();

	struct formated_element
	{
		std::string country;
		std::vector<std::vector<std::string>> points;
	};


	static std::vector<Formater::formated_element> FormateFeilds(std::vector<std::vector<std::string>> feild1, std::vector<std::vector<std::string>> feild2);
	static void writeFormatedData(std::string file, std::vector<Formater::formated_element> formated_data);
};

