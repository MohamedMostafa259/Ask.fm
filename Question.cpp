#include "Question.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>

Question::Question()  :
			question_id(-1), parent_question_id(-1), from_user_id(-1), to_user_id(-1), is_anonymous_questions(true), answer_text(DEFAULTS::ANSWER) {
	}
Question::Question(const string& line) {
	vector<string> subStrs = SplitString(line);
	assert(subStrs.size() == 7);

	question_id = stoi(subStrs[0]);
	parent_question_id = stoi(subStrs[1]);
	from_user_id = stoi(subStrs[2]);
	to_user_id = stoi(subStrs[3]);
	is_anonymous_questions = stoi(subStrs[4]);
	question_text = subStrs[5];
	answer_text = subStrs[6];
	if (answer_text == "")
		answer_text = DEFAULTS::ANSWER;
}
string Question::ToString() const {
	ostringstream oss;
	oss << question_id << DEFAULTS::DELIMITER << parent_question_id << DEFAULTS::DELIMITER << from_user_id << DEFAULTS::DELIMITER << to_user_id
		<< DEFAULTS::DELIMITER << is_anonymous_questions << DEFAULTS::DELIMITER << question_text << DEFAULTS::DELIMITER << answer_text;

	return oss.str();
}
void Question::PrintToQuestion() const {
	string prefix = "";

	if (parent_question_id != -1)
		prefix = "\tThread: ";

	cout << prefix << "Question Id (" << question_id << ")";
	if (!is_anonymous_questions)
		cout << " from user id(" << from_user_id << ")";
	cout << "\t Question: " << question_text << "\n";

	if (answer_text != DEFAULTS::ANSWER)
		cout << prefix << "\tAnswer: " << answer_text << "\n";
	cout << "\n";
}
void Question::PrintFromQuestion() const {
	cout << "Question Id (" << question_id << ")";
	if (!is_anonymous_questions)
		cout << " !AQ";

	cout << " to user id(" << to_user_id << ")";
	cout << "\t Question: " << question_text;

	if (answer_text != DEFAULTS::ANSWER)
		cout << "\tAnswer: " << answer_text << "\n";
	else
		cout << "\tNOT Answered YET\n";
}
void Question::PrintFeedQuestion() const {
	if (parent_question_id != -1)
		cout << "Thread Parent Question ID (" << parent_question_id << ") ";

	cout << "Question Id (" << question_id << ")";
	if (!is_anonymous_questions)
		cout << " from user id(" << from_user_id << ")";

	cout << " To user id(" << to_user_id << ")";

	cout << "\t Question: " << question_text << "\n";
	if (answer_text != DEFAULTS::ANSWER)
		cout << "\tAnswer: " << answer_text << "\n";
}
const string &Question::GetAnswerText() const {
    return answer_text;
}
void Question::SetAnswerText(const string &answerText) {
    answer_text = answerText;
}
int Question::GetFromUserId() const {
	return from_user_id;
}
void Question::SetFromUserId(int fromUserId) {
	from_user_id = fromUserId;
}
bool Question::GetIsAnonymousQuestions() const {
	return is_anonymous_questions;
}
void Question::SetIsAnonymousQuestions(bool isAnonymousQuestions) {
	is_anonymous_questions = isAnonymousQuestions;
}
int Question::GetParentQuestionId() const {
	return parent_question_id;
}
void Question::SetParentQuestionId(int parentQuestionId) {
	parent_question_id = parentQuestionId;
}
int Question::GetQuestionId() const {
	return question_id;
}
void Question::SetQuestionId(int questionId) {
	question_id = questionId;
}
const string &Question::GetQuestionText() const {
	return question_text;
}
void Question::SetQuestionText(const string& questionText) {
	question_text = questionText;
}
int Question::GetToUserId() const {
	return to_user_id;
}
void Question::SetToUserId(int toUserId) {
	to_user_id = toUserId;
}