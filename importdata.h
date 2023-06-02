#include <string>
#include "database.h"
using namespace std;

#ifndef IMPORTDATA_H
#define IMPORTDATA_H

class exit_prog;
void loaddata(const string& datafilename, Database& storage);
void sichereeingabe(vector<int>& columns,const vector<int>& possibleinputvalues);
void sichereeingabe_only_one_value(int& value,const vector<int>& possibleinputvalues);
void getlinefromcin(string& str);
bool exists(const std::string& name);
string& getfilename(Database& storage, int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl);

#endif
