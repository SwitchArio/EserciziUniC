#include <stdio.h>
#include <stdlib.h>

void stampa(int *a, int length);

int main() {
    int n;
    printf("quanti valori vuoi inserire? ");
    scanf("%d",&n);
    
    int *arrNomi = malloc(n * sizeof(int));

    printf("Inseriscili: ");
    for (int i = 0; i < n; i++) scanf("%d", arrNomi+i);
    
    int *arrNomi2 = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) *(arrNomi2 + i) = *(arrNomi + n - 1 - i);
    
    stampa(arrNomi, n);
    stampa(arrNomi2, n);
    free(arrNomi2);
    free(arrNomi);
    
    return 0;
}

void stampa(int *a, int length) {
    for (int i = 0; i < length; i++) printf("%d ", *(a+i));
    printf("\n");
    return;
}