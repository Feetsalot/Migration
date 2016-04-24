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
class WorldBank
{
public:
	WorldBank();
	~WorldBank();

	static std::vector<std::vector<std::string>> ReadWorldBankFile(std::string feild);

	static void WorldBank::writeBankData(std::string file, std::vector<std::vector<std::string>> codex);
};

