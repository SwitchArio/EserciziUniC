#pragma once

#include "Utils.h"
#include "Prenotazione.h" // Contiene Cliente, Pacchetto e String
using namespace std;

class GestoreAgenzia {
private: 
    vector<unique_ptr<PacchettoViaggio>> catalogo; // Tutti i pacchetti disponibili (Polimorfismo)
    vector<unique_ptr<Cliente>> clienti; // Tutti i clienti registrati
    vector<unique_ptr<Prenotazione>> prenotazioni; // Tutte le prenotazioni
    int prossimoCodicePacchetto; // Per generare codici univoci
    int prossimoCodiceCliente; // Per generare codici univoci
    int prossimoCodicePrenotazione; // Per generare codici univoci

public:
    // Costruttore e Distruttore
    GestoreAgenzia();
    ~GestoreAgenzia(); // Deve liberare TUTTA la memoria allocata!

    // === GESTIONE PACCHETTI ===
    void aggiungiPacchettoManuale(); // Chiede dati da tastiera
    unique_ptr<PacchettoViaggio> cercaPacchetto(string codice);
    void visualizzaCatalogo() const;
    void visualizzaPacchettiPerTipologia(string tipo) const;
    void visualizzaPacchettiDisponibili() const;
    
    // === GESTIONE CLIENTI ===
    void aggiungiCliente();
    unique_ptr<Cliente> cercaCliente(string codice);
    void visualizzaClienti() const;
    void visualizzaClientiPerTipologia(string tipo) const;

    // === GESTIONE PRENOTAZIONI ===
    void creaPrenotazione(); // Chiede codice cliente e codice pacchetto
    void confermaPrenotazione(string codicePrenotazione);
    void visualizzaPrenotazioni() const;
    void visualizzaPrenotazioniCliente(string codiceCliente) const;
    void visualizzaPrenotazioniConfermate() const;
    // === STATISTICHE ===
    void statisticheGenerali() const;
    // - Numero totale pacchetti
    // - Numero totale clienti
    // - Numero totale prenotazioni
    // - Fatturato totale
    // - Pacchetto più prenotato
    // - Destinazione più popolare

    void statistichePerTipologia() const;
    // Conteggio prenotazioni per ogni tipo di pacchetto

    unique_ptr<Cliente> clienteMigliore() const;
    // Cliente con maggior spesa totale

    // === GESTIONE FILE ===
    void salvaDatiSuFile(const string& nomefile) const;
    void caricaDatiDaFile(const string& nomefile);
    // Usa formato testo (CSV o simile) per semplicità

    // === UTILITY ===
    string generaCodiceUnico(char tipo);
    // 'P' per pacchetti, 'C' per clienti, 'B' per prenotazioni

};
