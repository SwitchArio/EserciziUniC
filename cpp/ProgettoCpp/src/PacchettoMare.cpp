#include "../include/PacchettoMare.h"
#include <iostream>
using namespace std;

PacchettoMare::PacchettoMare(
    string codice, string dest, int giorni, double prezzo, 
    bool ombrellone, string trattamento, bool attrezzatura
) 
    : PacchettoViaggio(codice, dest, giorni, prezzo),
    ombrelloneIncluso(ombrellone),
    tipoTrattamento(trattamento),
    attrezzaturaSportiva(attrezzatura)
{};

double PacchettoMare::calcolaPrezzoFinale() const { 
    double prezzoFinale = prezzoBase;
    if (ombrelloneIncluso) prezzoFinale += 100;
    if (tipoTrattamento == "Pensione completa") prezzoFinale += 200;
    else if (tipoTrattamento == "Mezza pensione") prezzoFinale += 100;
    if (attrezzaturaSportiva) prezzoFinale += 150;
    return prezzoFinale;
};

void PacchettoMare::stampaDettagli() const {
    cout << "Codice pacchetto: " << codicePacchetto << endl;
    cout << "Destinazione: " << destinazione << endl;
    cout << "Durata (giorni): " << durataGiorni << endl;
    cout << "Prezzo base: " << prezzoBase << " EUR" << endl;

    cout << "Ombrellone incluso: " << (ombrelloneIncluso ? "Si'" : "No") << endl;
    cout << "Trattamento: " << tipoTrattamento << endl;
    cout << "Attrezzatura sportiva inclusa: " << (attrezzaturaSportiva ? "Si'" : "No") << endl;

    cout << "Prezzo finale: " << calcolaPrezzoFinale() << " EUR" << endl;
}

string PacchettoMare::getTipologia() const { return "Mare"; };

string PacchettoMare::toString() const {
    return "Mare;" + codicePacchetto + ";" + destinazione + ";" +
           to_string(durataGiorni) + ";" +
           to_string(prezzoBase) + ";" +
           (disponibile ? "1" : "0") + ";" +
           (ombrelloneIncluso ? "1" : "0") + ";" +
           tipoTrattamento + ";" +
           (attrezzaturaSportiva ? "1" : "0");
}
