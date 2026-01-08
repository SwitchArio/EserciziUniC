#include "../include/Cliente.h"
#include <iostream>
using namespace std;

Cliente::Cliente(
    string codice, string nome, string cognome, 
    string email, string tel, int eta, string tipo
) 
    : codiceCliente(codice),
    nome(nome),
    cognome(cognome),
    email(email),
    telefono(tel),
    eta(eta),
    tipologiaCliente(tipo)
{};

string Cliente::getCodiceCliente() const { return codiceCliente; };
string Cliente::getNomeCompleto() const { return nome + " " + cognome; };
int Cliente::getEta() const { return eta; };
string Cliente::getTipologiaCliente() const { return tipologiaCliente; };

double Cliente::applicaSconto(double prezzoBase) const { 
    if ( tipologiaCliente == "Premium" ) return prezzoBase*0.9;
    if ( tipologiaCliente == "VIP" ) return prezzoBase*0.8;
    return prezzoBase;
};

void Cliente::stampaInfo() const {
    cout << "Codice cliente: " << codiceCliente << endl;
    cout << "Nome: " << nome << endl;
    cout << "Cognome: " << cognome << endl;
    cout << "Email: " << email << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Eta: " << eta << endl;
    cout << "Tipologia cliente: " << tipologiaCliente << endl;
};