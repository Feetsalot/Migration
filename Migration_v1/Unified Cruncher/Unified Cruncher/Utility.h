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
class utility
{
public:
	utility() {};

	//using namespace std;

	static std::vector<std::vector<std::string>>::iterator find_next_it(std::string country, std::vector<std::vector<std::string>>::iterator start, std::vector<std::vector<std::string>>::iterator end) {
		std::vector<std::vector<std::string>>::iterator it;
		std::vector<std::vector<std::string>>::iterator found_it;
		bool isFound = false;
		for (it = start; it != end; it++) {
			if (find(it->begin(), it->end(), country) == it->end()) { // it does not see the current country
				found_it = it;
				isFound = true;
				break;
			}

		}
		if (isFound) {
			return found_it;
		}
		else {
			return end;
		}
	}
	
	static std::vector<std::vector<std::string>>::iterator find_country_it(std::string country, std::vector<std::vector<std::string>>::iterator start, std::vector<std::vector<std::string>>::iterator end) {
		std::vector<std::vector<std::string>>::iterator it;
		std::vector<std::vector<std::string>>::iterator found_it;
		bool isFound = false;
		for (it = start; it != end; it++) {

			if (find(it->begin(), it->end(), country) != it->end()) { // it does not see the current country
				found_it = it;
				isFound = true;
				break;
			}
		}
		if (isFound) {
			return found_it;
		}
		else {
			return end;
		}
	}

	static bool predicate(char c) {
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

	static std::string remove_char(std::string str, char ch)
	{
		// remove all occurrences of char ch from str
		str.erase(std::remove(str.begin(), str.end(), ch), str.end());
		return str;
	}

	static std::string onlyNumbers(std::string s) {
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


};

