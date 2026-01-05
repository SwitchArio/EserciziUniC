#include <stdio.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} Studente;

int inizializzaStudente(Studente *s);
void stampaStudente(Studente *s);
void confrontaMedie(Studente *a, Studente *b);

int main() {
    Studente a, b;
    if (inizializzaStudente(&a)==-1) return -1;
    if (inizializzaStudente(&b)==-1) return -1;
    confrontaMedie(&a,&b);
    return 0;
}

int inizializzaStudente(Studente *s){
    if(s==NULL) return -1;
    printf("Inserisci il nome dello studente: ");
    scanf("%s",s->nome);
    printf("Inserisci il cognome dello studente: ");
    scanf("%s",s->cognome);
    printf("Inserisci la matricola dello studente: ");
    scanf("%d", &s->matricola);
    printf("Inserisci la media dei voti dello studente: ");
    scanf("%f", &s->media_voti);
    return 1;
}

void stampaStudente(Studente *s) {
    printf("Studente %s %s:\nMatricola %d\nMedia %2.1f\n", s->nome, s->cognome, s->matricola, s->media_voti);
};

void confrontaMedie(Studente *a, Studente *b) {
    if (a->media_voti < b->media_voti) printf("%s %s ha media più alta di %s %s", b->nome, b->cognome, a->nome, a->cognome);
    else if (a->media_voti > b->media_voti) printf("%s %s ha media più alta di %s %s", a->nome, a->cognome, b->nome, b->cognome);
    else printf("%s %s hanno la stessa media %s %s", a->nome, a->cognome, b->nome, b->cognome);
    return;
}