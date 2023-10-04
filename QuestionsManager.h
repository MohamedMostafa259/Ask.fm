#ifndef QUESTIONS_MANAGER_H
#define QUESTIONS_MANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "User.h"
#include "Question.h"
using namespace std;

class QuestionsManager {
private:
	map<int, vector<int>> questionID_ThreadIDs; // From question id (question to a user) to list of questions IDS on this question (thread questions) - All users
	map<int, Question> questionID_questionObject; // Map the question id to question object
	int last_id; // for generating IDs
public:
	QuestionsManager();
	void LoadDatabase();
	vector<int> GetUserFromQuestions(const User &user) const;
	vector<pair<int, int>> GetUserToQuestions(const User &user) const;
	void PrintUserToQuestions(const User &user) const;
	void PrintUserFromQuestions(const User &user) const;
	// Used in answering and deleting a question for YOU.
	int ReadQuestionId_ans_del(const User &user) const;
	// Used in asking a question
	int ReadQuestionId_ask(const User &user) const;
	void AnswerQuestion(const User &user);
	void DeleteQuestion(const User &user);
	void AskQuestion(const User &user, const pair<int, int> &to_user_pair); // to_user_pair = pair < user_id, allow_anonymous_questions >
	void ListFeed() const;
	void UpdateDatabase();
};

#endif
