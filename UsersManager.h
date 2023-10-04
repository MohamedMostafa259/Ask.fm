#ifndef USERS_MANAGER_H
#define USERS_MANAGER_H

#include <iostream>
#include <map>
#include "User.h"
using namespace std;

class UsersManager {
private:
	map<string, User> userName_userObject;
	User current_user;
	int last_id; // for generating IDs
public:
	UsersManager();
	void LoadDatabase();
	void AccessSystem();
	void DoLogin();
	void DoSignUp();
	void ResetFromQuestions(const vector<int> &from_questions);
	void ResetToQuestions(const vector<pair<int, int>> &to_questions);
	void ListUsersNamesIds() const;
	pair<int, int> ReadUserId() const; // return = pair < user_id, allow_anonymous_questions >
	void UpdateDatabase(const User &user);
	const User& GetCurrentUser() const;
};

#endif
