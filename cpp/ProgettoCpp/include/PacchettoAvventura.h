#pragma once

#include "PacchettoViaggio.h" // include anche <string>
#include <vector>
using namespace std;

class PacchettoAvventura : public PacchettoViaggio {
private:
    vector<string> attivita; // Lista attività (es: "Rafting", "Arrampicata", "Parapendio")
    string livelloAdrenalina; // "Basso", "Medio", "Alto"
    bool assicurazioneExtra; // true se include assicurazione extra

public:
    double calcolaPrezzoFinale() const override;
    void stampaDettagli() const override;
    string getTipologia() const override;

    PacchettoAvventura(string codice, string dest, int giorni, double prezzo, // Ereditati da Pacchetto viaggio
                      vector<string> attivita, string livelloAdr, bool assicurazione // Particolari della classe Derivata
                    );
};

