#include "../include/Prenotazione.h"
#include <iostream>
using namespace std;

Prenotazione::Prenotazione(
    string codice, Cliente* cli, PacchettoViaggio* pac, 
    int numPersone, string data
) 
    : codicePrenotazione(codice),
    cliente(cli),
    pacchetto(pac),
    numeroPersone(numPersone),
    dataPrenotazione(data),
    confermata(false),
    prezzoTotale(0)
{ calcolaPrezzoTotale(); };

string Prenotazione::getCodicePrenotazione() const { return codicePrenotazione; };
Cliente* Prenotazione::getCliente() const { return cliente; };
PacchettoViaggio* Prenotazione::getPacchetto() const { return pacchetto; };

double Prenotazione::getPrezzoTotale() const { return prezzoTotale; };
bool Prenotazione::isConfermata() const { return confermata; };

void Prenotazione::calcolaPrezzoTotale() {
    prezzoTotale = cliente->applicaSconto(pacchetto->calcolaPrezzoFinale()* numeroPersone);
}

void Prenotazione::confermaPrenotazione() { confermata = true; };
void Prenotazione::stampaDettagli() const { 
    cout << "Codice prenotazione: " << codicePrenotazione << endl;
    
    if (cliente != nullptr) {
        cout << "--- Cliente ---" << endl;
        cliente->stampaInfo();
        cout << "--- --- --- ---" << endl;
    } else {
        cout << "Cliente: non assegnato" << endl;
    }

    if (pacchetto != nullptr) {
        cout << "--- Pacchetto ---" << endl;
        pacchetto->stampaDettagli(); // Polimorfismo
        cout << "---  ---  --- ---" << endl;
    } else {
        cout << "Pacchetto: non assegnato" << endl;
    }

    cout << "Numero persone: " << numeroPersone << endl;
    cout << "Data prenotazione: " << dataPrenotazione << endl;
    cout << "Prezzo totale: " << prezzoTotale << endl;
    cout << "Stato conferma: " << (confermata ? "Confermata" : "In attesa") << endl;

};

string Prenotazione::toString() const {
    return codicePrenotazione + ";" + cliente->getCodiceCliente() 
    + ";" + pacchetto->getCodicePacchetto() 
    + ";" + to_string(numeroPersone) 
    + ";" + dataPrenotazione 
    + ";" + to_string(prezzoTotale) 
    + ";" +  (confermata ? "1" : "0");
}