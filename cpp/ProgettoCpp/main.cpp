#include "include/GestoreAgenzia.h"
#include <iostream>
/* 
cd "C:\Users\arand\Desktop\Progetti Coding\Programmazione in C\Esercizi\cpp\ProgettoCpp"
g++ main.cpp (Get-ChildItem ./src -Filter *.cpp | ForEach-Object { $_.FullName }) -I ./include -o main.exe -mconsole
.\main.exe
*/

using namespace std;

int main() {
    GestoreAgenzia gestore;

    while (true) {
        cout << "\n= SISTEMA GESTIONE AGENZIA VIAGGI =\n\n";
        cout << "=== GESTIONE CATALOGO PACCHETTI ===\n";
        cout << "1. Aggiungi nuovo pacchetto\n";
        cout << "2. Visualizza tutti i pacchetti\n";
        cout << "3. Cerca pacchetto per codice\n";
        cout << "4. Visualizza pacchetti per tipologia\n";
        cout << "5. Visualizza solo pacchetti disponibili\n\n";

        cout << "--- GESTIONE CLIENTI ---\n";
        cout << "6. Registra nuovo cliente\n";
        cout << "7. Visualizza tutti i clienti\n";
        cout << "8. Cerca cliente per codice\n";
        cout << "9. Visualizza clienti per tipologia\n\n";

        cout << "--- GESTIONE PRENOTAZIONI ---\n";
        cout << "10. Crea nuova prenotazione\n";
        cout << "11. Conferma prenotazione\n";
        cout << "12. Visualizza tutte le prenotazioni\n";
        cout << "13. Visualizza prenotazioni di un cliente\n";
        cout << "14. Visualizza prenotazioni confermate\n\n";

        cout << "--- STATISTICHE E REPORT ---\n";
        cout << "15. Statistiche generali\n";
        cout << "16. Statistiche per tipologia pacchetto\n";
        cout << "17. Trova cliente migliore (maggior spesa)\n";
        cout << "18. Report destinazioni più popolari\n\n";

        cout << "--- GESTIONE FILE ---\n";
        cout << "19. Salva dati su file\n";
        cout << "20. Carica dati da file\n\n";

        cout << "21. Esci\n\n";
        cout << "Seleziona un'opzione: ";

        int scelta = 0; cin >> scelta;

        switch (scelta) {
            // CATALOGO
            case 1:
                gestore.aggiungiPacchettoManuale();
                break;
            case 2:
                gestore.visualizzaCatalogo();
                break;
            case 3: {
                cout << "Inserisci codice pacchetto: ";
                string codice; getline(cin, codice);
                auto p = gestore.cercaPacchetto(codice);
                if (p) p->stampaDettagli();
                else cout << "Pacchetto non trovato.\n";
                break;
            }
            case 4: {
                cout << "Inserisci tipologia (CITTA/MARE/MONTAGNA/AVVENTURA): ";
                string tipo; getline(cin, tipo);
                gestore.visualizzaPacchettiPerTipologia(tipo);
                break;
            }
            case 5:
                gestore.visualizzaPacchettiDisponibili();
                break;

            // FILE
            case 19: {
                cout << "Nome file per salvataggio (es. file.txt): ";
                string nome; getline(cin, nome);
                // esempio: salva tre file con nome come nome + "pacchetti.txt"
                gestore.salvaDatiSuFile(nome);
                break;
            }
            case 20: {
                cout << "Nome file per caricamento (es. file.txt): ";
                string nome; getline(cin, nome);
                gestore.caricaDatiDaFile(nome);
                break;
            }

            // ESCI
            case 21:
                cout << "Uscita. Salva prima di chiudere se necessario.\n";
                return 0;

            default:
                cout << "Opzione non valida.\n";
                break;
        } // fine switch
    } // fine while

    return 0;
}