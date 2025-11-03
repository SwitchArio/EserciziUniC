#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, Max_Char = 30;
    printf("quanti nomi vuoi inserire? ");
    scanf("%d",&n);
    
    char *arrNomi[n];
    for (int i = 0; i < n; i++){
        arrNomi[i] = malloc(Max_Char * sizeof(char));
        scanf("%s",arrNomi[i]);
    }
    
    for (int i = 0; i < n; i++)
        printf("hai inserito: %s, indirizzo: %p\n",arrNomi[i], (void*)arrNomi[i]);
    
    for (int i = 0; i < n; i++)
        free(arrNomi[i]);
    
    return 0;
}