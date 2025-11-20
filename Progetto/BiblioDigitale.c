#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char path[] = "C:\\Users\\arand\\Desktop\\Progetti Coding\\Programmazione in C\\Esercizi\\Progetto\\";

// =========================================================
// STRUTTURE DATI
// =========================================================

typedef struct {
    char ISBN[18];
    char titolo[100];
    char autore[50];
    int anno_pubblicazione;
    int numero_copie;
    char genere[30];
} Libro;

typedef struct {
    int codice_utente;
    char nome[50];
    char cognome[50];
    char email[80];
    char data_iscrizione[15];
} Utente;

typedef struct {
    int codice_prestito;
    char codice_ISBN_libro[20];
    int codice_utente;
    char data_prestito[15];
    char data_restituzione_prevista[15];
    int restituito; // 0 = no, 1 = sì
} Prestito;

// =========================================================
// DATABASE DINAMICI
// =========================================================

Libro *dbLibri = NULL;
Utente *dbUtenti = NULL;
Prestito *dbPrestiti = NULL;

int maxLibri = 0, maxUtenti = 0, maxPrestiti = 0;
int countLibri = 0, countUtenti = 0, countPrestiti = 0;

int dbCaricato = 0;

// =========================================================
// PROTOTIPI
// =========================================================

// Menu
void mostraMenu();

// Gestione Libri
void inserisciLibro();
void stampaLibro(Libro l);
void visualizzaLibri();
int cercaLibroISBN(char *isbn);

// Gestione Utenti
void inserisciUtente();
void stampaUtente(Utente u);
void visualizzaUtenti();
int cercaUtenteDaCodice(int codice);

// Gestione Prestiti
void creaPrestito();
void restituisciLibro();
void visualizzaPrestitiAttivi();
void generaDataRestituzione(char *data, char *dataRestituzione);

// File Binario
void salvaDB();
void caricaDB();

// Utils
int initDB();
int validaData(char *data);
int validaEmail(char *mail);
char* newStrCat(const char* str1, const char* str2);
int dataToInt(char *data);
char* intToData(int data);
int myPow(int a, int b);
int strToInt(char a);


// =========================================================
// MAIN
// =========================================================

int main() {
    int scelta;

    // chiede capacità e alloca
    if (initDB() == -1) { printf("Avvio fallito"); return 1; }; 

    do {
        mostraMenu();
        scanf("%d", &scelta);
        printf("\n\n\n\n\n");

        switch (scelta) {
            case 1: inserisciLibro(); break;
            case 2: visualizzaLibri(); break;
            case 3: {
                char isbn[20];
                printf("Inserisci ISBN (formato XXX-X-XXXX-XXXX-X): ");
                scanf("%s", isbn);
                int idx = cercaLibroISBN(isbn);
                if (idx >= 0) stampaLibro(dbLibri[idx]);
                else printf("Libro non trovato.\n");
            } break;

            case 6: inserisciUtente(); break;
            case 7: visualizzaUtenti(); break;
            case 8: {
                int codice_utente;
                printf("Inserisci codice utente: ");
                scanf("%d", &codice_utente);
                int idx = cercaUtenteDaCodice(codice_utente);
                if (idx >= 0) stampaUtente(dbUtenti[idx]);
                else printf("Utente non trovato.\n");
            } break;

            case 9: creaPrestito(); break;
            case 10: restituisciLibro(); break;
            case 11: visualizzaPrestitiAttivi(); break;

            case 16: salvaDB(); break;
            case 17: caricaDB(); break;
        }

        

    } while (scelta != 20);

    // deallocazione
    for (int i = 0; i < countLibri; i++) free(dbLibri+i);
    for (int i = 0; i < countUtenti; i++) free(dbUtenti+i);
    for (int i = 0; i < countPrestiti; i++) free(dbPrestiti+i);
    //free(dbLibri);
    //free(dbUtenti);
    //free(dbPrestiti);

    return 0;
}


// =========================================================
// INIZIALIZZAZIONE DATABASE
// =========================================================

int initDB() {
    printf("Capacita' massima libri: ");
    scanf("%d", &maxLibri);

    printf("Capacita' massima utenti: ");
    scanf("%d", &maxUtenti);

    printf("Capacita' massima prestiti: ");
    scanf("%d", &maxPrestiti);

    dbLibri = malloc(sizeof(Libro) * maxLibri);
    dbUtenti = malloc(sizeof(Utente) * maxUtenti);
    dbPrestiti = malloc(sizeof(Prestito) * maxPrestiti);

    if (!dbLibri || !dbUtenti || !dbPrestiti) {
        printf("Errore allocazione memoria.\n");
        return -1;
    }

    printf("Database inizializzato.\n\n");
    //dbCaricato = 0;
}

void mostraMenu() {
    printf("=== MENU PRINCIPALE ===\n");
    printf("1. Inserisci nuovo libro\n");
    printf("2. Visualizza libri\n");
    printf("3. Cerca libro per ISBN\n");
    printf("6. Inserisci nuovo utente\n");
    printf("7. Visualizza utenti\n");
    printf("8. Cerca utente per codice\n");
    printf("9. Registra prestito\n");
    printf("10. Registra restituzione\n");
    printf("11. Prestiti attivi\n");
    printf("16. Salva database (bin)\n");
    printf("17. Carica database (bin)\n");
    printf("20. Esci\n");
    printf("Scelta: ");
}

// =========================================================
// GESTIONE LIBRI
// =========================================================

void inserisciLibro() {
    if (countLibri >= maxLibri) { printf("Database libri pieno.\n"); return; }

    Libro l;
    printf("ISBN (formato XXX-X-XXXX-XXXX-X): "); scanf("%s", l.ISBN);

    // unicità
    if (cercaLibroISBN(l.ISBN) == 0) {
        printf("ISBN già presente.\n");
        return;
    }

    
    printf("Titolo: "); scanf(" %[^\n]", l.titolo);
    printf("Autore: "); scanf(" %[^\n]", l.autore);
    
    do
    {
        printf("L'anno di pubblicazione deve essere nell'intervallo 1800-2025.\n");
        printf("Anno: "); scanf("%d", &l.anno_pubblicazione);
    } while (l.anno_pubblicazione < 1800 || l.anno_pubblicazione > 2025);

    do
    {
        printf("Il numero di copie deve essere un intero positivo.\n"); 
        printf("Copie: "); scanf("%d", &l.numero_copie);
    } while (l.numero_copie < 0);
    
    printf("Genere: "); scanf("%s", l.genere);

    dbLibri[countLibri++] = l;

}

void stampaLibro(Libro l) {
    printf("ISBN: %s\nTitolo: %s\nAutore: %s\nAnno: %d\nCopie: %d\nGenere: %s\n",
           l.ISBN, l.titolo, l.autore, l.anno_pubblicazione, l.numero_copie, l.genere);
    printf("--------------------------------\n");
}

void visualizzaLibri() {
    if (countLibri <= 0)
    {
        printf("Non sono stati inseriti libri nella libreria.\n");
        return;
    }
    
    for (int i = 0; i < countLibri; i++) stampaLibro(dbLibri[i]);
}

int cercaLibroISBN(char *ISBN) {
    for (int i = 0; i < countLibri; i++)
        if (strcmp(dbLibri[i].ISBN, ISBN) == 0)
            return i;
    return -1;
}


// =========================================================
// GESTIONE UTENTI
// =========================================================

void inserisciUtente() {
    if (countUtenti >= maxUtenti) { printf("Database utenti pieno.\n"); return; }

    Utente u;
    printf("Codice utente: ");
    scanf("%d", &u.codice_utente);

    if (cercaUtenteDaCodice(u.codice_utente) >= 0) {
        printf("Codice già presente.\n");
        return;
    }

    printf("Nome: "); scanf("%s", u.nome);
    printf("Cognome: "); scanf("%s", u.cognome);
    printf("Email: "); scanf("%s", u.email);
    while (validaEmail(u.email) == -1) { 
        printf("Email non valida, deve essere presente il carattere '@'\nInserisci una email valida: "); 
        scanf("%s", u.email);
    }

    printf("Data iscrizione: "); scanf("%s", u.data_iscrizione);
    while (validaData(u.data_iscrizione) == -1) {
        printf("Data non valida\nInserisci una data valida: "); 
        scanf("%s", u.data_iscrizione);
    }

    dbUtenti[countUtenti++] = u;    
}

void stampaUtente(Utente u) {
    printf("Codice: %d\nNome: %s\nCognome: %s\nEmail: %s\nData: %s\n",
           u.codice_utente, u.nome, u.cognome, u.email, u.data_iscrizione);
    printf("--------------------------------\n");
}

void visualizzaUtenti() {
    for (int i = 0; i < countUtenti; i++) stampaUtente(dbUtenti[i]);
}

int cercaUtenteDaCodice(int codice) {
    for (int i = 0; i < countUtenti; i++)
        if (dbUtenti[i].codice_utente == codice)
            return i;
    return -1;
}


// =========================================================
// GESTIONE PRESTITI 
// =========================================================

void creaPrestito() {
    if (countPrestiti >= maxPrestiti) { printf("Database prestiti pieno.\n"); return; }

    char isbn[20];
    int codice_utente;

    printf("ISBN libro: "); scanf("%s", isbn);

    int indiceLibro = cercaLibroISBN(isbn);
    if (indiceLibro < 0 || dbLibri[indiceLibro].numero_copie <= 0) { printf("Libro non disponibile.\n"); return; }

    if (countUtenti == 0) {printf("Nessun utente registrato"); return;}
    
    printf("Codice utente: "); scanf("%d", &codice_utente);

    int indiceUtente = cercaUtenteDaCodice(codice_utente);
    if (indiceUtente < 0) { printf("Utente inesistente.\n"); return; }

    Prestito p;
    p.codice_prestito = countPrestiti + 1;
    strcpy(p.codice_ISBN_libro, isbn);
    p.codice_utente = codice_utente;
    printf("Data prestito: "); scanf("%s", p.data_prestito);
    while (validaData(p.data_prestito) == -1) {
        printf("Data non valida\n Inserisci una data valida: "); 
        scanf("%s", p.data_prestito);
    }
    char restituzione[11];
    generaDataRestituzione(p.data_prestito, restituzione);
    strcpy(p.data_restituzione_prevista, restituzione);
    p.restituito = 0;

    dbPrestiti[countPrestiti++] = p;
    dbLibri[indiceLibro].numero_copie--;
}

void generaDataRestituzione(char *data, char* dataRestituzione) {
    int oldData = dataToInt(data);
    // 12345678
    int day = oldData%100;
    int month = oldData/100%100;
    int year = oldData/10000;

    int ggXmm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    day = (day+30)%ggXmm[month - 1];
    month = month + (day+30)/ggXmm[month - 1];
    year = year + (month+12)%12;

    int newData = day+month*100+year*10000;
    char* newDataStr = intToData(newData);
    strcpy(dataRestituzione, newDataStr);
}

int myPow(int a, int b) {
    int toReturn = 1;
    for (int i = 0; i < b; i++) toReturn *= a;
    return toReturn;
}

void restituisciLibro() {
    int codice;
    printf("Codice prestito: ");
    scanf("%d", &codice);
    
    for (int i = 0; i < countPrestiti; i++) {
        if (dbPrestiti[i].codice_prestito == codice) {
            if (dbPrestiti[i].restituito == 1) {
                printf("Gia' restituito.\n");
                return;
            }

            dbPrestiti[i].restituito = 1;
            
            int IL = cercaLibroISBN(dbPrestiti[i].codice_ISBN_libro);
            if (IL >= 0) dbLibri[IL].numero_copie++;
            
            printf("Restituito.\n");
            return;
        }
    }

    printf("Prestito non trovato.\n");
}

void visualizzaPrestitiAttivi() {
    for (int i = 0; i < countPrestiti; i++) {
        if (dbPrestiti[i].restituito == 0) {
            printf("Prestito %d | ISBN %s | Utente %d\n",
                   dbPrestiti[i].codice_prestito,
                   dbPrestiti[i].codice_ISBN_libro,
                   dbPrestiti[i].codice_utente);
                }
    }
}

// =========================================================
// FILE BINARI
// =========================================================

void salvaDB() {
    char* file1 = newStrCat(path, "libri.bin");
    char* file2 = newStrCat(path, "utenti.bin");
    char* file3 = newStrCat(path, "prestiti.bin");

    //LIBRI
    FILE *fp = fopen(file1, "wb");
    if (!fp) { printf("Errore file libri.\n"); return; }
    fwrite(&countLibri, sizeof(int), 1, fp);
    fwrite(dbLibri, sizeof(Libro), countLibri, fp);
    fclose(fp);
    
    // UTENTI
    fp = fopen(file2, "wb");
    if (!fp) { printf("Errore file utenti.\n"); return; }
    fwrite(&countUtenti, sizeof(int), 1, fp);
    fwrite(dbUtenti, sizeof(Utente), countUtenti, fp);
    fclose(fp);
    
    // PRESTITI
    fp = fopen(file3, "wb");
    if (!fp) { printf("Errore file prestiti.\n"); return; }
    fwrite(&countPrestiti, sizeof(int), 1, fp);
    fwrite(dbPrestiti, sizeof(Prestito), countPrestiti, fp);
    fclose(fp);
    
    printf("Database salvato.\n");
}

void caricaDB() {
    char* file1 = newStrCat(path, "libri.bin");
    char* file2 = newStrCat(path, "utenti.bin");
    char* file3 = newStrCat(path, "prestiti.bin");

    FILE *fp;
    // LIBRI
    fp = fopen(file1, "rb");
    if (fp) {
        fread(&countLibri, sizeof(int), 1, fp);
        fread(dbLibri, sizeof(Libro), countLibri, fp);
        fclose(fp);
    }
    // UTENTI
    fp = fopen(file2, "rb");
    if (fp) {
        fread(&countUtenti, sizeof(int), 1, fp);
        fread(dbUtenti, sizeof(Utente), countUtenti, fp);
        fclose(fp);
    }
    // PRESTITI
    fp = fopen(file3, "rb");
    if (fp) {
        fread(&countPrestiti, sizeof(int), 1, fp);
        fread(dbPrestiti, sizeof(Prestito), countPrestiti, fp);
        fclose(fp);
    }
    
    printf("Database caricato.\n");
}

// =========================================================
// ULITI
// =========================================================

int validaData(char *data) {
    if(strlen(data) != 10) return -1;
    if(data[2] != '/' || data[5] != '/') return -1;
    int intData = dataToInt(data);
    int day = intData%100, month = intData/100%100, year = intData/10000;
    printf("===\nDEBUG: intData %d, day %d, month %d, year %d\n===\n", intData, day, month, year);
    if (day > 30 || day < 0 || month > 12 || month < 0 || year > 2025 || year < 1800) 
        return -1;
    return 1;
};

int validaEmail(char *mail) {
    for (int i = 0; i < strlen(mail); i++)
        if ('@' == mail[i]) return 1;
    return -1;
};

char* newStrCat(const char* str1, const char* str2) {
    char *toReturn = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(toReturn, str1);
    strcat(toReturn, str2);
    return toReturn;
}

int dataToInt(char *data) {
    int day = strToInt(data[1])*10+strToInt(data[0]);
    int month = strToInt(data[3])*10+strToInt(data[4]);
    int year = strToInt(data[6])*1000+strToInt(data[7])*100+strToInt(data[8])*10+strToInt(data[9]);
    return year*10000+month*100+day;
}

char* intToData(int data) { 
    char *toReturn = malloc(11); // "gg/mm/aaaa" + '\0'

    // data : aaaammgg
    int giorno = data % 100;
    int mese   = (data % 10000) / 100;
    int anno   = data / 10000;

    sprintf(toReturn, "%02d/%02d/%04d", giorno, mese, anno);
    return toReturn;
}

int strToInt(char a) {return (((int) a) - 48);}