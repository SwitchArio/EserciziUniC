#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char path[] = "C:\\Users\\arand\\Desktop\\Progetti Coding\\Programmazione in C\\Esercizi\\File\\";

typedef struct 
{
    char nome[50];
    char cognome[50];
    char telefono[15];
    char email[80];
} Contatto;

void aggiungiContatto();
void inizializzaContatto(Contatto* nuovoContatto);
void visualizzaContatti();
void stampaContatto(Contatto c);
Contatto* cercaContatto();
void mostraMenu();
void salvaSuBin();
void caricaDaBin();

Contatto* dbContatti = NULL; // database
int counterContatti = 0, dbCaricato = 0;

int main() {

    int scelta;    
    do {
        mostraMenu();
        scanf("%d", &scelta);
        printf("\n\n\n\n");
        switch (scelta)
        {
        case 1:
            aggiungiContatto();
            break;
        case 2:
            visualizzaContatti();
            break;
        case 3:
            Contatto* c = cercaContatto();
            if (c != NULL) stampaContatto(*c);
            else printf("Contatto non trovato");
            break;
        case 4:
            salvaSuBin();
            break;
        case 5:
            caricaDaBin();
            break;
        default:
            break;
        }
    } while (scelta != 6);
    

    

    return 0;
}

void aggiungiContatto() {
    if (dbContatti == NULL && dbCaricato == 0) { printf("database non caricato"); return; }
    
    Contatto nuovoContatto;
    inizializzaContatto(&nuovoContatto);
    
    Contatto* tmp = realloc(dbContatti, ++counterContatti*sizeof(Contatto));
    if (tmp == NULL) { printf("errore nella riallocazione della memoria"); return; }

    dbContatti = tmp;
    dbContatti[counterContatti-1] = nuovoContatto;
};

void inizializzaContatto(Contatto* nuovoContatto) {
    printf("Inserisci nome: ");
    scanf("%s", nuovoContatto->nome);
    printf("Inserisci cognome: ");
    scanf("%s", nuovoContatto->cognome);
    printf("Inserisci email: ");
    scanf("%s", nuovoContatto->email);
    printf("Inserisci telefono: ");
    scanf("%s", nuovoContatto->telefono);
};

void visualizzaContatti() {
    if (dbContatti == NULL) { printf("database non caricato"); return; }

    for (int i = 0; i < counterContatti; i++) stampaContatto(dbContatti[i]);
};

void stampaContatto(Contatto c) {
    printf("Nome: %s\nCognome: %s\nTelefono: %s\nEmail: %s\n",
           c.nome, c.cognome, c.telefono, c.email);
    printf("-------------------------------------------\n");
}

Contatto* cercaContatto() {
    if (dbContatti == NULL && dbCaricato == 0) { printf("database non caricato"); return NULL; }
    char nome[50], cognome[50];
    printf("Inserisci nome e cognome: ");
    scanf("%s %s", nome, cognome);
    for (int i = 0; i < counterContatti; i++)
        if (strcmp(dbContatti[i].nome, nome) && strcmp(dbContatti[i].cognome, cognome))
            return dbContatti + i;
    return NULL;
}

void mostraMenu() {
    printf("\n==================== RUBRICA ====================\n");
    printf("1. Aggiungi nuovo contatto\n");
    printf("2. Visualizza tutti i contatti\n");
    printf("3. Cerca contatto per cognome\n");
    printf("4. Salva rubrica su file binario (rubrica.dat)\n");
    printf("5. Carica rubrica da file binario\n");
    printf("6. Esci\n");
    printf("=================================================\n");
    printf("Scelta: ");
}

void salvaSuBin() {
    if (dbCaricato == 0) { printf("carica prima un database"); return; }
    char fileName[] = "rubrica.bin";
    char *filePath = malloc(strlen(path) + strlen(fileName) + 1);
    strcpy(filePath, path);
    strcat(filePath, fileName);

    FILE *fp = fopen(filePath, "wb"); free(filePath);
    if (fp == NULL) { printf("File non inizializzato correttamente"); return; }
    
    size_t written = fwrite(&counterContatti, sizeof(int), 1, fp);
    if (written != 1)  printf("Errore nella scrittura su file");
    written = fwrite(dbContatti, sizeof(Contatto), counterContatti, fp);
    if (written != counterContatti)  printf("Errore nella scrittura su file, scritto %zu su %d\n", written, counterContatti);
    fclose(fp);
};

void caricaDaBin() {
    char fileName[] = "rubrica.bin";
    char *filePath = malloc(strlen(path) + strlen(fileName) + 1);
    strcpy(filePath, path);
    strcat(filePath, fileName);

    FILE *fp = fopen(filePath, "rb"); free(filePath);
    if (fp == NULL) { 
        if (dbCaricato == 0) {
            dbCaricato = 1; 
            printf("database creato e caricato correttamente"); 
            return;
        }
        else { printf("File non inizializzato correttamente"); return; }
    }
    
    size_t read = fread(&counterContatti, sizeof(int), 1, fp);
    if (read != 1) { printf("Errore nella lettura su file\n"); return; }

    dbContatti = malloc(sizeof(Contatto) * counterContatti);
    read = fread(dbContatti, sizeof(Contatto), counterContatti, fp);
    if (read == counterContatti) { 
        printf("database caricato correttamente"); 
        dbCaricato = 1; 
        return;
    }
    
    printf("Errore nella lettura su file, letto %zu su %d\n", read, counterContatti);
    
    
};