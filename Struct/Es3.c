#include <stdio.h>

typedef struct {
    char titolo[100];
    char autore[50];
    int anno_pubblicazione;
    float prezzo;
} Libro;

int inizializzaLibro(Libro *s);

int main() {
    int n = 3;
    Libro a[n];
    float somma;
    for (int i = 0; i < n; i++) if (inizializzaLibro(&a[i])==-1) return -1;
    for (int i = 0; i < n; i++) somma += a[i].prezzo;
    
    printf("Il prezzo medio dei libri è %f", somma/n );
    
    return 0;
}

int inizializzaLibro(Libro *s){
    if(s==NULL) return -1;
    printf("Inserisci il titolo del libro: ");
    scanf("%s",s->titolo);
    printf("Inserisci l'autore del libro: ");
    scanf("%s",s->autore);
    printf("Inserisci l'anno di pubblicazione: ");
    scanf("%d", &s->anno_pubblicazione);
    printf("Inserisci il prezzo del libro: ");
    scanf("%f", &s->prezzo);
    return 1;
}