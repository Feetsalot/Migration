// Unified Cruncher.cpp : Defines the entry point for the console application.
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
#include "Utility.h"
//using namespace std;
//using namespace utility;
using namespace std;
#include "WorldFactBook.h"
#include "WorldBank.h"
#include "OCED.h"
#include "Formater.h"



int main()
{
	
	string plug;

	vector<vector<string>> codex1;
	vector<vector<string>> codex2;
	vector<vector<string>> codex3;
	vector<Formater::formated_element> final_codex;

	vector<vector<string>> countries;


	codex1 = WorldBank::ReadWorldBankFile("unemploy");
	codex2 = WorldBank::ReadWorldBankFile("GINI");

	WorldBank::writeBankData("results1.txt", codex1);
	WorldBank::writeBankData("results1.txt", codex2);

	final_codex = Formater::FormateFeilds(codex1, codex2);
	Formater::writeFormatedData("formated.txt", final_codex);

    return 0;
}

