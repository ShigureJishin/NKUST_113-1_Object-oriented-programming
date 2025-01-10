#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

#include "Fighter.h"
using namespace std;

class Account {
public:
    Account(string inUsername ="", string inPassword="", bool isAdmin = false)
        : username(inUsername), password(inPassword), admin(isAdmin) {
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    void setPassword(string inPassword);
    string Encrypt(string inPassword) const;
    string Decrypt(string inPassword) const;
    bool validatePassword(const string& inPassword) const { return Decrypt(password) == inPassword; }
    bool isAdmin() const { return admin; }
    /* 角色 */
    void loadCharacter(CFighter* inFighter) { characters.push_back(inFighter); };
    CFighter* addCharacter(string name, string profession);
    CFighter* selectCharacter();
    bool deleteCharacter();
    const vector<CFighter *> getCharacters() const { return characters; };

private:
    string username;
    string password;
    bool admin;  // 是否為管理員
    vector<CFighter *> characters;  // 該帳號下的角色列表
};

#endif
