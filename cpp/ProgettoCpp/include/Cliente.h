#pragma once

#include <string>
using namespace std;

class Cliente {
private:
    string codiceCliente; // Formato: "CLT-XXXX"
    string nome;
    string cognome;
    string email;
    string telefono;
    int eta;
    string tipologiaCliente; // "Standard", "Premium", "VIP"

public:
    // Costruttore
    Cliente(string codice, string nome, string cognome, string email, string tel, int eta, string tipo);

    // Getter
    string getCodiceCliente() const;
    string getNomeCompleto() const; // Ritorna "Nome Cognome"
    int getEta() const;
    string getTipologiaCliente() const;

    // Metodo per applicare sconto in base alla tipologia
    double applicaSconto(double prezzoBase) const;

    // Standard: 0%, Premium: 10%, VIP: 20%
    void stampaInfo() const;

    string toString() const;

    ~Cliente() = default;
};