#include <iostream>
#include <fstream>
#include "libreria_xor.h"
using namespace std;

void agregarTxt(char* a);
int longitud(char *a);
char *lista_nombre(char *a);
int desplazamiento(int a);
//bool direccion();
char ingresar_llave(char a);

int main()
{
    fstream archivo,compresion;
    int bit = 0;
    bool lado = true;
    unsigned char ch, llave;
    char nombre_documento[30], filo[500];
    char *nombre = nombre_documento, *fila = filo;
    nombre = lista_nombre(nombre);
    archivo.open(nombre, ios :: in);
    if (archivo.fail()){
        archivo.close();
        cout << "archivo " << nombre << " no existe\n";
    }
    else{
        llave = ingresar_llave(llave);
        cin.clear();
        bit = desplazamiento(bit);
        cin.clear();
        while(archivo.getline(fila, 500)){
            for (int a = 0; fila[a] != '\0'; a++ ){
                cout << fila[a];
            }
            cout << endl;
        }
        archivo.close();
        archivo.open(nombre, ios::in);
        compresion.open("compresion.txt",ios::out);
        while (archivo.getline(fila, 500)){
            for (int a = 0; fila[a] != '\0'; a++ ){
                /*validacion de lado*/
                ch = fila[a];
                if (ch != ' '){
                    ch = (ch << bit) | (ch >> (8 - bit));
                    ch ^= llave;
                    fila[a] = ch;
                }
                cout << fila[a];
                compresion << fila[a];
            }
            cout << endl;
            compresion << endl;
        }
        archivo.close();
        compresion.close();
        compresion.open("compresion.txt", ios::in);
        while (compresion.getline(fila, 500)){
            for (int a = 0; fila[a] != '\0'; a++ ){
                ch = fila[a];
                if (ch != ' '){
                    ch ^= llave;
                    ch = (ch >> bit) | (ch << (8 - bit));
                    fila[a] = ch;
                }
                cout << fila[a];
            }
            cout << endl;
        }
    }
}

/*
                if (lado == false){
                    fila[a] = fila[a] << bit;
                    if (fila[a] != ' '){
                        fila[a] ^= llave;
                        cout << fila[a];
}
}
else if (lado == true){
    fila[a] = fila[a] >> bit;
    if (fila[a] != ' '){
        fila[a] ^= llave;
        cout << fila[a];
    }
}
*/
/*
bool direccion(){
    char decision;
    bool valor;
    while (true){
        try {
            cout << "(a) izquierda (b) derecha\n";
            cin >> decision;
            if (decision == 'a' || decision == 'b' || decision == 'A' || decision == 'B'){
                if (decision == 'a' || decision == 'A'){
                    valor = true;
                }
                else if (decision == 'b' || decision == 'B'){
                    valor = false;
                }
            }
            else {
                throw runtime_error("tiene que ser valor a o b");
            }
            break;
        }
        catch(runtime_error& e){
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
    return valor;
}
*/
