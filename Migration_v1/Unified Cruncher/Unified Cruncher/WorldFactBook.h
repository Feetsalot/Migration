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

class WorldFactBook
{
public:
	WorldFactBook();
	~WorldFactBook();

	std::vector < std::vector < std::string >> codex;

	static std::vector<std::vector<std::string>> ReadWorldFile(int id, int date);

	static std::vector <std::vector<std::string>> createFeildCodex(int id, int start, int end);

	static std::vector <std::vector<std::string>> createNonRepeatCodex(int id, int start, int end);

	void printVisual(std::string file);

};

