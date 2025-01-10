#include <iostream>
#include <sstream>
#include <fstream>

#include "Account.h"
#include "AccountData.h"
#include "GlobalInfo.h"
#include "def.h"

using namespace std;

void Account::setPassword(string inPassword) {
    password = Encrypt(inPassword);
}

string Account::Encrypt(string inPassword) const{
    string encrypted_password = "";

    for (size_t i = 0; i < inPassword.length(); ++i) {
        char c = inPassword[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            encrypted_password += (c - base + 3) % 26 + base;
        }
        else {
            encrypted_password += c; // 如果不是字母，則保持不變
        }
    }

    return encrypted_password;
}

string Account::Decrypt(string inPassword) const {
    string decrypted_password = "";

    for (size_t i = 0; i < inPassword.length(); ++i) {
        char c = inPassword[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            decrypted_password += (c - base - 3 + 26) % 26 + base;
        }
        else {
            decrypted_password += c; // 非字母字元保持不變
        }
    }
    return decrypted_password;
}

CFighter* Account::addCharacter(string inName, string inProfession) {
    for (const CFighter* fighter : characters) {
        if (((CLifeEntity*)fighter)->getname() == inName) {
            cout << "與該帳號底下的角色名稱重複。" << endl;
            return nullptr; // 插入失敗，表示名稱已存在
        }
    }

    if (characters.size() >= 3) {
        cout << "角色數量已達上限 (3個)。" << std::endl;
        return nullptr; // 已達上限
    }

    Profession profession;
    if (inProfession == "Berserker") {
        profession = Profession::Berserker;
    }
    else if (inProfession == "Mage") {
        profession = Profession::Mage;
    }
    else if (inProfession == "Tank") {
        profession = Profession::Tank;
    }
    else {
        cout << "無效的職業名稱：" << inProfession << std::endl;
        return nullptr; // 無效的職業名稱
    }

    CFighter* newFighter = new CFighter(inName, 0, 0, 0, 0, 0, 1, profession); // 呼叫主要建構子，並提供預設值
    characters.push_back(newFighter);
    CGlobalInfo::accountManager->saveToFile();

#if 0
    vector<CFighter *>::iterator it;
    for (it = characters.begin(); it != characters.end(); it++) {
        cout << "Test: " << (*it)->getname() << endl;
    }
#endif

    return newFighter;
}

CFighter* Account::selectCharacter() {
    if (characters.empty()) {
        cout << "無可用角色，請先創建角色。" << endl;
        return nullptr;
    }

    cout << "可用角色列表：" << endl;
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i]->getname() << " Lv" << characters[i]->getLevel() << " " << characters[i]->getProfession_String() << endl;
    }

    size_t choice;
    cout << "請選擇角色編號：";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "無效輸入，請輸入數字。" << endl;
        return nullptr;
    }

    if (choice == 0 || choice > characters.size()) {
        cout << "無效的選擇。" << endl;
        return nullptr;
    }

    return characters[choice - 1];
}

bool Account::deleteCharacter() {
    if (characters.empty()) {
        cout << "無角色可刪除。" << endl;
        return false;
    }

    cout << "可刪除角色列表：" << endl;
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i]->getname() << endl;
    }

    size_t choice;
    cout << "請選擇要刪除的角色編號：";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "無效輸入，請輸入數字。" << endl;
        return false;
    }

    if (choice == 0 || choice > characters.size()) {
        cout << "無效的選擇。" << endl;
        return false;
    }

    delete characters[choice - 1]; // 釋放記憶體
    characters.erase(characters.begin() + (choice - 1)); // 從列表移除
    CGlobalInfo::accountManager->saveToFile();

    return true;
}