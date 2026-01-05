#include <iostream>
#include <memory>

using namespace std;

void stampa(unique_ptr<int>& p) {
    cout << *p;
}

int main() {
    auto p = make_unique<int>(4); // auto = unique_ptr<int>
    cin >> *p;
    stampa(p);
}   