#pragma once

#include "Cliente.h"
#include "PacchettoViaggio.h"
using namespace std;

class Prenotazione {
private:
    string codicePrenotazione; // Formato: "BKG-XXXX" (generato automaticamente)
    Cliente* cliente; // Puntatore al cliente
    PacchettoViaggio* pacchetto; // Puntatore al pacchetto (polimorfismo!) 
    int numeroPersone; // Numero di persone per la prenotazione
    string dataPrenotazione; // Formato: "gg/mm/aaaa"
    double prezzoTotale; // Calcolato automaticamente
    bool confermata; // true se confermata, false se in attesa

public:
    // Costruttore
    Prenotazione(string codice, Cliente* cli, PacchettoViaggio* pac, int numPersone, string data);
    // Getter
    string getCodicePrenotazione() const;
    Cliente* getCliente() const;
    PacchettoViaggio* getPacchetto() const;
    double getPrezzoTotale() const;
    bool isConfermata() const;

    // Calcola prezzo totale:
    // (pacchetto->calcolaPrezzoFinale() * numeroPersone) con sconto del cliente applicato
    void calcolaPrezzoTotale();
    void confermaPrenotazione();
    void stampaDettagli() const;
    ~Prenotazione() = default;
};