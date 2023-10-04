#include "QuestionsManager.h"

QuestionsManager::QuestionsManager() : last_id{0} { }

void QuestionsManager::LoadDatabase() {
    last_id = 0;
    questionID_ThreadIDs.clear();
    questionID_questionObject.clear();

    vector<string> lines = ReadFileLines(DEFAULTS::QUESTIONS_FILE_NAME);
    for (const auto &line : lines) {
        Question question(line);
        last_id = max(last_id, question.GetQuestionId());

        questionID_questionObject[question.GetQuestionId()] = question;

        if (question.GetParentQuestionId() == -1)
            questionID_ThreadIDs[question.GetQuestionId()].push_back(question.GetQuestionId());
        else
            questionID_ThreadIDs[question.GetParentQuestionId()].push_back(question.GetQuestionId());
    }
}
vector<int> QuestionsManager::GetUserFromQuestions(const User &user) const {
    vector<int> question_ids;

    for (const auto &pair : questionID_ThreadIDs) {	
        for (const auto &question_id : pair.second) {

            const Question &question = questionID_questionObject.find(question_id)->second;

            if (question.GetFromUserId() == user.GetUserId())
                question_ids.push_back(question.GetQuestionId());
        }
    }
    return question_ids;
}
vector<pair<int, int>> QuestionsManager::GetUserToQuestions(const User &user) const {
    vector<pair<int, int>> question_ids;

    for (const auto &pair : questionID_ThreadIDs) {
        for (const auto &question_id : pair.second) {
            
            const Question &question = questionID_questionObject.find(question_id)->second;

            if (question.GetToUserId() == user.GetUserId()) {
                if (question.GetParentQuestionId() == -1)
                    question_ids.push_back(make_pair(question.GetQuestionId(), question.GetQuestionId()));
                else
                    question_ids.push_back(make_pair(question.GetParentQuestionId(), question.GetQuestionId()));
            }
        }
    }
    return question_ids;
}
void QuestionsManager::PrintUserToQuestions(const User &user) const {
    cout << "\n";

    if (user.GetQuestionID_ThreadIDs().size() == 0)
        cout << "No Questions";

    for (const auto &pair : user.GetQuestionID_ThreadIDs()) {		
        for (const auto &question_id : pair.second) {

            // Accessing questionID_questionObject[] change the map by adding if not exist. You can't use in const function
            // Here we just find, which return iterator (second is like a pointer to object)
            const Question &question = questionID_questionObject.find(question_id)->second;
            question.PrintToQuestion();
        }
    }
    cout << "\n";
}
void QuestionsManager::PrintUserFromQuestions(const User &user) const {
    cout << "\n";
    if (user.GetQuestionsIdFromMe().size() == 0)
        cout << "No Questions";

    for (const auto &question_id : user.GetQuestionsIdFromMe()) {
        const Question &question = questionID_questionObject.find(question_id)->second;
        question.PrintFromQuestion();
    }
    cout << "\n";
}
int QuestionsManager::ReadQuestionId_ans_del(const User &user) const {
    int question_id;
    cout << "Enter Question id or -1 to cancel: ";
    cin >> question_id;

    if (question_id == -1)
        return -1;
    
    auto it{questionID_questionObject.find(question_id)};
    if (it == questionID_questionObject.end()) { // Not Exist
        cout << "\nERROR: No question with such ID. Try again\n\n";
        return ReadQuestionId_ans_del(user);
    }
    // const Question &question = questionID_questionObject[question_id]; // Compilation Error => because of Accessing questionID_questionObject[]
                                                                                // change the map by adding if not exist. You can't use in const function 
    // Here we just find, which return iterator (second is like a pointer to object)
    const Question &question = questionID_questionObject.find(question_id)->second;

    if (question.GetToUserId() != user.GetUserId()) {
        cout << "\nERROR: Invalid question ID. Try again\n\n";
        return ReadQuestionId_ans_del(user);
    }
    return question_id;
}
int QuestionsManager::ReadQuestionId_ask(const User &user) const {
    int question_id;
    cout << "For thread question: Enter Question id or -1 for new question: ";
    cin >> question_id;

    if (question_id == -1)
        return -1;

    auto it{questionID_questionObject.find(question_id)};
    if (it == questionID_questionObject.end()) { // Not Exist
        cout << "\nERROR: No question with such ID. Try again\n\n";
        return ReadQuestionId_ask(user);
    }
    return question_id;
}
void QuestionsManager::AnswerQuestion(const User &user) {
    int question_id = ReadQuestionId_ans_del(user);

    if (question_id == -1)
        return;

    Question &question = questionID_questionObject.find(question_id)->second;

    question.PrintToQuestion();

    if (question.GetAnswerText() != DEFAULTS::ANSWER)
        cout << "\nWarning: Already answered. Answer will be updated\n";

    cout << "Enter answer: ";
    string line;
    cin.ignore(1, '\n'); // read last enter '\n'
    getline(cin, line);
    question.SetAnswerText(line);
}
void QuestionsManager::DeleteQuestion(const User &user) {
    int question_id = ReadQuestionId_ans_del(user);

    if (question_id == -1)
        return;

    vector<int> ids_to_remove;	// to remove from questionID_questionObject

    // Let's see if thread or not. If thread, remove all of it
    if (questionID_ThreadIDs.count(question_id)) { // thread
        ids_to_remove = questionID_ThreadIDs[question_id];
        questionID_ThreadIDs.erase(question_id);
    } else {
        ids_to_remove.push_back(question_id);

        // let's find in which thread to remove. Consistency is important when have multi-view ↓↓
        for (auto &pair : questionID_ThreadIDs) { // (multi-view means that the same data exists in more than a data structure)
            vector<int> &vec = pair.second;
            bool found = false;
            for (int pos = 0; pos < (int) vec.size(); ++pos) {
                if (question_id == vec[pos]) {
                    vec.erase(vec.begin() + pos);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
    }
    for (const auto &id : ids_to_remove)
        questionID_questionObject.erase(id);
}
void QuestionsManager::AskQuestion(const User &user, const pair<int, int> &to_user_pair) { 
    Question question;

    if (!to_user_pair.second) {
        cout << "Note: Anonymous questions are not allowed for this user\n";
        question.SetIsAnonymousQuestions(0);
    } else {
        cout << "Is anonymous questions?: (0 or 1): ";
        int st;
        cin >> st;
        question.SetIsAnonymousQuestions(st);
    }

    question.SetParentQuestionId(ReadQuestionId_ask(user));

    cout << "Enter question text: ";
    string line;
    cin.ignore(1, '\n'); // read last enter '\n'
    getline(cin, line);
    question.SetQuestionText(line);

    question.SetFromUserId(user.GetUserId());
    question.SetToUserId(to_user_pair.first);
    LoadDatabase(); // for handling this case: if two or more parallel sessions asked questions, They wouldn't be given same id.
    
    question.SetQuestionId(++last_id);

    questionID_questionObject[question.GetQuestionId()] = question;

    if (question.GetParentQuestionId() == -1)
        questionID_ThreadIDs[question.GetQuestionId()].push_back(question.GetQuestionId());
    else
        questionID_ThreadIDs[question.GetParentQuestionId()].push_back(question.GetQuestionId());
}
void QuestionsManager::ListFeed() const {
    for (const auto &pair : questionID_questionObject) {
        const Question &question = pair.second;

        if (question.GetAnswerText() == DEFAULTS::ANSWER)
            continue;
        question.PrintFeedQuestion();
    }
}
void QuestionsManager::UpdateDatabase()
{
    vector<string> lines;

    for (const auto &pair : questionID_questionObject)
        lines.push_back(pair.second.ToString());

    WriteFileLines(DEFAULTS::QUESTIONS_FILE_NAME, lines, false);
}