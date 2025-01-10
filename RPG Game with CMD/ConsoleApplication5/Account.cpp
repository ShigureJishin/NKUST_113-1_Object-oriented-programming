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
            encrypted_password += c; // �p�G���O�r���A�h�O������
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
            decrypted_password += c; // �D�r���r���O������
        }
    }
    return decrypted_password;
}

CFighter* Account::addCharacter(string inName, string inProfession) {
    for (const CFighter* fighter : characters) {
        if (((CLifeEntity*)fighter)->getname() == inName) {
            cout << "�P�ӱb�����U������W�٭��ơC" << endl;
            return nullptr; // ���J���ѡA��ܦW�٤w�s�b
        }
    }

    if (characters.size() >= 3) {
        cout << "����ƶq�w�F�W�� (3��)�C" << std::endl;
        return nullptr; // �w�F�W��
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
        cout << "�L�Ī�¾�~�W�١G" << inProfession << std::endl;
        return nullptr; // �L�Ī�¾�~�W��
    }

    CFighter* newFighter = new CFighter(inName, 0, 0, 0, 0, 0, 1, profession); // �I�s�D�n�غc�l�A�ô��ѹw�]��
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
        cout << "�L�i�Ψ���A�Х��Ыب���C" << endl;
        return nullptr;
    }

    cout << "�i�Ψ���C��G" << endl;
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i]->getname() << " Lv" << characters[i]->getLevel() << " " << characters[i]->getProfession_String() << endl;
    }

    size_t choice;
    cout << "�п�ܨ���s���G";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "�L�Ŀ�J�A�п�J�Ʀr�C" << endl;
        return nullptr;
    }

    if (choice == 0 || choice > characters.size()) {
        cout << "�L�Ī���ܡC" << endl;
        return nullptr;
    }

    return characters[choice - 1];
}

bool Account::deleteCharacter() {
    if (characters.empty()) {
        cout << "�L����i�R���C" << endl;
        return false;
    }

    cout << "�i�R������C��G" << endl;
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ". " << characters[i]->getname() << endl;
    }

    size_t choice;
    cout << "�п�ܭn�R��������s���G";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "�L�Ŀ�J�A�п�J�Ʀr�C" << endl;
        return false;
    }

    if (choice == 0 || choice > characters.size()) {
        cout << "�L�Ī���ܡC" << endl;
        return false;
    }

    delete characters[choice - 1]; // ����O����
    characters.erase(characters.begin() + (choice - 1)); // �q�C����
    CGlobalInfo::accountManager->saveToFile();

    return true;
}