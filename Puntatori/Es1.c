#include <stdio.h>

int main() {
    int a,b;
    int *pa = &a;
    int *pb = &b;
    scanf("%d",&a);
    scanf("%d",&b);
    printf("%d",*pa+*pb);
    return 0;
}