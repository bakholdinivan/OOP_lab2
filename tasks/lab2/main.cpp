#include "twelve.h"
#include <iostream>
using namespace std;

int main() {
    try {
        Twelve a("A5");
        Twelve b("17B");

        Twelve c = a.add(b);
        Twelve d = b.sub(a);
        Twelve e = a.copy();

        cout << a.toString() << " + " << b.toString() << " = " << c.toString() << endl;
        cout << b.toString() << " - " << a.toString() << " = " << d.toString() << endl;
        cout << "Копия числа a: " << e.toString() << endl;

        int cmp = a.compare(b);
        if (cmp < 0) cout << a.toString() << " < " << b.toString() << endl;
        else if (cmp > 0) cout << a.toString() << " > " << b.toString() << endl;
        else cout << a.toString() << " == " << b.toString() << endl;
    }
    catch (const exception& ex) {
        cout << "Ошибка: " << ex.what() << endl;
    }

    return 0;
}