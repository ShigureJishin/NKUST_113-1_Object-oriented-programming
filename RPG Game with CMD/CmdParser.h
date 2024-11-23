#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class CCmdParser {
public:
  CCmdParser();
  int query ();
  void splitstring(const string& s, vector<string>& v, const string& c);
  
private:
  map<string,  void (*)> cmdMap; // «ü¥O¶°
};

#endif