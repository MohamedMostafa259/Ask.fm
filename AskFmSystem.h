#ifndef ASK_FM_SYSTEM_H
#define ASK_FM_SYSTEM_H

#include "UsersManager.h"
#include "QuestionsManager.h"

class AskMeSystem {
private:
	UsersManager users_manager;
	QuestionsManager questions_manager;

	void LoadDatabase(bool fill_user_questions = false);
	void ResetCurrentUserQuestions();
public:
	void Run();
};

#endif