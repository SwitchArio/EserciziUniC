#include "../include/PacchettoAvventura.h"
#include <iostream>
using namespace std;

PacchettoAvventura::PacchettoAvventura(
    string codice, string dest, int giorni, double prezzo, // Ereditati da Pacchetto viaggio
    vector<string> attivita, string livelloAdr, bool assicurazione // Particolari della classe Derivata
)
    : PacchettoViaggio(codice, dest, giorni, prezzo),
    attivita(attivita),
    livelloAdrenalina(livelloAdr),
    assicurazioneExtra(assicurazione)
{};

double PacchettoAvventura::calcolaPrezzoFinale() const {
    double prezzoFinale = prezzoBase;
    prezzoFinale =+ attivita.size()*80;
    if (livelloAdrenalina == "Alto") prezzoFinale *= 1.25; // 25% 
    else if (livelloAdrenalina == "Medio") prezzoFinale *= 1.15; // 15% 
    if(assicurazioneExtra) prezzoFinale += 100;
    return prezzoFinale;
};

void PacchettoAvventura::stampaDettagli() const {
    cout << "Codice pacchetto: " << codicePacchetto << endl;
    cout << "Destinazione: " << destinazione << endl;
    cout << "Durata (giorni): " << durataGiorni << endl;
    cout << "Prezzo base: " << prezzoBase << " EUR" << endl;

    cout << "Assicurazione inclusa: " << (assicurazioneExtra ? "Si'" : "No") << endl;
    cout << "Livello adrenalina: " << livelloAdrenalina << endl;
    cout << "Numero attivita': " << attivita.size() << endl;

    for (int i = 0; i<attivita.size(); i++) cout << i++ << ". " << attivita[i] << endl; 

    cout << "Prezzo finale: " << calcolaPrezzoFinale() << " EUR" << endl;
};

string PacchettoAvventura::getTipologia() const { return "Avventura"; };