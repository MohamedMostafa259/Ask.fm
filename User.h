#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <sstream>
#include "HelperMethods.h"
using namespace std;

class User {
private:
	int user_id;		// internal system ID
	string user_name;
	string password;
	string name;
	string email;
	bool allow_anonymous_questions;	// 0 or 1
	vector<int> questions_id_from_me;
	map<int, vector<int>> questionID_ThreadIDs; // From question id (question to me) to list of questions IDs on this question (thread questions) - For this user

public:
	User();
	User(const string &line);
	string ToString() const;
	void Print() const;
	void ResetFromQuestions(const vector<int> &from_questions);
	void ResetToQuestions(const vector<pair<int, int>> &to_questions);
	void ReadUser(const string &user_name, int id);
	bool IsAllowAnonymousQuestions() const;
	void SetAllowAnonymousQuestions(bool allowAnonymousQuestions);
	const string& GetEmail() const;
    void SetEmail(const string& email);
    const string& GetName() const;
    void SetName(const string& name);
    const string& GetPassword() const;
    void SetPassword(const string& password);
    int GetUserId() const;
    void SetUserId(int userId);
    const string& GetUserName() const;
    void SetUserName(const string& userName);
    const map<int, vector<int> >& GetQuestionID_ThreadIDs() const;
    const vector<int>& GetQuestionsIdFromMe() const;
};

#endif
