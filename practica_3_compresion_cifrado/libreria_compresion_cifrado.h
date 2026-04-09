#ifndef LIBRERIA_COMPRESION_CIFRADO_H
#define LIBRERIA_COMPRESION_CIFRADO_H
#include <iostream>
#include <fstream>
using namespace std;
string comprobar_nombre_documento(string a){
    while(true){
        try {
            cout << "ingrese el nombre del documento \n";
            cin >> a;
            if (a.length()<1){
                throw runtime_error("el nombre del documento es muy corto");
            }
            if (a.length() > 20){
                throw runtime_error("el nombre del documento es muy largo");
            }
            break;
        }
        catch(runtime_error& e) {
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
    int punto = -1;
    for (int i = 0; i < a.length(); i++){
        if (a[i] == '.'){
            punto = i;
            break;
        }
    }
    if (punto == -1){
        a += ".txt";
    }
    else{
        string tipo_documento = a.substr(punto);
        if(tipo_documento != ".txt"){
            a = a.substr(0,punto) + ".txt";
        }
    }
    return a;
}

string sin_numeros(string a){
    while(true){
        try {
            cout << "Escribe el contenido del documento: ";
            cin.ignore();
            getline(cin, a);
            if (a == ""){
                throw runtime_error("no se puede añadir vacío");
            }
            else{
                for (int b = 0; b < a.length(); b++ ){
                    if (a[b] >= '0' && a[b] <= '9'){
                        throw runtime_error("no se puede ingresar números");
                    }
                }
            }
            return a;
        }
        catch (runtime_error& e) {
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
}
int desplazamiento(int a){
    while(true){
        try {
            cout << "ingrese el numero de bits desplazados \n";
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

#endif // LIBRERIA_COMPRESION_CIFRADO_H
