#include <stdio.h>

int main() {
    int n;
    printf("quanti interi vuoi inserire? ");
    scanf("%d",&n);
    int values[n];
    int *p_values = values;
    for (int i = 0; i < n; i++)
        scanf("%d",&values[i]);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += *(p_values+i);
    
    printf("sum: %d",sum);
    return 0;
}