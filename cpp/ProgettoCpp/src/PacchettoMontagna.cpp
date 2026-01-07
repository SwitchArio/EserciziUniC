#include "../include/PacchettoMontagna.h"
#include <iostream>
using namespace std;

PacchettoMontagna::PacchettoMontagna(
    string codice, string dest, int giorni, double prezzo, // Ereditati da Pacchetto viaggio
    bool skipass, int numEscursioni, string difficolta // Particolari della classe Derivata
)
    : PacchettoViaggio(codice, dest, giorni, prezzo),
    skipassIncluso(skipass),
    numeroEscursioni(numEscursioni),
    difficolta(difficolta)
{};

double PacchettoMontagna::calcolaPrezzoFinale() const {
    double prezzoFinale = prezzoBase;
    if (skipassIncluso) prezzoFinale =+ 45*durataGiorni;
    prezzoFinale += numeroEscursioni*30; 
    if (difficolta == "Difficile") prezzoFinale *= 1.2; // 20% sul totale
    return prezzoFinale;
};

void PacchettoMontagna::stampaDettagli() const {
    cout << "Codice pacchetto: " << codicePacchetto << endl;
    cout << "Destinazione: " << destinazione << endl;
    cout << "Durata (giorni): " << durataGiorni << endl;
    cout << "Prezzo base: " << prezzoBase << " EUR" << endl;

    cout << "Skipass incluso: " << (skipassIncluso ? "Si'" : "No") << endl;
    cout << "Numero Escursioni: " << numeroEscursioni << endl;
    cout << "Difficolta': " << difficolta << endl;

    cout << "Prezzo finale: " << calcolaPrezzoFinale() << " EUR" << endl;
};

string PacchettoMontagna::getTipologia() const { return "Montagna"; };