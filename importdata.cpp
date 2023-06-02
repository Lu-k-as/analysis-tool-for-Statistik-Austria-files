#include "importdata.h"
#include "database.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;


//Funktionen um ein Datei welche eine spezielle formatierung aufweist in eine art datenbank zu laden
void loaddata(const string& datafilename,Database& storage){
    string line;
    vector<string> column;
    ifstream myfile (datafilename);
    size_t pos1,pos2;  
    Database_element dataelement; //-->database.cpp
    double sum;

    if (myfile.is_open()){

        //Spaltennamen einlesen und speichern
        getline (myfile,line); 
        pos1 = line.find(";");
        column.push_back(line.substr(0,pos1));
        while(pos1 != string::npos){
            pos2 = line.find(";", pos1+1);
            column.push_back(line.substr(pos1+1,pos2-pos1-1));
            pos1 = pos2;
        }
        storage.setcolumns(column);

        //Datensätze einlesen
        while (getline(myfile,line)){
            pos1 = line.find(";");
            if(pos1 == string::npos){
                break;
            }
            dataelement.year = stoi(line.substr(0,pos1)); //erster Eintrag ist immer das Jahr in int
            while(pos1 != string::npos){ //nun folgen die anderen Spalten
                pos2 = line.find(";", pos1+1);
                dataelement.el.push_back(stod(line.substr(pos1+1,pos2-pos1-1)));
                pos1 = pos2;
            }
            //Berechnung der Summe aller Werte / die gasammte Energiemenge dieses Jahres
            sum = 0;
            for(int i = 0; i<dataelement.el.size();i++){
                sum += dataelement.el[i];
            }
            dataelement.sum = sum;
            storage.addentry(dataelement); //--> database.cpp
            dataelement.el.clear();
        }
        myfile.close();
    }
    else{
        throw runtime_error("Unable to open file");
    }
    return;
}


//Einlesen von Werten in columns, welche aber in possibleinputvalues stehen
void sichereeingabe(vector<int>& columns,const vector<int>& possibleinputvalues){
    string rawstring,strip;
    size_t pos1 = 0,pos2; 
    int value;
    getline(cin, rawstring); 
    columns.clear();

    //Einfach einmal alle Werte Einlesen und nur auf "Q" überprüfen
    while(pos1 != string::npos){
        pos2 = rawstring.find(" ", pos1+1);
        strip = rawstring.substr(pos1,pos2-pos1);
        if(0 == strip.compare("Q")){ //Falls das Programm abgebrochen werden soll wird "Q" eingegeben
            cout <<endl << endl<< "Quit Programm" << endl <<endl;
            throw "Quit"; 
            //Hier und nur hier wird ein anderer bestimmter (string) Error geworfen, welcher
            //sich von den anderen Errors unterscheidet da er NUR in der höchsten Instanz an Funktionen
            //nämlich main() bearbeitet wird und dort das gesammt programm beeendet.
            //Hier befindet sich also die einzige Möglichkeit das Programm zu schließen !!!
        }
        try{
        value = stoi(rawstring.substr(pos1,pos2-pos1));
        }
        catch(...){
            throw runtime_error("Bitte eine Zahl eingeben");
        }
        columns.push_back(value);
        if(pos2 == string::npos) {pos1 = string::npos;}
        else{ pos1 = pos2+1; }
    }


    for(int i = 0; i < columns.size(); i++){
        //Überprüfen ob die Eingabewerte in den Possibleinputvalues enthalten sind
        if (find(possibleinputvalues.begin(), possibleinputvalues.end(), columns[i]) == possibleinputvalues.end()){
            throw runtime_error("Eingabe außerhalb des Wertebereiches");
        } 
        //Doppelte Einträge entfernen
        if (find(columns.begin(), columns.begin()+i, columns[i]) != columns.begin()+i){
            columns.erase(columns.begin()+i);
            i--;
        }
    }
    sort(columns.begin(),columns.end());
    return;
}


//Wie sichereeingabe() nur dass nur ein Wert zurückgegeben werden darf
void sichereeingabe_only_one_value(int& value,const vector<int>& possibleinputvalues){
    vector<int> columns;

    sichereeingabe(columns, possibleinputvalues);
    if (columns.size()!=1){
        throw runtime_error("Bitte nur einen Wert Eingeben.");
    }
    value = columns.back();
    return;
}


// Check ob die Datei mit <name> schon existiert
bool exists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}


// Automatisierte Erstellung eines Namens für die Ausgabedatei
string& getfilename(Database& Data, int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl){
    string string1; 
    static string string2;
    string2.clear();
    vector<string> columns = Data.getcolums();
    
    string2 = "AT_Energieverbrauch_von_" + to_string(beginn);
    string2 += "-";
    string2 += to_string(ende);
    string2 += "_von";

    for(int i = 0; i < spaltenauswahl.size(); i++){
        string2 += "_";
        string2 += columns[spaltenauswahl[i]];
    }
    string2 += string1;
    if(value_or_percent == PERCENT){
        string2 += "_in_Prozent";
    }
    string2 += ".csv";
    return string2;
}