#include "UsersManager.h"

UsersManager::UsersManager() {
    last_id = 0;
}
void UsersManager::LoadDatabase() {
    last_id = 0;
    userName_userObject.clear();

    vector<string> lines = ReadFileLines(DEFAULTS::USERS_FILE_NAME);
    for (const auto &line : lines) {
        User user(line);
        userName_userObject[user.GetUserName()] = user;
        last_id = max(last_id, user.GetUserId());
    }
}
void UsersManager::AccessSystem() {
    int choice = ShowReadMenu( { "Login", "Sign Up" });
    if (choice == 1)
        DoLogin();
    else
        DoSignUp();
}
void UsersManager::DoLogin() {
    LoadDatabase();	// in case user added from other parallel run

    while (true) {
        string name, pass;
        cout << "Enter user name & password: ";
        cin >> name >> pass;
        current_user.SetUserName(name);
        current_user.SetPassword(pass);

        if (!userName_userObject.count(current_user.GetUserName())) {/* actually, this error message will occur if a user name is invalid only NOT user name
                                                                        or password, but we wrote "user name or password" for making our system more secure */
            cout << "\nInvalid user name or password. Try again\n\n";
            continue;
        }
        const User& user_exist = userName_userObject[current_user.GetUserName()];

        if (current_user.GetPassword() != user_exist.GetPassword()) {
            cout << "\nInvalid user name or password. Try again\n\n";
            continue;
        }
        current_user = user_exist;
        break;
    }
}
void UsersManager::DoSignUp() {
    string user_name;
    while (true) {
        cout << "Enter user name. (No spaces): ";
        cin >> user_name;

        if (userName_userObject.count(user_name))
            cout << "Already used. Try again\n";
        else
            break;
    }
    LoadDatabase(); // for handling this case: if two or more parallel sessions signed up, They wouldn't be given same id.
    current_user.ReadUser(user_name, ++last_id);
    userName_userObject[current_user.GetUserName()] = current_user;

    UpdateDatabase(current_user);
}
void UsersManager::ResetFromQuestions(const vector<int> &from_questions) {
    current_user.ResetFromQuestions(from_questions);
}
void UsersManager::ResetToQuestions(const vector<pair<int, int>> &to_questions) {
    current_user.ResetToQuestions(to_questions);
}
void UsersManager::ListUsersNamesIds() const {
    for (const auto &pair : userName_userObject)
        cout << "ID: " << pair.second.GetUserId() << "\t\tName: " << pair.second.GetName() << "\n";
}
pair<int, int> UsersManager::ReadUserId() const {
    int user_id;
    cout << "Enter User id or -1 to cancel: ";
    cin >> user_id;

    if (user_id == -1)
        return make_pair(-1, -1);

    for (const auto &pair : userName_userObject) {
        if (pair.second.GetUserId() == user_id)
            return make_pair(user_id, pair.second.IsAllowAnonymousQuestions());
    }

    cout << "Invalid User ID. Try again\n";
    return ReadUserId();
}
void UsersManager::UpdateDatabase(const User &user) {
    string line = user.ToString();
    vector<string> lines(1, line);
    WriteFileLines(DEFAULTS::USERS_FILE_NAME, lines);
}
const User &UsersManager::GetCurrentUser() const {
    return current_user;
}