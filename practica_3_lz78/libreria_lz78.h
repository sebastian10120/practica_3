#ifndef LIBRERIA_LZ78_H
#define LIBRERIA_LZ78_H
#include <iostream>
#include <fstream>
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
void texto(char *a){
    while(true){
        try{
            cout << "escriba el contenido del texto";
            cin.getline(a,500);
            int len = longitud(a);
            if (len < 1){
                throw runtime_error("no se puede ingresar una cadena vacia");
            }
            else if (len >= 500){
                throw runtime_error("no se puede ingresar una cadena tan larga");
            }
            break;
        }
        catch (runtime_error& e) {
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }
}
void leer(char *contenido, char* nombre,int tamano_total){
    fstream archivo(nombre, ios::in);
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    int i = 0;
    char ch;
    while (archivo.get(ch) && i < tamano_total - 1) {
        contenido[i++] = ch;
    }
    contenido[i] = '\0';
    archivo.close();
}
void imprimirContenido(char* contenido) {
    int i = 0;
    while (contenido[i] != '\0') {
        cout << contenido[i];
        i++;
    }
    cout << endl;
}
void descomprimir(char *nombre){
    fstream archivo (nombre, ios::in);
    char diccionario[500][500];
    diccionario[0][0] = '\0';
    int pref;
    char ch;
    int tam = 1;
    while (archivo >> pref >>ch){
        int i = 0;
        while (diccionario[pref][i] != '\0'){
            diccionario[tam][i] = diccionario[pref][i];
            i++;
        }
        if (ch != '#') {
            diccionario[tam][i] = ch;
            diccionario[tam][i + 1] = '\0';
        } else {
            diccionario[tam][i] = '\0';
        }
        cout << diccionario[tam];
        tam++;
    }

    archivo.close();
    cout << endl;
}

#endif // LIBRERIA_LZ78_H
