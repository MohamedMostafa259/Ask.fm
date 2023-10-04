#ifndef QUESTION_H
#define QUESTION_H

#include "HelperMethods.h"
#include <string>
using namespace std;

class Question {
private:
	int question_id;
	// To support the thread. Each question look at a parent's question
	// -1 No parent (first question in the thread)
	int parent_question_id;
	int from_user_id;
	int to_user_id;
	bool is_anonymous_questions;	// 0 or 1
	string question_text;
	string answer_text;

public:
	Question();
	Question(const string &line); // How many constructor arguments is too many? => https://stackoverflow.com/questions/40264/how-many-conclassor-arguments-is-too-many
	string ToString() const;
	void PrintToQuestion() const;
	void PrintFromQuestion() const;
	void PrintFeedQuestion() const;
	const string& GetAnswerText() const;
	void SetAnswerText(const string& answerText);
	int GetFromUserId() const;
	void SetFromUserId(int fromUserId);
	bool GetIsAnonymousQuestions() const;
	void SetIsAnonymousQuestions(bool isAnonymousQuestions);
	int GetParentQuestionId() const;
	void SetParentQuestionId(int parentQuestionId);
	int GetQuestionId() const;
	void SetQuestionId(int questionId);
	const string& GetQuestionText() const;
	void SetQuestionText(const string& questionText);
	int GetToUserId() const;
	void SetToUserId(int toUserId);
};

#endif
