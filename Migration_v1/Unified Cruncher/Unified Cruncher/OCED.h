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
class OCED
{
public:
	OCED();
	~OCED();

	std::vector<std::vector<std::string>>ReadOCEDFile(std::string file);
};

