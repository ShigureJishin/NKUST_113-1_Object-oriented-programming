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

/*�n�J�P�n�X�]3%�^
���\��Ϫ��a����Q�ά۹������b���]Username�^�αK�X
�]Password�^�ӵn�J�C
�ѰO�K�X�]2%�^
���a�ѰO�K�X�ɡA�i�ϥ�admin�b���ӭ��]�K�X�]�ݿ�
�J�⦸�s�K�X�^�C

1.admin�b�� (present in program)
2.player�b��(in config.txt) */

// �b���޲z���O
class CAccountManager {
public:
    CAccountManager();
    void login(const vector<string>& tokens);
    void logout(const vector<string>& tokens);
    void list(const vector<string>& tokens);
    void changePassword(const vector<string>& tokens);

private:
    map<string, string> accounts;  // �x�s�b���M�K�X
    string currentUser;            // ������e�n�J���ϥΪ�
};

// �c�y�禡
CAccountManager::CAccountManager() {
    // �w�]�b�����
    accounts["admin"] = "admin123";
    accounts["user1"] = "password1";
    accounts["user2"] = "password2";
}

// �n�J�\��
void CAccountManager::login() {
    vector<string> tokens;
    getline(cin, tokens, '\n');
    
    if (tokens.size() != 2) {
        cout << "�ϥΤ覡: <�b��> <�K�X>" << endl;
        return;
    }

    string username = tokens[0];
    string password = tokens[1];

    if (accounts.find(username) != accounts.end() && accounts[username] == password) {
        currentUser = username;
        cout << "�n�J���\�I�w�� " << username << endl;
    }
    else {
        cout << "�b���αK�X���~�C" << endl;
    }
}

// �n�X�\��
void CAccountManager::logout(const vector<string>& tokens) {
    if (currentUser.empty()) {
        cout << "�|���n�J�C" << endl;
    }
    else {
        cout << "�ϥΪ� " << currentUser << " �w�n�X�C" << endl;
        currentUser.clear();
    }
}

// �C�X�Ҧ��b��
void CAccountManager::list(const vector<string>& tokens) {
    if (currentUser != "admin") {
        cout << "�u���޲z���i�H�˵��b���M��C" << endl;
        return;
    }

    cout << "�b���M��:" << endl;
    for (const auto& pair : accounts) {
        cout << "- " << pair.first << endl;
    }
}

// �ק�K�X
void CAccountManager::changePassword(const vector<string>& tokens) {
    if (tokens.size() != 3) {
        cout << "�ϥΤ覡: changepassword <�b��> <�s�K�X>" << endl;
        return;
    }

    string username = tokens[1];
    string newPassword = tokens[2];

    if (accounts.find(username) != accounts.end()) {
        accounts[username] = newPassword;
        cout << "�b�� " << username << " �K�X�w�ק�C" << endl;
    }
    else {
        cout << "�b�����s�b�C" << endl;
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