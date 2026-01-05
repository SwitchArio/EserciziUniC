#pragma once

#include <string>
using namespace std;

class PacchettoViaggio
{
protected:
    string codicePacchetto; // Formato: "PKG-XXXX" (es: "PKG-0001")
    string destinazione; // Nome della città/località
    int durataGiorni; // Numero di giorni del viaggio
    double prezzoBase; // Prezzo base per persona
    bool disponibile; // true se prenotabile, false altrimenti

public:
    PacchettoViaggio(string codice, string dest, int giorni, double prezzo);
    virtual ~PacchettoViaggio(); // = default  //TODO: da considerare

    virtual double calcolaPrezzoFinale() const = 0;
    virtual void stampaDettagli() const = 0;
    virtual string getTipologia() const = 0;

    string getCodicePacchetto() const;
    string getDestinazione() const;
    int getDurataGiorni() const;
    double getPrezzoBase() const;
    bool isDisponibile() const;
    void setDisponibile(bool disp);
};