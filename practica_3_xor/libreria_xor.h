#ifndef LIBRERIA_XOR_H
#define LIBRERIA_XOR_H
#include <iostream>
using namespace std;
int longitud(char* a);
void agregarTxt(char* a);
char *lista_nombre(char *a){
    while(true){
        try {
            cout << "ingrese el nombre de documento:\n";
            cin.getline(a,30);
            int len = longitud(a);
            if (len < 1){
                throw runtime_error("no se puede ingresar una cadena vacia");
            }
            else if (len >= 30){
                throw runtime_error("no se puede ingresar una cadena tan larga");
            }
            break;
        } catch (runtime_error& e) {
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
    agregarTxt(a);
    return a;
}
int longitud(char* a) {
    int i = 0;
    while (a[i] != '\0') {
        i++;
    }
    return i;
}

int desplazamiento(int a){
    while(true){
        try {
            cout << "ingrese el numero de veces que se moveran los bits a la derecha \n";
            cin >> a;
            if (cin.fail()) {
                throw runtime_error("Entrada invalida (vacia o no numerica)");
            }
            if (0 >= a){
                throw runtime_error("no se puede ingresar un valor menor a 1");
            }
            else if (8 < a){
                throw runtime_error("no se puede ingresar un valor menor a 8");
            }
            break;
        }
        catch (runtime_error& e) {
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
    return a;
}
char ingresar_llave(char a){
    try{
        cout << "ingrese el caracter usado como llave:\n";
        cin >> a;
        if (cin.fail()) {
            throw runtime_error("Entrada invalida vacia");
        }
    }
    catch(runtime_error& e){
        cout << "Error: " << e.what() << " Intente de nuevo.\n";
    }

    return a;
}
void agregarTxt(char* a) {
    int len = longitud(a);
    int posPunto = -1;
    for (int i = 0; i < len; i++) {
        if (a[i] == '.') {
            posPunto = i;
            break;
        }
    }
    if (posPunto == -1) {
        a[len] = '.';
        a[len + 1] = 't';
        a[len + 2] = 'x';
        a[len + 3] = 't';
        a[len + 4] = '\0';
        return;
    }
    if (len - posPunto == 4 && a[posPunto+1] == 't' && a[posPunto+2] == 'x' &&  a[posPunto+3] == 't') {
        return;
    }
    a[posPunto] = '.';
    a[posPunto + 1] = 't';
    a[posPunto + 2] = 'x';
    a[posPunto + 3] = 't';
    a[posPunto + 4] = '\0';
}
#endif // LIBRERIA_XOR_H
