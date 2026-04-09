#ifndef LIBRERIA_RLE_H
#define LIBRERIA_RLE_H
#include <iostream>
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
            return a; // contenido válido
        }
        catch (runtime_error& e) {
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
}

#endif // LIBRERIA_RLE_H
