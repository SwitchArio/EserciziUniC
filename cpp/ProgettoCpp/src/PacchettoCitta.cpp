#include "../include/PacchettoCitta.h"
#include <iostream>
using namespace std;

PacchettoCitta::PacchettoCitta(
    string codice, string dest, int giorni, double prezzo, 
    int numMusei, bool guida, string catHotel 
)
    : PacchettoViaggio(codice, dest, giorni, prezzo),
    numeroMusei(numMusei),
    guidaTuristica(guida),
    categoriaHotel(catHotel)
{};

double PacchettoCitta::calcolaPrezzoFinale() const {
    double prezzoFinale = prezzoBase + numeroMusei*15;
    if (guidaTuristica) prezzoFinale *= 1.1; // 10% 
    if (categoriaHotel == "5 stelle") prezzoFinale *= 1.3; // 30%
    else if (categoriaHotel == "4 stelle") prezzoFinale *= 1.15; // 15%
    return prezzoFinale;
};

void PacchettoCitta::stampaDettagli() const {
    cout << "Codice pacchetto: " << codicePacchetto << endl;
    cout << "Destinazione: " << destinazione << endl;
    cout << "Durata (giorni): " << durataGiorni << endl;
    cout << "Prezzo base: " << prezzoBase << " EUR" << endl;

    cout << "Ombrellone incluso: " << (guidaTuristica ? "Si'" : "No") << endl;
    cout << "Numero Musei: " << numeroMusei << endl;
    cout << "Categoria Hotel: " << categoriaHotel << endl;

    cout << "Prezzo finale: " << calcolaPrezzoFinale() << " EUR" << endl;
};

string PacchettoCitta::getTipologia() const { return "Citta"; };
