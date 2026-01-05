#include <stdio.h>

const char path[] = "C:\\Users\\arand\\Desktop\\Progetti Coding\\Programmazione in C\\Esercizi\\File\\es1.txt";

int main() {
    int n;
    printf("Quante temperature vuoi inserire? ");
    scanf("%d", &n);

    float temperature[n];    
    FILE *fp = fopen(path, "a+");
    if (fp == NULL) { printf("File non inizializzato correttamente"); return 1; }
    
    for (int i = 0; i < n; i++) {
        scanf("%f", &temperature[i]);
        fprintf(fp, "%.2f\n", temperature[i]);
    }
    
    
    fclose(fp);

    return 0;
}
