#include <iostream>

using namespace std;

void incrementa(int& a) {a++;}
void incrementa(int* a, int n) { *a+=n; }

int main() {
    int x, y;
    cout << "Inserisci 2 numeri" << endl;
    cin >> x >> y;
    cout << "x++ : ";
    incrementa(x); 
    cout << x << endl << "x+=" << y;
    incrementa(&x, y); 
    cout << " : " << x;
}