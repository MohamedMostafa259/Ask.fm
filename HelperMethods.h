#ifndef HELPER_METHODS_H
#define HELPER_METHODS_H

#include <vector>
#include <string>
using namespace std;

namespace DEFAULTS {
	const string DELIMITER{"|"}; // delimiter "|" is less likely to appear in the user's input
	const string ANSWER{"Not Answered Yet"};
	const string QUESTIONS_FILE_NAME{"questions.txt"};
	const string USERS_FILE_NAME{"users.txt"};
}

vector<string> ReadFileLines(const string &path);

void WriteFileLines(const string &path, const vector<string> &lines, bool append = true);

vector<string> SplitString(const string &str, const string &delimiter = DEFAULTS::DELIMITER);

int ReadInt(int low, int high);

int ShowReadMenu(const vector<string> &choices);

#endif