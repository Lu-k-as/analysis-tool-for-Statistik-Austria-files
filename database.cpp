#include "database.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;


// Spaltennamen der Datenbank einstellen
void Database::setcolumns(vector<string> namecloumns){
    columns = namecloumns;
}


// Einen Datensatz einfügen
void Database::addentry(Database_element el){
    Data.push_back(el);
}


// Spaltennamen der Datenbank ausgeben
vector<string> Database::getcolums(){
    return columns;
}


// Datenbank mit gewisser Auswahl in der Konsole ausgeben
void Database::printdata(int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl){
    cout<<setw(10)<< columns[0] <<"; ";
    for(int i = 0; i < spaltenauswahl.size(); i++)
    {
    cout<<setw(10)<<columns[spaltenauswahl[i]]<<"; ";
    }
    cout << endl;
    for(int i = 0; i < Data.size(); i++)
    {
        if(Data[i].year >= beginn && Data[i].year <= ende){
            cout << setw(10) << Data[i].year << "; ";
            for(int j = 0; j < spaltenauswahl.size(); j++){
                if(value_or_percent == VALUE){
                    cout<<setw(10)<<Data[i].el[spaltenauswahl[j]]<<"; ";
                } 
                else if(value_or_percent == PERCENT){
                    cout<<setw(10)<<(100*Data[i].el[spaltenauswahl[j]]/Data[i].sum)<<"; ";
                }  
            }
            cout << endl;
        }
    }

    cout << endl << "Nun folgt noch die Prognose" <<endl;
    cout<<setw(10)<< columns[0] <<"; ";
    for(int i = 0; i < spaltenauswahl.size(); i++)
    {
    cout<<setw(10)<<columns[spaltenauswahl[i]]<<"; ";
    }
    cout << endl;

    for(int i = 0; i < PrognoseData.size(); i++)
    {
        cout << setw(10) << PrognoseData[i].year << "; ";
        for(int j = 0; j < spaltenauswahl.size(); j++){
            if(value_or_percent == VALUE){
                cout<<setw(10)<<PrognoseData[i].el[spaltenauswahl[j]]<<"; ";
            }
            else if(value_or_percent == PERCENT){
                cout<<setw(10)<<(100*PrognoseData[i].el[spaltenauswahl[j]]/PrognoseData[i].sum)<<"; ";
            }  
        }
        cout << endl;
    }    
    cout << endl;
}


//Ausgabe aller Jahre die in der Datenbank gespeichert sind
void Database::getyears(vector<int>& years){
    for(int i = 0; i < Data.size(); i++)
    {
        years.push_back(Data[i].year);
    }
}


//Progrnose programm welche linear extrapoliert über die letzten 2 Jahre hinweg
void Database::prognose(int futureyears){
    Database_element n,n_1,n_2;
    double sum;

    n_1 = Data[Data.size()-1];
    n_2 = Data[Data.size()-2]; 

    for(int j = 0; j < futureyears; j++){

        n.el.clear();
        n.year = n_1.year +1;
        for(int i = 0; i<n_1.el.size();i++){
            n.el.push_back(2*n_1.el[i]-n_2.el[i]);
        }
        sum = 0;
        for(int i = 0; i<n.el.size();i++){
            sum += n.el[i];
        }
        n.sum = sum;
        PrognoseData.push_back(n);
        n_2=n_1;
        n_1=n;    
    }
    return;
}


//Funktione zur Ausgabe der Datenbank unter gewissen Auswahl ein eine Datei
void Database::storedata(string& filename, int beginn,int ende,int value_or_percent,vector<int>& spaltenauswahl){
    fstream my_file;
    my_file.open(filename, ios::out);
    if (!my_file) {
		throw runtime_error("Ausgabestream konnte nicht geöffnet werden");
	}

    my_file<< columns[0] <<";";
    for(int i = 0; i < spaltenauswahl.size(); i++)
    {
    my_file<<columns[spaltenauswahl[i]]<<";";
    }
    my_file << endl;
    for(int i = 0; i < Data.size(); i++)
    {
        if(Data[i].year >= beginn && Data[i].year <= ende){
            my_file << Data[i].year << "; ";
            for(int j = 0; j < spaltenauswahl.size(); j++){
                if(value_or_percent == VALUE){
                    my_file<<Data[i].el[spaltenauswahl[j]]<<";";
                } 
                else if(value_or_percent == PERCENT){
                    my_file<<((Data[i].el[spaltenauswahl[j]]/Data[i].sum)*100)<<";";
                }  
            }
            my_file << endl;
        }
    }

    my_file << endl << "Nun folgt noch die Prognose" <<endl;
    my_file<< columns[0] <<";";
    for(int i = 0; i < spaltenauswahl.size(); i++)
    {
    my_file<<columns[spaltenauswahl[i]]<<";";
    }
    my_file << endl;

    for(int i = 0; i < PrognoseData.size(); i++)
    {
        my_file<< PrognoseData[i].year << ";";
        for(int j = 0; j < spaltenauswahl.size(); j++){
            if(value_or_percent == VALUE){
                my_file<<PrognoseData[i].el[spaltenauswahl[j]]<<";";
            }
            else if(value_or_percent == PERCENT){
                my_file<<(100*PrognoseData[i].el[spaltenauswahl[j]]/PrognoseData[i].sum)<<";";
            }  
        }
        my_file << endl;
    }    
    my_file << endl;

    if(value_or_percent == VALUE){
        my_file << "Alle Angaben in Terajoule" << endl << endl;
    }
    else if(value_or_percent == PERCENT){
        my_file << "Alle Angaben % bezogen auf den jährlich Gesamtverbrauch" << endl << endl;;
    }

    my_file << "Quelle: Statistik Austria" << endl <<"https://statcube.at/statcube/opendatabase?id=deebilanz";

	my_file.close();  
    cout << endl << endl << "Data stored" << endl << endl;
}