#pragma once

#include "PacchettoViaggio.h" // include anche <string>
using namespace std;

class PacchettoMontagna : public PacchettoViaggio {
private:
    bool skipassIncluso; // true se include skipass
    int numeroEscursioni; // Numero di escursioni guidate incluse
    string difficolta; // "Facile", "Media", "Difficile"

public:
    double calcolaPrezzoFinale() const override;
    void stampaDettagli() const override;
    string getTipologia() const override;

    PacchettoMontagna(string codice, string dest, int giorni, double prezzo, // Ereditati da Pacchetto viaggio
                      bool skipass, int numEscursioni, string difficolta // Particolari della classe Derivata
                    );
};

