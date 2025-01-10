#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include "AccountData.h"
#include "Fighter.h"
#include "LifeEntity.h"
#include "GlobalInfo.h"
#include "ItemData.h"

using namespace std;

CAccountData::CAccountData(const string filename="") : dataFile(filename) {
    loggedInAccount = NULL;
    loadFromFile();

    // ���غ޲z���b���A�D�ɮפ������
    adminAccount = new Account("admin", "admin", true);
#if 0
    if (adminAccount)
        cout << "Add Admin account." << adminAccount->getUsername() << " " << adminAccount->getPassword() << endl;
#endif
}

// �n�J
bool CAccountData::login(const string username,const string password) {

    // �u���ˬd���غ޲z��
    if (username == adminAccount->getUsername() && username == adminAccount->getPassword()) {
        loggedInAccount = adminAccount;
        return true;
    }
    // �ˬd�ɮפ������q�b��
    for (const auto& account : accounts) {
        if (account->getUsername() == username && account->validatePassword(password)) {
            loggedInAccount = account;
            return true;
        }
    }
    return false;
}

// �n�X
void CAccountData::logout() {
    loggedInAccount = nullptr;
}

// �إ߷s�b��
bool CAccountData::createAccount(string username, string password) {
    if (usernameExists(username)) {
        return false;
    }

    Account* newAccount = new Account(username, "password", false);
    newAccount->setPassword(password);
    accounts.push_back(newAccount); // ���q�b��
    saveToFile();
    return true;
}

// �R���b��
bool CAccountData::deleteAccount() {
    string inUsername;
    listUsers();
    cout << "�п�J�n�R���b�����ϥΪ̦W�١G";
    cin >> inUsername;

    Account* inAccount = getAccount_by_username(inUsername);

    if (!inAccount) {
        cout << "�䤣��ӨϥΪ̡C\n";
        return false;
    }

    accounts.erase(find(accounts.begin(), accounts.end(), inAccount));
    saveToFile();
    cout << "�w���\�R���b�� " << inUsername << " �C\n";
    return true;
}

// �C�X�Ҧ����q�ϥΪ�
void CAccountData::listUsers() const {
    cout << "�ϥΪ̱b���G\n";
    for (const auto& account : accounts) {
        cout << "- " << account->getUsername() << "\n";
    }
}

// �ˬd�b���O�_�w�s�b
Account *CAccountData::usernameExists(string username) const {
    if (username == adminAccount->getUsername()) {
        return adminAccount; // �קK���ƦW�٩M�޲z���b���W�٬ۦP
    }
    for (const auto& account : accounts) {
        if (account->getUsername() == username) {
            return account;
        }
    }
    return nullptr;
}

Account *CAccountData::getAccount_by_username(const string username) {
    if (username == adminAccount->getUsername()) {
        return nullptr; // �קK���ƦW�٩M�޲z���b���W�٬ۦP
    }
    for (const auto& account : accounts) {
        if (account->getUsername() == username) {
            return account;
        }
    }
    return false;
}
// �ѰO�K�X�Ƶ{��
int CAccountData::resetPassword() {
    string inUsername;
    listUsers();
    cout << "�п�J�n���]�K�X���ϥΪ̦W�١G";
    cin >> inUsername;

    Account* inAccount = getAccount_by_username(inUsername);

    if (!inAccount) {
        cout << "�䤣��ӨϥΪ̡C\n";
        return -1; // ��ܥ���
    }

    string newPassword1, newPassword2;
    do {
        cout << "�п�J�s�K�X�G";
        cin >> newPassword1;
        cout << "�ЦA����J�s�K�X�G";
        cin >> newPassword2;

        
        if (newPassword1 != newPassword2) {
           cout << "�⦸��J���K�X���@�P�A�Э��s��J�C\n";
        }
        else if (!isValid_Space(newPassword1)) {
            cout << "�W�٤��ର�ũΥ]�t�ťզr�šA�Э��s��J�C\n";
        }
    } while (newPassword1 != newPassword2 || !isValid_Space(newPassword1) || !isValid_Space(newPassword2));

    inAccount->setPassword(newPassword1);
    saveToFile();
    cout << "�w���\���] " << inUsername << " ���K�X�C\n";
    return 0; // ��ܦ��\
}

// �q�ɮ׸��J���
void CAccountData::loadFromFile() {
    CGlobalInfo::itm_data->Initialize();

    ifstream file(dataFile);
    if (!file.is_open()) {
        cout << "�L�kŪ������ɮסC\n";
        return;
    }
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        int characterCount;

        if (ss >> username >> password >> characterCount) {
            // �Ыطs�b��
            Account* newAccount = new Account(username, password, false);

            // �q���Ū������
            for (int i = 0; i < characterCount; ++i) {
                if (!getline(file, line)) {
                    cout << "Ū�������ƮɥX���I\n";
                    break;
                }
                stringstream characterStream(line);
                string characterName;
                Profession profession;
                int professionInt;
                int cur_city;
                int HP, MAXHP, SP, MAXSP, MP, MAXMP, Lucky, Defense, Level, Money, XP, Ponint, SkillPoint;
                string ArrorList, SkillList, PetList, BagList, CurrentPet;
                characterStream >> characterName >> professionInt >> cur_city >> HP >> MAXHP >> SP >> MAXSP >> MP >> MAXMP
                    >> Defense >> Money >> XP >> Level >> Lucky >> Ponint >> SkillPoint >> ArrorList >> SkillList >> PetList >> BagList >> CurrentPet;

                switch (professionInt) {
                case 1: profession = Profession::Berserker; break;
                case 2: profession = Profession::Mage; break;
                case 3: profession = Profession::Tank; break;
                default: profession = Profession::Berserker; break; // �q�{¾�~
                }

                CFighter* newCharacter = new CFighter(characterName, MAXHP, HP, SP, MAXSP, MP, MAXMP, Lucky, Defense,
                    Money, XP, Level, cur_city, profession, Ponint, SkillPoint);
                newCharacter->deserializeArror(ArrorList);
                newCharacter->deserializeSkills(SkillList);
                newCharacter->deserializePets(PetList);
                newCharacter->deserializeBag(BagList);
                newCharacter->deserializeCurrentPet(CurrentPet);
#if 0
                cout << "ArrorList: " << ArrorList << endl;
                cout << "SkillList: " << SkillList << endl;
                cout << "PetList: " << PetList << endl;
                cout << "BagList: " << BagList << endl;
#endif
                newAccount->loadCharacter(newCharacter);
                system("cls");
            }

            accounts.push_back(newAccount);
        }
    }
    file.close();
}


// �x�s��ƨ��ɮ�
void CAccountData::saveToFile() const {
    ofstream file(dataFile);
    if (!file.is_open()) {
        cout << "�L�k�g�J����ɮסI\n";
        return;
    }
    for (const auto& account : accounts) {
        // �x�s�ϥΪ̦W�١B�K�X�P����ƶq
        file << account->getUsername() << " "
            << account->getPassword() << " "
            << account->getCharacters().size() << "\n";


        // �x�s�C�Ө��⪺�ƾ�
        for (CFighter *fighter : account->getCharacters()) {
            file << fighter->getname() << " "    // �W��
                << fighter->getProfession() << " " //¾�~
                << fighter->get_current_city() << " " // �Ҧb��m
                << fighter->getHP() << " "      // HP
                << fighter->getMAXHP() << " "   // HP
                << fighter->getSP() << " "      // SP
                << fighter->getMAXSP() << " "   // HP
                << fighter->getMP() << " "      // MP
                << fighter->getMAXMP() << " "   // MP
                << fighter->getDefense() << " " // ���m
                << fighter->getMoney() << " "   // ����
                << fighter->getXP() << " "      // �g���
                << fighter->getLevel() << " "   // ����
                << fighter->getLucky() << " "   // ���B��
                << fighter->getProperty_Point() << " "   // �ݩ��I��
                << fighter->getSkill_Point() << " ";     // �ޯ��I��
                

            /*0.�˳� 1.�ޯ� 2.�I�] 3.�d��*/
            file << fighter->serializeArror() << " ";
            file << fighter->serializeSkills() << " ";
            file << fighter->serializePets() << " ";
            file << fighter->serializeBag() << " ";
            file << fighter->serializeCurrentPet();
            file << "\n";
            // �@�Ө���s�ɵ���
        }
    }
    file.close();
}

int CAccountData::query() {
    string username, password;

    if (loggedInAccount != NULL)
        cout << "�n�J���\�I�w��A" << loggedInAccount->getUsername() << "�C" << endl;

    cout << "�\����G\n";
    cout << "1. �n�J\n";
    cout << "2. �إ߱b��\n";
    cout << "3. �R���b��(�޲z���\��)\n";
    cout << "4. �ѰO�K�X(�޲z���\��)\n";
    cout << "5. �n�X\n";
    cout << "0. ���}\n";
    cout << "�п�ܥ\��G";

    char selection;
    cin >> selection;
    cin.ignore(1024, '\n');

    switch (selection) {
    case '1': { // �n�J
        if (loggedInAccount) {
            cout << "�z�w�g�n�J�F�A�бz���n�X�A�ӵn�J�C" << endl;
        }
        else {
            cout << "�п�J�ϥΪ̦W��: ";
            getline(cin, username);

            cout << "�п�J�K�X: ";
            getline(cin, password);

            if (login(username, password)) {
                if (loggedInAccount != adminAccount)
                    return 0; // ���}�n�J�t�ΡA�i�J�﨤��
            }
            else {
                cout << "�b���αK�X���~�A�Э��s���աC" << endl;
            }
        }

        break;
    }
    case '2': { // �إ߱b��
        cout << "�п�J�s�ϥΪ̦W��: ";
        getline(cin, username);
        cout << "�п�J�s�K�X: ";
        getline(cin, password);

        if (!isValid_Space(username)) {
            cout << "�W�٤��ର�ũΥ]�t�ťզr�šA�Э��s��J�C\n";
        }
        else if (createAccount(username, password)) {
            cout << "�b���إߦ��\�I" << endl;
        }
        else {
            cout << "�b���w�s�b�C" << endl;
        }
       
        break;
    }
    case '3': { // �R���b��(�޲z���\��)
        if (loggedInAccount == adminAccount) {
            deleteAccount();
        }
        else {
            cout << "���\��ȭ��޲z���ϥΡC" << endl;
        }
        break;
    }
    case '4': { // �ѰO�K�X(�޲z���\��)
        if (loggedInAccount == adminAccount) {
            resetPassword();
        }
        else {
            cout << "���\��ȭ��޲z���ϥΡC" << endl;
        }
        break;
    }
    case '5': { // �n�X
        if (loggedInAccount) {
            cout << loggedInAccount->getUsername() << " �U�����A�w���z�n�X�C" << endl;
            logout();
        }
        else {
            cout << "���S�n�J�A�A�ٷQ�n�n�X�C" << endl;
        }
        break;
    }
    case '0': { // ���}
        system("cls");
        cout << "�A���I" << endl;

        exit(0);
    }
    default:
        cout << "�L�Ī��ﶵ�A�Э��s��ܡC" << endl; 
        break;
    }

    return -1;  // �O���n�J�t��

}

int CAccountData::queryCharacters() {

    cout << "�n�J���\�I�w��A" << loggedInAccount->getUsername() << "�C" << endl;
    cout << "����޲z���G\n";
    cout << "1. �Ыب���\n";
    cout << "2. ��ܨ���\n";
    cout << "3. �R������\n";
    cout << "0. �����C��\n";
    cout << "�п�ܥ\��G";

    char selection;
    cin >> selection;
    cin.ignore(1024, '\n');

    switch (selection) {
    case '1': { // �Ыب���
        string name, profession;
        cout << "��J����W�١G";
        getline(cin, name);

        if (!isValid_Space(name)) {
            cout << "�W�٤��ର�ũΧt���ťզr�šA�Э��s��J�C\n";
            break;
        }

        cout << "���¾�~�]Berserker/Mage/Tank�^�G";
        getline(cin, profession);

        if (loggedInAccount->addCharacter(name, profession)) {
            cout << "���� " << name << " �Ыئ��\�I" << endl;
            saveToFile();
        }

        break;
    }
    case '2': { // ��ܨ���
        currentCharacter = loggedInAccount->selectCharacter();
        if (currentCharacter) {
            cout << "�w��ܨ���G" << currentCharacter->getname() << endl;
            return 0;   
        }
        
        break;
    }
    case '3': { // �R������
        if (loggedInAccount->deleteCharacter()) {
            cout << "����R�����\�C" << endl;
        }
        else {
            cout << "����R�����ѡA�i��|���Ыب���C" << endl;
        }
        break;
    }
    case '0': // exit game
        system("cls");
        cout << "�A���I" << endl;
        exit(0);
    default:
        cout << "�L�Ī��ﶵ�A�Э��s��ܡC" << endl;
    }
    
    return -1;
}

bool CAccountData::isValid_Space(const string inData) {
    if (inData.empty()) return false; // �ˬd�O�_����
    for (char c : inData) {
        if (isspace(c)) return false; // �ˬd�O�_�]�t�ťզr��
    }
    return true;
}