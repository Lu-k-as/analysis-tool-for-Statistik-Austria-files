#include <vector>
#include <string>
using namespace std;

#ifndef DATABASE_H
#define DATABASE_H

#define PERCENT 0
#define VALUE 1

//Grunstrukur eines Eintrags in einer Tabelle
struct Database_element{
    int year;
    vector<double> el;
    double sum;
};

//Allgemeine form der Datentabelle
class Database{
    public:
        void setcolumns(vector<string> namecloumns);
        void addentry(Database_element el);
        vector<string> getcolums(); 
        void printdata(int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl);
        void storedata(string& filename, int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl);
        void getyears(vector<int>& years);
        void prognose(int futureyears);
    private:
        vector<string> columns;
        vector<Database_element> Data;
        vector<Database_element> PrognoseData;
};

#endif