#pragma once

#include "PacchettoViaggio.h" // include anche <string>
using namespace std;

class PacchettoMare : public PacchettoViaggio {
private:
    bool ombrelloneIncluso; // true se include ombrellone+lettini
    string tipoTrattamento; // "Pensione completa", "Mezza pensione", "Solo colazione"
    bool attrezzaturaSportiva; // true se include attrezzatura per sport acquatici

public:
    double calcolaPrezzoFinale() const override;
    void stampaDettagli() const override;
    string getTipologia() const override;
    string toString() const override;

    PacchettoMare(string codice, string dest, int giorni, double prezzo, // Ereditati da Pacchetto viaggio
                   bool ombrellone, string trattamento, bool attrezzatura // Particolari della classe Derivata
                );
};
