#include <iostream>

using namespace std;

double toFahrenheit(double celsius) {
    return celsius*9/5+32;
}

int main() {
    double temp;
    cout << "Inserisci la temperatura in Celsius" << endl;
    cin >> temp;
    cout << "La temperatura in Fahrenheit e' " << toFahrenheit(temp) << endl;
}