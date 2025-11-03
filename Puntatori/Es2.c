#include <stdio.h>

int main() {
    int a,b;
    int *pa = &a;
    int *pb = &b;
    scanf("%d",&a);
    scanf("%d",&b);
    int tmp = *pa;
    a = *pb;
    b = tmp;
    printf("a: %d, b: %d",a,b);
    return 0;
}