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

    // 內建管理員帳號，非檔案中的資料
    adminAccount = new Account("admin", "admin", true);
#if 0
    if (adminAccount)
        cout << "Add Admin account." << adminAccount->getUsername() << " " << adminAccount->getPassword() << endl;
#endif
}

// 登入
bool CAccountData::login(const string username,const string password) {

    // 優先檢查內建管理員
    if (username == adminAccount->getUsername() && username == adminAccount->getPassword()) {
        loggedInAccount = adminAccount;
        return true;
    }
    // 檢查檔案中的普通帳號
    for (const auto& account : accounts) {
        if (account->getUsername() == username && account->validatePassword(password)) {
            loggedInAccount = account;
            return true;
        }
    }
    return false;
}

// 登出
void CAccountData::logout() {
    loggedInAccount = nullptr;
}

// 建立新帳號
bool CAccountData::createAccount(string username, string password) {
    if (usernameExists(username)) {
        return false;
    }

    Account* newAccount = new Account(username, "password", false);
    newAccount->setPassword(password);
    accounts.push_back(newAccount); // 普通帳號
    saveToFile();
    return true;
}

// 刪除帳號
bool CAccountData::deleteAccount() {
    string inUsername;
    listUsers();
    cout << "請輸入要刪除帳號的使用者名稱：";
    cin >> inUsername;

    Account* inAccount = getAccount_by_username(inUsername);

    if (!inAccount) {
        cout << "找不到該使用者。\n";
        return false;
    }

    accounts.erase(find(accounts.begin(), accounts.end(), inAccount));
    saveToFile();
    cout << "已成功刪除帳號 " << inUsername << " 。\n";
    return true;
}

// 列出所有普通使用者
void CAccountData::listUsers() const {
    cout << "使用者帳號：\n";
    for (const auto& account : accounts) {
        cout << "- " << account->getUsername() << "\n";
    }
}

// 檢查帳號是否已存在
Account *CAccountData::usernameExists(string username) const {
    if (username == adminAccount->getUsername()) {
        return adminAccount; // 避免重複名稱和管理員帳號名稱相同
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
        return nullptr; // 避免重複名稱和管理員帳號名稱相同
    }
    for (const auto& account : accounts) {
        if (account->getUsername() == username) {
            return account;
        }
    }
    return false;
}
// 忘記密碼副程式
int CAccountData::resetPassword() {
    string inUsername;
    listUsers();
    cout << "請輸入要重設密碼的使用者名稱：";
    cin >> inUsername;

    Account* inAccount = getAccount_by_username(inUsername);

    if (!inAccount) {
        cout << "找不到該使用者。\n";
        return -1; // 表示失敗
    }

    string newPassword1, newPassword2;
    do {
        cout << "請輸入新密碼：";
        cin >> newPassword1;
        cout << "請再次輸入新密碼：";
        cin >> newPassword2;

        
        if (newPassword1 != newPassword2) {
           cout << "兩次輸入的密碼不一致，請重新輸入。\n";
        }
        else if (!isValid_Space(newPassword1)) {
            cout << "名稱不能為空或包含空白字符，請重新輸入。\n";
        }
    } while (newPassword1 != newPassword2 || !isValid_Space(newPassword1) || !isValid_Space(newPassword2));

    inAccount->setPassword(newPassword1);
    saveToFile();
    cout << "已成功重設 " << inUsername << " 的密碼。\n";
    return 0; // 表示成功
}

// 從檔案載入資料
void CAccountData::loadFromFile() {
    CGlobalInfo::itm_data->Initialize();

    ifstream file(dataFile);
    if (!file.is_open()) {
        cout << "無法讀取資料檔案。\n";
        return;
    }
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        int characterCount;

        if (ss >> username >> password >> characterCount) {
            // 創建新帳號
            Account* newAccount = new Account(username, password, false);

            // 從文件中讀取角色
            for (int i = 0; i < characterCount; ++i) {
                if (!getline(file, line)) {
                    cout << "讀取角色資料時出錯！\n";
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
                default: profession = Profession::Berserker; break; // 默認職業
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


// 儲存資料到檔案
void CAccountData::saveToFile() const {
    ofstream file(dataFile);
    if (!file.is_open()) {
        cout << "無法寫入資料檔案！\n";
        return;
    }
    for (const auto& account : accounts) {
        // 儲存使用者名稱、密碼與角色數量
        file << account->getUsername() << " "
            << account->getPassword() << " "
            << account->getCharacters().size() << "\n";


        // 儲存每個角色的數據
        for (CFighter *fighter : account->getCharacters()) {
            file << fighter->getname() << " "    // 名稱
                << fighter->getProfession() << " " //職業
                << fighter->get_current_city() << " " // 所在位置
                << fighter->getHP() << " "      // HP
                << fighter->getMAXHP() << " "   // HP
                << fighter->getSP() << " "      // SP
                << fighter->getMAXSP() << " "   // HP
                << fighter->getMP() << " "      // MP
                << fighter->getMAXMP() << " "   // MP
                << fighter->getDefense() << " " // 防禦
                << fighter->getMoney() << " "   // 金錢
                << fighter->getXP() << " "      // 經驗值
                << fighter->getLevel() << " "   // 等級
                << fighter->getLucky() << " "   // 幸運值
                << fighter->getProperty_Point() << " "   // 屬性點數
                << fighter->getSkill_Point() << " ";     // 技能點數
                

            /*0.裝備 1.技能 2.背包 3.寵物*/
            file << fighter->serializeArror() << " ";
            file << fighter->serializeSkills() << " ";
            file << fighter->serializePets() << " ";
            file << fighter->serializeBag() << " ";
            file << fighter->serializeCurrentPet();
            file << "\n";
            // 一個角色存檔結束
        }
    }
    file.close();
}

int CAccountData::query() {
    string username, password;

    if (loggedInAccount != NULL)
        cout << "登入成功！歡迎，" << loggedInAccount->getUsername() << "。" << endl;

    cout << "功能選單：\n";
    cout << "1. 登入\n";
    cout << "2. 建立帳號\n";
    cout << "3. 刪除帳號(管理員功能)\n";
    cout << "4. 忘記密碼(管理員功能)\n";
    cout << "5. 登出\n";
    cout << "0. 離開\n";
    cout << "請選擇功能：";

    char selection;
    cin >> selection;
    cin.ignore(1024, '\n');

    switch (selection) {
    case '1': { // 登入
        if (loggedInAccount) {
            cout << "您已經登入了，請您先登出再來登入。" << endl;
        }
        else {
            cout << "請輸入使用者名稱: ";
            getline(cin, username);

            cout << "請輸入密碼: ";
            getline(cin, password);

            if (login(username, password)) {
                if (loggedInAccount != adminAccount)
                    return 0; // 離開登入系統，進入選角色
            }
            else {
                cout << "帳號或密碼錯誤，請重新嘗試。" << endl;
            }
        }

        break;
    }
    case '2': { // 建立帳號
        cout << "請輸入新使用者名稱: ";
        getline(cin, username);
        cout << "請輸入新密碼: ";
        getline(cin, password);

        if (!isValid_Space(username)) {
            cout << "名稱不能為空或包含空白字符，請重新輸入。\n";
        }
        else if (createAccount(username, password)) {
            cout << "帳號建立成功！" << endl;
        }
        else {
            cout << "帳號已存在。" << endl;
        }
       
        break;
    }
    case '3': { // 刪除帳號(管理員功能)
        if (loggedInAccount == adminAccount) {
            deleteAccount();
        }
        else {
            cout << "此功能僅限管理員使用。" << endl;
        }
        break;
    }
    case '4': { // 忘記密碼(管理員功能)
        if (loggedInAccount == adminAccount) {
            resetPassword();
        }
        else {
            cout << "此功能僅限管理員使用。" << endl;
        }
        break;
    }
    case '5': { // 登出
        if (loggedInAccount) {
            cout << loggedInAccount->getUsername() << " 下次見，已為您登出。" << endl;
            logout();
        }
        else {
            cout << "都沒登入，你還想要登出。" << endl;
        }
        break;
    }
    case '0': { // 離開
        system("cls");
        cout << "再見！" << endl;

        exit(0);
    }
    default:
        cout << "無效的選項，請重新選擇。" << endl; 
        break;
    }

    return -1;  // 保持登入系統

}

int CAccountData::queryCharacters() {

    cout << "登入成功！歡迎，" << loggedInAccount->getUsername() << "。" << endl;
    cout << "角色管理選單：\n";
    cout << "1. 創建角色\n";
    cout << "2. 選擇角色\n";
    cout << "3. 刪除角色\n";
    cout << "0. 結束遊戲\n";
    cout << "請選擇功能：";

    char selection;
    cin >> selection;
    cin.ignore(1024, '\n');

    switch (selection) {
    case '1': { // 創建角色
        string name, profession;
        cout << "輸入角色名稱：";
        getline(cin, name);

        if (!isValid_Space(name)) {
            cout << "名稱不能為空或含有空白字符，請重新輸入。\n";
            break;
        }

        cout << "選擇職業（Berserker/Mage/Tank）：";
        getline(cin, profession);

        if (loggedInAccount->addCharacter(name, profession)) {
            cout << "角色 " << name << " 創建成功！" << endl;
            saveToFile();
        }

        break;
    }
    case '2': { // 選擇角色
        currentCharacter = loggedInAccount->selectCharacter();
        if (currentCharacter) {
            cout << "已選擇角色：" << currentCharacter->getname() << endl;
            return 0;   
        }
        
        break;
    }
    case '3': { // 刪除角色
        if (loggedInAccount->deleteCharacter()) {
            cout << "角色刪除成功。" << endl;
        }
        else {
            cout << "角色刪除失敗，可能尚未創建角色。" << endl;
        }
        break;
    }
    case '0': // exit game
        system("cls");
        cout << "再見！" << endl;
        exit(0);
    default:
        cout << "無效的選項，請重新選擇。" << endl;
    }
    
    return -1;
}

bool CAccountData::isValid_Space(const string inData) {
    if (inData.empty()) return false; // 檢查是否為空
    for (char c : inData) {
        if (isspace(c)) return false; // 檢查是否包含空白字符
    }
    return true;
}