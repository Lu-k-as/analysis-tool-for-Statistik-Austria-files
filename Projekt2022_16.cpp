#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include"importdata.h"
#include"database.h"

using namespace std;


//Hier könnten weiter Dateien welche im Verzeichnis sind eingefügt werden.
vector<string> data = {"AT_Energieverbrauch_nach_Bereichen_1970-2020.csv","AT_Energieverbrauch_nach_Energietraegern_1970-2020.csv"};


//Menue zur Auswahl welche Datei aus dem vector - data eingelesen werden soll
void menuedateiauswahl(vector<string>& data, int& select){
    int inputvalue;
    bool auswahl = true;
    string rawstring;
    vector<int> possibleinputvalues, colums;   

    do{
        cout << "------ MENÜ - DATEIAUSWAHL ------" << endl;
        cout << "Bitte wählen Sie die Datei aus die Sie einlesen möchten:" << endl;
        for (int i = 0; i<data.size();i++){
            cout << "<" << i << "> " << data[i] << endl;
            possibleinputvalues.push_back(i);
        }

        try{
            sichereeingabe_only_one_value(inputvalue, possibleinputvalues); // --> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Dateiauswahl: " << err.what() << endl;
        }
    }while(auswahl);
    select = inputvalue;
    return;
}


//Menue welche Spalten von der Originaldatei im Ergebniss erscheinen sollen 
void menuespaltenauswahl(Database& storage, vector<int>& columns){
    vector<int> possibleinputvalues;  
    vector<string> vector = storage.getcolums();   
    int auswahl =true;
    do{ 
        cout <<endl<< "------ MENÜ - SPALTENAUSWAHL ------" << endl;
        cout << "Bitte wählen Sie die Spalten aus die in der Datei erscheinen sollen:" << endl;
        cout << "Merhfachauswahl durch z.B. <1 3 4>"<<endl;
        for(int i = 1; i < vector.size(); i++){
            cout<<"<" << i << ">" <<vector[i]<<endl;
            possibleinputvalues.push_back(i);
        }
        cout<<"<" << "Q" << ">" <<" Quit"<<endl;

        try{
            sichereeingabe(columns, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Dateiauswahl: " << err.what() << endl;
        }
    }while(auswahl);
    return;
}


//Menue zur Auswahl ob generell die Ausgabe per Wert oder in Porzent zur Gesammtmenge ausgegeben werden soll
void menue_Value_Percentage (int& x){
    vector<int> possibleinputvalues = {VALUE,PERCENT};
    int inputvalue, auswahl = true;  

    do{ 
        cout <<endl<< "------ MENÜ - WERT ODER PROZENTAUSAGABE ------" << endl;
        cout << "Bitte wählen Sie zwischen:" << endl;
        cout << "<" << VALUE <<"> Wert" << endl;
        cout << "<" << PERCENT <<"> Anteil [%]" << endl;
        cout << "<" << "Q" << ">" <<" Quit"<<endl; 

        try{
            sichereeingabe_only_one_value(inputvalue, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Value-Percentage: " << err.what() << endl;
        }
    }while(auswahl);
    x=inputvalue;
    return;
}


//Menue zur Auswahl des Zeitraums Anfang-Ende für die Ausgabe der Werte
void menuzeitraumauswahl(Database& storage, int& beginn, int& ende){
    int beginn_i, ende_i;
    bool auswahl = true;

    vector<int> possibleinputvalues;
    storage.getyears(possibleinputvalues); //--> database.cpp

    //Ermittlung vom Beginn des Zeitraumes
    do{ 
        cout <<endl<< "------ MENÜ - ZEITRAUM - BEGINN ------" << endl;
        cout << "Bitte wählen Sie ab wann Sie an den Daten interresiert sind:" << endl;
        cout << "Wählen Sie dafür ein Jahr zwischen: ";
        cout << "<" << *min_element(possibleinputvalues.begin(), possibleinputvalues.end()) <<"> und " << endl;
        cout << "<" << *max_element(possibleinputvalues.begin(), possibleinputvalues.end()) <<"> Anteil [%]" << endl;
        cout << "<" << "Q" << ">" <<" Quit"<<endl; 

        try{
            sichereeingabe_only_one_value(beginn_i, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Zeitraumauswahl: " << err.what() << endl;
        }
    }while(auswahl);

    auswahl = true;
    //Ermittlung vom Ende des Zeitraumes
    do{ 
        cout <<endl<< "------ MENÜ - ZEITRAUM - Ende ------" << endl;
        cout << "Bitte wählen Sie bis wann Sie an den Daten interresiert sind:" << endl;
        cout << "Wählen Sie dafür ein Jahr zwischen: ";
        cout << "<" << beginn_i <<"> und " << endl;
        cout << "<" << *max_element(possibleinputvalues.begin(), possibleinputvalues.end()) <<"> Anteil [%]" << endl;
        cout << "<" << "Q" << ">" <<" Quit"<<endl; 

        try{
            sichereeingabe_only_one_value(ende_i, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Zeitraumauswahl: " << err.what() << endl;
        }
    }while(auswahl);

    beginn =  beginn_i;
    ende =  ende_i;
    return;
}


//Menue zur Asuwahl für wieviele Jahre eine Prognose erstellt werden soll
void menuprogrnose(int& futureyears){
    bool auswahl =true;
    int input_years;
    vector<int> possibleinputvalues = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    do{ 
        cout <<endl<< "------ MENÜ - PROGNOSE ------" << endl;
        cout << "Bitte wählen Sie für wieviel Jahre eine Prgnose erstellt werden soll (Maximal <20>)" << endl;
        cout << "<" << "0" << ">"<<endl;  
        cout << "..."<<endl;  
        cout << "<" << "20" << ">"<<endl;                
        cout << "<" << "Q" << ">" <<" Quit"<<endl; 

        try{
            sichereeingabe_only_one_value(input_years, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Prognose: " << err.what() << endl;
        }
    }while(auswahl);
    futureyears = input_years;
    return;    
}


//Menu zur Auswahl wie die Daten ausgegeben werden sollen (Bildschirm, Datei)
void menudatashow(int& show_print){
    bool auswahl =true;
    int input;
    vector<int> possibleinputvalues = {0,1,2};

    do{ 
        cout <<endl<< "------ MENÜ - AUSGABE ------" << endl;
        cout << "Bitte wählen Sie aus was mit den erstelleten Daten passieren soll:" << endl;
        cout << "<" << "0" << ">" <<" Bildschirmausgabe"<<endl; 
        cout << "<" << "1" << ">" <<" Speichern in einer Datei"<<endl; 
        cout << "<" << "2" << ">" <<" Speichern in einer Datei und Bildschirmausgabe"<<endl;         
        cout << "<" << "Q" << ">" <<" Quit"<<endl; 

        try{
            sichereeingabe_only_one_value(input, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Ausgabe: " << err.what() << endl;
        }
    }while(auswahl);
    show_print = input;
    return;
}


//Spezialmenue falls die Datei die ersellt werden soll bereits existiert 
bool menustoredataifexists(){
    bool auswahl =true;
    int input;
    vector<int> possibleinputvalues = {0,1};

    do{ 
        cout <<endl<< "------ MENÜ - DATEI ÜBERSCHREIBEN ------" << endl;
        cout << "Es existiert bereits eine Datei die diese Daten enthält, soll diese überschrieben werden?" << endl;
        cout << "<" << "0" << ">" <<" JA - Datei überschreiben"<<endl; 
        cout << "<" << "1" << ">" <<" NEIN - Datei beibehalten"<<endl;          
        cout << "<" << "Q" << ">" <<" Quit"<<endl; 

        try{
            sichereeingabe_only_one_value(input, possibleinputvalues); //--> importdata.cpp
            auswahl = false;
        }
        catch (const runtime_error &err){
            cerr << "Error at Menue Datei überschreiben: " << err.what() << endl;
        }
    }while(auswahl);
    if(input==0){
        return true;
    }
    else
        return false;

}


//Menu zur Speicherung der Werte in eine Datei
void menustoredata(Database& storage, int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl){
    bool build = true;
    try{
        string filename = getfilename(storage,  beginn, ende, value_or_percent,spaltenauswahl);
        cout << filename;
        if(exists(filename)){
            build = menustoredataifexists();
        }
        if(build){
            storage.storedata(filename, beginn, ende, value_or_percent,spaltenauswahl);
        }
    }
    catch(const runtime_error &err){
        cerr << "Error: " << err.what() << endl; 
        throw runtime_error("Speichern der Datei ist fehlgeschlagen");
    }
}


// State-Maschine welche den grundsätzlichen Programmdurchlauf wiederspiegelt
void statemaschine(){
    Database storage;    //database.cpp
    int select_input_data,value_or_percent,beginn,ende,futureyears,show_print;
    vector<int> columns;
    
    try{
    // Menü zur Dateiauswahl
    menuedateiauswahl(data, select_input_data);

    // Daten einlesen
    loaddata(data[select_input_data], storage); // --> importdata.cpp
    cout << endl << "Datei " << data[select_input_data] << " wurde gelesen" << endl << endl << endl << endl;

    // Menü zur Spaltenauswahl
    menuespaltenauswahl(storage, columns);

    // Menü zur Ausgabe in Prozent oder Zahlenwerten
    menue_Value_Percentage(value_or_percent);

    // Menü zur Auswahl des Zeitraumes;
    menuzeitraumauswahl(storage, beginn, ende); 

    // Prognose Erstellen
    menuprogrnose(futureyears);
    storage.prognose(futureyears); // --> database.cpp

    //show
    menudatashow(show_print);

    switch (show_print) {
    case 0:    
        storage.printdata(beginn,ende,value_or_percent,columns); // --> database.cpp
        break;
    case 1:
        menustoredata(storage, beginn,ende,value_or_percent,columns);
        break;
    case 2:
        storage.printdata(beginn,ende,value_or_percent,columns); // --> database.cpp
        menustoredata(storage, beginn,ende,value_or_percent,columns);       
    }

    }
    catch (const runtime_error &err){
        cerr << "Error: " << err.what() << endl;
    }
}


// Hauptprogramm welches wiederkehrend die State-Maschine aufruft
int main(){
    cout << endl << "Willkommen in der Progrnoseanwendung für Energie-Montoring" << endl << endl;
    try{
        while(true){
            statemaschine();
            cout << endl << endl;
            cout << "ES WIRD NUN EIN ERNEUTER DURCHGANG DES PROGRAMMES GESTARTET" << endl << endl;
        }    
    }
    catch(const string& e){
        cout << "Quit Programm" << endl;
    }
    return 0;
}