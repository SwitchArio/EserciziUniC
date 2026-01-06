#pragma once

#include "PacchettoViaggio.h" // include anche <string>
using namespace std;

class PacchettoCitta : public PacchettoViaggio {
private:
    int numeroMusei; // Numero di musei inclusi nel tour
    bool guidaTuristica; // true se include guida turistica
    string categoriaHotel; // "3 stelle", "4 stelle", "5 stelle"
public:
    double calcolaPrezzoFinale() const override;
    void stampaDettagli() const override;
    string getTipologia() const override;

    PacchettoCitta(const string& codice, const string& dest, int giorni, double prezzo, // Ereditati da Pacchetto viaggio
                   int numMusei, bool guida, const string& catHotel // Particolari della classe Derivata
                );
};
