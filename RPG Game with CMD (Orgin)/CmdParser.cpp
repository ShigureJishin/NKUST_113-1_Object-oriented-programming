#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "CmdParser.h"

// �h�X�{��
int function_exit (vector<string> &tokens){	
	return -1;
}

// �n�X
int function_logout (vector<string> &tokens){
  

  return 0;
}

// �c�y���O��
CCmdParser::CCmdParser() {
    cmdMap [string("exit")] = function_exit;
    cmdMap[string("logout")] = function_logout;
    /*cmdMap["list"] = &CAccountManager::list;
    cmdMap["changepassword"] = &CAccountManager::changePassword;*/
}

// �`�n�B��
int CCmdParser::query (){
  string sentense;  
  getline (cin, sentense);  

  vector<string> tokens;
  splitstring (sentense, tokens, string(" "));  
  if (tokens.size () == 0){
    return 0;
  }

  map<string,  void (*)>::iterator it;
  it = cmdMap.find (tokens [0]);
  if (it == cmdMap.end ()){
    cout << "no such commands" << endl;
    return 0;
  }  
  return (reinterpret_cast<int(*)(const vector<string> &)>(it->second)(tokens));
}

// ���Φr��
void CCmdParser::splitstring(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find_first_of(c);
	pos1 = 0;
	while (string::npos != pos2){
		if(pos2-pos1)
			v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

