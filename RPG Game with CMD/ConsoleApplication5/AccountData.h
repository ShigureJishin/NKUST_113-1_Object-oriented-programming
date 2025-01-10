#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H

#include <iostream>
#include <vector>
#include "Account.h"
#include "Fighter.h"

using namespace std;

class CAccountData {
public:
	CAccountData(const string filename);
	bool login(const string username, const string password);
	void logout();
	bool createAccount(string username, string password);
	bool deleteAccount();
	void listUsers() const;
	int resetPassword();
	CFighter* getFighter() { return currentCharacter; };
	Account *getAccount_by_username(const string username);
	int query();
	int queryCharacters();
	void loadFromFile();
	void saveToFile() const;

private:
	bool isValid_Space(const string inData);

	vector<Account *> accounts;     // �x�s���q�b��
	string dataFile;
	Account *adminAccount;
	Account *loggedInAccount;

	CFighter *currentCharacter;   // ��e��ܪ�����

	Account *usernameExists(string username) const;
};
#endif