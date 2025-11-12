    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    typedef struct {
        char nomeCorso[50];
        int voto;
        int cfu;
        char data[11];
    } Esame;

    typedef struct {
        char nome[50];
        char cognome[50];
        int numeroEsami;
        Esame *esami;
    } Studente;

    void genera_statistiche();
    void stampaEsamiStudenteOrdinati(Studente *studente);
    int inizializzaEsame(Esame *s);
    void stampaEsame(Esame e);
    void scambiaEsami(Esame *esami, int from, int to);
    float mediaEsami(Esame *arrEsami, int arrLen);
    void inserisciStudente(Studente *s);
    int inserisciNumero(char* testo);
    int indiceMigliorVotoDaA(Esame *esami, int numeroEsami, int from, int to);
    int isEsameInArray(Esame toSearch, Esame *list, int listLen);
    Studente *ricercaStudente();
    Studente *getStudentByName(char * nome, char * cognome);
    Studente *getStudentByBestMean();
    void aggiungiEsameToStudente(Esame *esame, Studente *studente);
    void aggiungiEsameInArray(Esame toSearch, Esame **list, int *listLen);
    int menuScelta();

    Studente * dbStudenti;
    int counterStudenti = 0;
    Esame *esamiTotali = NULL; 
    int esamiInseriti =0;

    int main() {

        int n = inserisciNumero("Quanti studenti deve poter gestire il database? ");

        dbStudenti = malloc(n * sizeof(Studente));
        while (counterStudenti < n) 
            inserisciStudente(&dbStudenti[counterStudenti++]);
        
        if (dbStudenti == NULL) { printf("errore nella creazione del db"); return -1;}
        
        int scelta = menuScelta();
        while (scelta != 0)
        {
            switch (scelta)
            {
                case 1:
                    inserisciStudente(&dbStudenti[counterStudenti++]);
                    break;
                case 2: {
                    Studente *studente = ricercaStudente();
                    Esame nuovoEsame;
                    int res = inizializzaEsame(&nuovoEsame);
                    if (res == -1 || studente == NULL) {
                        printf("problema nell'inizializzazione dello studente o dell'esame");
                        break;
                    }
                    aggiungiEsameToStudente(&nuovoEsame,studente);
                } break;
                case 3: {
                    Studente *studente = ricercaStudente();
                    printf("La media di %s %s è %.2f", 
                            studente->nome, 
                            studente->cognome, 
                            mediaEsami(studente->esami, studente->numeroEsami));
                    break;
                }
                case 4: {
                    Studente *studente = getStudentByBestMean(dbStudenti, counterStudenti);
                    printf("Lo studente con la media migliore è %s %s", studente->nome, studente->cognome);
                } break;
                case 5: {
                    
                    Studente *studente = ricercaStudente();
                    if (studente == NULL) break;
                    stampaEsamiStudenteOrdinati(studente);
                    
                } break;
                case 6: genera_statistiche(); break;
                default: break;
            }
            scelta = menuScelta();
        }
        
        for (int i = 0; i < counterStudenti; i++)
            free(dbStudenti[i].esami);
        free(dbStudenti);
        
        return 0;
    }

    void stampaEsamiStudenteOrdinati(Studente *studente) {
        int curr = 0;
        int nEsami = studente->numeroEsami;
        Esame *esami = studente->esami;
        while (curr < nEsami)
        {
            int k = indiceMigliorVotoDaA(esami, nEsami, curr, nEsami);
            if (k == -1) { printf("Errore nella ricerca"); break; }
            stampaEsame(esami[k]);
            scambiaEsami(esami, k, curr++);
        }
        return;
    }

    void genera_statistiche(){
        printf("Statistiche: \n");
        printf("Numero totale di esami nel sistema: %d\n", esamiInseriti);
        float somma = 0;
        int distribuzione[4] = {0,0,0,0};
        for (int i = 0; i < counterStudenti; i++){
            float media = mediaEsami(dbStudenti[i].esami, dbStudenti[i].numeroEsami);
            somma += media;
            if (media <= 21) distribuzione[0]++;
            else if (media <= 25) distribuzione[1]++;
            else if (media <= 28) distribuzione[2]++;
            else distribuzione[3]++;
        }
        printf("Media generale: %.2f\n", somma/(float)counterStudenti);
        printf("Distribuzione voti:\n   %d nel range 18-21\n   %d nel range 22-25\n   %d nel range 26-28\n   %d nel range 29-30L\n", 
        distribuzione[0], distribuzione[1], distribuzione[2], distribuzione[3]);
        return;
    }

    void aggiungiEsameInArray(Esame toSearch, Esame **list, int *listLen){
        // list deve essere un puntatore all'indirizzo della lista, 
        // perchè cambia anche l'indizzo oltre al contenuto
        Esame *tmp = realloc(*list, sizeof(Esame) * ++(*listLen));
        if (tmp == NULL)
        {
            printf("Errore nell'aggiunta dell'esame %s al database", toSearch.nomeCorso);
            return;
        }
        *list = tmp;
        (*list)[*listLen-1] = toSearch;
        return;
    };

    int isEsameInArray(Esame toSearch, Esame *list, int listLen){
        // if (list == NULL || listLen <= 0) return -1;
        for (int i = 0; i < listLen; i++)
            if(strcmp(list[i].nomeCorso,toSearch.nomeCorso) == 0) 
                return 1;
        return -1;
    };

    void stampaEsame(Esame e) {
        printf("---------\n");
        printf("Esame di %s\n", e.nomeCorso);
        printf("CFU: %d\n", e.cfu);
        printf("Voto: %d\n", e.voto);
        printf("Sostenuto in data: %s\n", e.data);
    };

    void scambiaEsami(Esame *esami, int from, int to) {
        if (from >= to) return;
        Esame tmp = esami[to];
        esami[to] = esami[from]; 
        esami[from] = tmp;
        return;
    }

    int indiceMigliorVotoDaA(Esame *esami, int numeroEsami, int from, int to) {
        int bestVoto = esami->voto;
        int bestIndex = from;
        if (to < from || to > numeroEsami) return -1;
        
        for (int i = from+1; i < to; i++)
        {
            int currVoto = (esami+i)->voto;
            if (bestVoto < currVoto) {
                bestVoto = currVoto;
                bestIndex = i;
            }
        }

        return bestIndex;
    }

    Studente *ricercaStudente() {
        char nome[50], cognome[50];
        printf("Inserisci nome e cognome dello studente cercato: ");
        scanf("%s %s", nome, cognome);
        Studente *nuovoStudente = getStudentByName(nome, cognome);
        if (nuovoStudente == NULL) { printf("Errore nella ricerca dello studente"); return NULL; };
        return nuovoStudente;
    };

    Studente *getStudentByName(char *nome, char *cognome){
        for (int i = 0; i < counterStudenti; i++)
            if (strcmp(dbStudenti[i].nome, nome) == 0 && strcmp(dbStudenti[i].cognome, cognome) == 0)
                return &dbStudenti[i];
        return NULL;
    }

    Studente *getStudentByBestMean(){
        Studente *bestStudent = &dbStudenti[0];
        for (int i = 1; i < counterStudenti; i++){
            float bestMean = mediaEsami(bestStudent->esami, bestStudent->numeroEsami);
            float currMean = mediaEsami(dbStudenti[i].esami, dbStudenti[i].numeroEsami);
            if (bestMean<currMean) bestStudent = &dbStudenti[i];
        }
        return bestStudent;
    }

    void aggiungiEsameToStudente(Esame *esame, Studente *studente){
        Esame* tmp = realloc(studente->esami, sizeof(Studente) * (++studente->numeroEsami));
        if (tmp == NULL)
        {
            printf("errore nella riallocazione della memoria nell'aggiunta dell'esame allo studente");
            return;
        }
        studente->esami = tmp;
        studente->esami[studente->numeroEsami] = *esame;
        return;
    }

    float mediaEsami(Esame *arrEsami, int arrLen){
        if (arrLen <= 0 || arrEsami == NULL) return 0;
        float somma = 0, cfuTot = 0;
        for (int i = 0; i < arrLen; i++){
            somma += arrEsami[i].voto * arrEsami[i].cfu;
            cfuTot += arrEsami[i].cfu;
        }
        return somma/cfuTot;
    }

    int inizializzaEsame(Esame *s){
        if(s==NULL) return -1;
        printf("Inserisci il nome dell'esame: ");
        scanf("%s",s->nomeCorso);
        printf("Inserisci il voto: ");
        scanf("%d", &s->voto);
        printf("Inserisci i cfu: ");
        scanf("%d", &s->cfu);
        printf("Inserisci la data nel formato gg/mm/aaaa: ");
        scanf("%s", s->data);
        if(isEsameInArray(*s, esamiTotali, esamiInseriti) == -1) {
            aggiungiEsameInArray(*s, &esamiTotali, &esamiInseriti);
        }
        return 1;
    }

    void inserisciStudente(Studente *s){
        if(s==NULL) {printf("errore nell'inserimento studente"); return;}
        printf("Inserisci il nome dello studente: ");
        scanf("%s",s->nome);
        printf("Inserisci il cognome dello studente: ");
        scanf("%s",s->cognome);
        printf("Inserisci il numero di esami dello studente: ");
        scanf("%d", &s->numeroEsami);
        s->esami = malloc(sizeof(Esame) * s->numeroEsami);
        for (int i = 0; i < s->numeroEsami; i++)
            inizializzaEsame(&s->esami[i]);

        return;
    }

    int inserisciNumero(char* testo){
        int toReturn = 0;
        printf("%s", testo);
        scanf("%d", &toReturn);
        return toReturn;
    };

    int menuScelta() {
        printf("\n==============================\n");
        printf("      GESTIONE STUDENTI\n");
        printf("==============================\n");
        printf("1) Inserire nuovo studente\n");
        printf("2) Aggiungere esame a uno studente esistente\n");
        printf("3) Calcolare la media pesata di uno studente\n");
        printf("4) Trovare lo studente con la media più alta\n");
        printf("5) Visualizzare tutti gli esami di uno studente\n");
        printf("6) Generare statistiche:\n");
        printf("   - Numero totale di esami nel sistema\n");
        printf("   - Media generale di tutti gli studenti\n");
        printf("   - Distribuzione dei voti: 18-21, 22-25, 26-28, 29-30L\n");
        printf("0) Uscita\n");
        printf("==============================\n");

        return inserisciNumero("Scelta: ");
    }