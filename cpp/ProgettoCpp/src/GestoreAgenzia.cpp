#include "../include/GestoreAgenzia.h"
#include "../include/PacchettoMare.h"
#include "../include/PacchettoMontagna.h"
#include "../include/PacchettoCitta.h"
#include "../include/PacchettoAvventura.h"
#include <iostream>
#include <fstream>
using namespace std;

GestoreAgenzia::GestoreAgenzia() { 
    prossimoCodicePacchetto = 1;
    prossimoCodiceCliente = 1;
    prossimoCodicePrenotazione = 1;
}
GestoreAgenzia::~GestoreAgenzia() {};

// === GESTIONE PACCHETTI ===
void GestoreAgenzia::aggiungiPacchettoManuale() {
    cout << "Che pacchetto vuoi inserire?\n1. Mare\n2. Citta'\n3. Montagna\n4. Avventura";
    int scelta; cin >> scelta;
    if (scelta  < 0 || scelta > 4) { cout << "scelta non valida"; return; }    
    
    string codicePacchetto = generaCodiceUnico('P');
    string destinazione; int durataGiorni; double prezzoBase;
    cout << "Inserisci la destinazione: "; cin >> destinazione;
    cout << "Inserisci la durata (giorni): "; cin >> durataGiorni;
    cout << "Inserisci il prezzo base: "; cin >> prezzoBase;

    switch (scelta)
    {
    case 1: {       
        bool ombrelloneIncluso;
        cout << "Inserisci se l'ombrellone e' incluso (1=si,0=no) : ";
        cin >> ombrelloneIncluso;

        string tipoTrattamento = "";
        while (tipoTrattamento != "Pensione completa" && tipoTrattamento != "Mezza pensione" && tipoTrattamento != "Solo colazione")
        {
            cout << "I trattamenti disponibili sono: 'Pensione completa', 'Mezza pensione', 'Solo colazione'" << endl;
            cout << "Inserisci il tipo di trattamento : ";
            getline(cin >> ws, tipoTrattamento);
        }
        
        bool attrezzaturaSportiva;
        cout << "Inserisci se l'attrezzatura sportiva e' inclusa (1=si,0=no) : ";
        cin >> attrezzaturaSportiva;
        
        auto p = make_unique<PacchettoMare>(
            codicePacchetto,
            destinazione,
            durataGiorni,
            prezzoBase,
            ombrelloneIncluso,
            tipoTrattamento,
            attrezzaturaSportiva
        );
        catalogo.push_back(move(p));
        break;
    }
    case 2: {
        int numeroMusei = -1;
        while (numeroMusei < 0)
        {
            cout << "Inserisci il numero di musei : " << endl;
            cout << "Il numero deve essere un intero positivo";
            cin >> numeroMusei;
        }

        bool guidaTuristica; 
        cout << "Inserisci se la guida turistica e' inclusa (1=si,0=no) : ";
        cin >> guidaTuristica;

        string categoriaHotel; 
        while (categoriaHotel != "3 stelle" && categoriaHotel != "4 stelle" && categoriaHotel != "5 stelle")
        {
            cout << "Le categorie disponibili sono: '3 stelle', '4 stelle', '5 stelle'" << endl;
            cout << "Inserisci la categoria dell'Hotel : ";
            getline(cin >> ws, categoriaHotel);
        }

        auto p = make_unique<PacchettoCitta>(
            codicePacchetto,
            destinazione,
            durataGiorni,
            prezzoBase, 
            numeroMusei,
            guidaTuristica,
            categoriaHotel
        );
        catalogo.push_back(move(p));
        break;
    }
    case 3: {
        int numeroEscursioni = -1;
        while (numeroEscursioni < 0)
        {
            cout << "Inserisci il numero di escursioni : " << endl;
            cout << "Il numero deve essere un intero positivo";
            cin >> numeroEscursioni;
        }

        bool skipassIncluso; 
        cout << "Inserisci se lo skipass e' incluso (1=si,0=no) : ";
        cin >> skipassIncluso;

        string difficolta; 
        while (difficolta != "Facile" && difficolta != "Media" && difficolta != "Difficile")
        {
            cout << "Le difficolta' disponibili sono: 'Facile', 'Media', 'Difficile'" << endl;
            cout << "Inserisci la difficolta' delle escursioni' : ";
            getline(cin >> ws, difficolta);
        }

        auto p = make_unique<PacchettoMontagna>(
            codicePacchetto,
            destinazione,
            durataGiorni,
            prezzoBase, 
            skipassIncluso, 
            numeroEscursioni,
            difficolta
        );
        catalogo.push_back(move(p));
        break;
    }
    case 4: {
        vector<string> attivita;
        string keepAsking = "s";
        while (keepAsking == "s")
        {
            string a = ""; 
            while (a.length() > 1)
            {
                cout << "Inserisci il nome di un'attivita': " << endl;
                cout << "Il nome dell'attivita' deve avere almeno 2 caratteri";
                getline(cin >> ws, a);
            }
            attivita.push_back(a);
            cout << "Vuoi inserire un'altra attivita'? (s/n) " << endl;
            getline(cin >> ws, keepAsking);
        }

        bool assicurazioneExtra; 
        cout << "Inserisci se l'assicurazione e' inclusa (1=si,0=no) : ";
        cin >> assicurazioneExtra;

        string livelloAdrenalina; 
        while (livelloAdrenalina != "Basso" && livelloAdrenalina != "Medio" && livelloAdrenalina != "Alto")
        {
            cout << "I livelli di adrenalina disponibili sono: 'Basso', 'Medio', 'Alto'" << endl;
            cout << "Inserisci l'adrenalina: ";
            getline(cin >> ws, livelloAdrenalina);
        }

        auto p = make_unique<PacchettoAvventura>(
            codicePacchetto,
            destinazione,
            durataGiorni,
            prezzoBase, 
            attivita,
            livelloAdrenalina,
            assicurazioneExtra
            
        );
        catalogo.push_back(move(p));
        break;
    }
    }
};

unique_ptr<PacchettoViaggio> GestoreAgenzia::cercaPacchetto(string codice) {
    for (auto& pacchetto : catalogo) 
        if (pacchetto->getCodicePacchetto() == codice) 
            return move(pacchetto);
    return nullptr;
}

void GestoreAgenzia::visualizzaCatalogo() const {
    if (catalogo.size() <= 0) { cout << "Catalogo vuoto!" <<  endl; return; }
    for (auto& pacchetto : catalogo) pacchetto->stampaDettagli();
};

void GestoreAgenzia::visualizzaPacchettiPerTipologia(string tipo) const {
    if (catalogo.size() <= 0) { cout << "Catalogo vuoto!" <<  endl; return; }
    for (auto& pacchetto : catalogo) if(pacchetto->getTipologia() == tipo) pacchetto->stampaDettagli();
};

void GestoreAgenzia::visualizzaPacchettiDisponibili() const {
    if (catalogo.size() <= 0) { cout << "Catalogo vuoto!" <<  endl; return; }
    for (auto& pacchetto : catalogo) if(pacchetto->isDisponibile()) pacchetto->stampaDettagli();
};


// === GESTIONE FILE ===
void GestoreAgenzia::salvaDatiSuFile(const string& nomefile) const {
    ofstream file(nomefile);
    if (!file) { cout << "Errore nell'inizializzazione del file"; return; }

    file << "===CATALOGO===\n";
    file << "TIPO;CODICE;DESTINAZIONE;GIORNI;PREZZO;DISPONIBILE;CAMPI_SPECIFICI\n";
    for (auto& pacchetto : catalogo) file << pacchetto->toString() << "\n";
    
    file << "===CLIENTI===\n";
    file << "CODICE;NOME;COGNOME;EMAIL;TELEFONO;ETA;TIPOLOGIA\n";
    for (auto& cliente : clienti) file << cliente->toString() << "\n";

    file << "===PRENOTAZIONI===\n";
    file << "CODICE;COD_CLIENTE;COD_PACCHETTO;NUM_PERSONE;DATA;CONFERMATA\n";
    for (auto& prenotazione : prenotazioni) file << prenotazione->toString() << "\n";
    file.close();

};

void GestoreAgenzia::caricaDatiDaFile(const string& nomefile) {

};

// 'P' per pacchetti, 'C' per clienti, 'B' per prenotazioni
string GestoreAgenzia::generaCodiceUnico(char tipo) {
    if (tipo == 'P') 
        return "PKG-" 
        + string(4 - to_string(prossimoCodicePacchetto).length(), '0') 
        + to_string(prossimoCodicePacchetto++);
    if (tipo == 'C') 
        return "";
    return "";
};