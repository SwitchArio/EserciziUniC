#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("quanti interi vuoi inserire? ");
    scanf("%d",&n);
    
    int *arr = malloc(n * sizeof(int)); 
    int *arr2 = malloc(n * sizeof(int));
    // il cast (int*) ad int è superfluo in c

    for (int i = 0; i < n; i++){
        scanf("%d",arr+i);
        printf("hai inserito: %d, indirizzo: %d\n",*(arr+i), arr+i);
    }

    for (int i = 0; i < n; i++){
        *(arr2+i) = *(arr+i);
        
    }
    for (int i = 0; i < n; i++){
        printf("%d",*(arr2+i));
        printf("%d",*(arr+i));
    }
    free(arr);
    free(arr2);
    return 0;
}