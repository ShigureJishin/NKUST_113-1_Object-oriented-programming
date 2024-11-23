#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <map>
#include <cassert>
//#include <windows.h>
#include "GlobalInfo.h"
#include "CmdParser.h"

using namespace std;

/*登入與登出（3%）
此功能使玩家能夠利用相對應的帳號（Username）及密碼
（Password）來登入。
忘記密碼（2%）
當玩家忘記密碼時，可使用admin帳號來重設密碼（需輸
入兩次新密碼）。

1.admin帳號 (present in program)
2.player帳號(in config.txt) */

// 帳號管理類別
class CAccountManager {
public:
    CAccountManager();
    void login(const vector<string>& tokens);
    void logout(const vector<string>& tokens);
    void list(const vector<string>& tokens);
    void changePassword(const vector<string>& tokens);

private:
    map<string, string> accounts;  // 儲存帳號和密碼
    string currentUser;            // 紀錄當前登入的使用者
};

// 構造函式
CAccountManager::CAccountManager() {
    // 預設帳號資料
    accounts["admin"] = "admin123";
    accounts["user1"] = "password1";
    accounts["user2"] = "password2";
}

// 登入功能
void CAccountManager::login() {
    vector<string> tokens;
    getline(cin, tokens, '\n');
    
    if (tokens.size() != 2) {
        cout << "使用方式: <帳號> <密碼>" << endl;
        return;
    }

    string username = tokens[0];
    string password = tokens[1];

    if (accounts.find(username) != accounts.end() && accounts[username] == password) {
        currentUser = username;
        cout << "登入成功！歡迎 " << username << endl;
    }
    else {
        cout << "帳號或密碼錯誤。" << endl;
    }
}

// 登出功能
void CAccountManager::logout(const vector<string>& tokens) {
    if (currentUser.empty()) {
        cout << "尚未登入。" << endl;
    }
    else {
        cout << "使用者 " << currentUser << " 已登出。" << endl;
        currentUser.clear();
    }
}

// 列出所有帳號
void CAccountManager::list(const vector<string>& tokens) {
    if (currentUser != "admin") {
        cout << "只有管理員可以檢視帳號清單。" << endl;
        return;
    }

    cout << "帳號清單:" << endl;
    for (const auto& pair : accounts) {
        cout << "- " << pair.first << endl;
    }
}

// 修改密碼
void CAccountManager::changePassword(const vector<string>& tokens) {
    if (tokens.size() != 3) {
        cout << "使用方式: changepassword <帳號> <新密碼>" << endl;
        return;
    }

    string username = tokens[1];
    string newPassword = tokens[2];

    if (accounts.find(username) != accounts.end()) {
        accounts[username] = newPassword;
        cout << "帳號 " << username << " 密碼已修改。" << endl;
    }
    else {
        cout << "帳號不存在。" << endl;
    }
}

CAccountManager* ptr = new CAccountManager;
CCmdParser *CGlobalInfo::parser = new CCmdParser;

int main() {
    ptr->login();
    while (CGlobalInfo::parser->query () >= 0){

    }

    system("pause");
    return 0;
}