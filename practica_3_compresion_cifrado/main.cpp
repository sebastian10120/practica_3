#include <iostream>
#include <fstream>
#include "libreria_compresion_cifrado.h"
using namespace std;
string comprobar_nombre_documento(string a);
string ingresar_contenido_rle(string a);
char ingresar_llave(char a);
int desplazamiento(int a);
int seleccionar_compresion();
void agregarTxt(char* a);
int longitud(char* a);
void texto(char *a);
void imprimirContenido(char* contenido);
void descomprimir(char *nombre);
void leer(char *contenido, char* nombre,int tamano_total);
char *lista_nombre(char *a);
int main()
{
    int elegir_metodo_compresion;
    bool documento_abierto = false;
    bool compresion_de_documento = true;
    char fila_lista[500],fila_decifrada[500];
    string documento, fila,texto_descifrado = "",contenido_extraido, contenido_entero,contenido;
    string numero_repetido, linea, linea_descifrada, cadena_comprimida;
    unsigned char chs, llave;
    int bit = 0;
    elegir_metodo_compresion = seleccionar_compresion();
    bit = desplazamiento(bit);
    llave = ingresar_llave(llave);
    if (elegir_metodo_compresion == 1){
        documento = comprobar_nombre_documento(documento);
        fstream abrir, comprimido;
        abrir.open(documento);
        if (abrir.fail()){
            abrir.close();
            cout << "documento no existe por favor escriba el contenido del nuevo documento:\n";
            abrir.open(documento, ios::out);
            string contenido_rle;
            contenido = ingresar_contenido_rle(contenido_rle);
            abrir << contenido;
        }

        cin.clear();
        abrir.close();
        abrir.open(documento, ios::in);
        while (getline(abrir, fila)){
            cout << fila << endl;
        }
        abrir.close();
        abrir.open(documento, ios::in);
        char ch_evaluado = '\0', ch_antiguo = '\0';
        while (getline(abrir,contenido_extraido)){
            cadena_comprimida = "";
            int contador_iguales=1;
            for(int i= 0; i < contenido_extraido.length();i++){
                if (i == 0){
                    ch_evaluado = contenido_extraido[i];
                }
                else if (i >0){
                    ch_antiguo = ch_evaluado;
                    ch_evaluado = contenido_extraido[i];
                    if (ch_antiguo == ch_evaluado){
                        contador_iguales++;
                    }
                    else{
                        cadena_comprimida += string(1, ch_antiguo) + "_" + to_string(contador_iguales);
                        contador_iguales = 1;
                    }
                }
            }
            cadena_comprimida += string(1, ch_antiguo) + "_" + to_string(contador_iguales);
            contenido_entero += cadena_comprimida + "\n";
        }
        cout << contenido_entero;
        abrir.close();
        abrir.open(documento, ios::out);
        abrir << contenido_entero;
        abrir.close();
        abrir.open(documento, ios::in);
        comprimido.open("compresion.txt", ios::out);
        while (abrir.getline(fila_lista, 500)){
            for (int a = 0; fila_lista[a] != '\0'; a++ ){
                chs = fila_lista[a];
                if (chs != ' '){
                    chs = (chs << bit) | (chs >> (8 - bit));
                    chs ^= llave;
                    fila_lista[a] = chs;
                }
                cout << fila_lista[a];
                comprimido << fila_lista[a];
            }
            cout << endl;
            comprimido << endl;
        }
        abrir.close();
        comprimido.close();
        comprimido.open("compresion.txt", ios::in);
        abrir.open(documento, ios::out);
        while (comprimido.getline(fila_lista, 500)){
            abrir << fila_lista << endl;
        }
        comprimido.close();
        abrir.close();
        abrir.open(documento, ios::in);
        texto_descifrado = "";
        while (abrir.getline(fila_lista, 500)){
            for (int a = 0; fila_lista[a] != '\0'; a++ ){
                chs = fila_lista[a];

                if (chs != ' '){
                    chs ^= llave;
                    chs = (chs >> bit) | (chs << (8 - bit));
                }
                texto_descifrado += chs;
                cout << chs;
            }
            texto_descifrado += "\n";
            cout << endl;
        }
        abrir.close();
        abrir.open(documento, ios::out);
        abrir << texto_descifrado;
        abrir.close();
        abrir.open(documento, ios::in);
        char ch = '\0';
        int numero = 0;
        linea = "";
        while (getline(abrir,contenido_extraido)){
            numero_repetido = "";
            for(int j = 0; j < contenido_extraido.length(); j++){
                if (contenido_extraido[j] == '_' && contenido_extraido[j+1] == '_'){
                    ch = '_';
                    j++;
                    continue;
                }
                if (contenido_extraido[j] == '_'){
                    continue;
                }

                if (contenido_extraido[j] >= '0' && contenido_extraido[j] <= '9'){
                    numero_repetido += contenido_extraido[j];
                }
                else {
                    if (ch != '\0' && numero_repetido != "") {

                        numero = 0;
                        for (int i = 0; i < numero_repetido.length(); i++) {
                            numero = numero * 10 + (numero_repetido[i] - '0');
                        }
                        for (int y = 0; y < numero; y++) {
                            linea += ch;
                        }
                        numero_repetido = "";
                    }
                    ch = contenido_extraido[j];
                }
            }
            if (ch != '\0' && numero_repetido != "") {
                numero = 0;
                for (int i = 0; i < numero_repetido.length(); i++) {
                    numero = numero * 10 + (numero_repetido[i] - '0');
                }
                for (int y = 0; y < numero; y++) {
                    linea += ch;
                }
            }
            linea += "\n";
        }
        cout << linea;
        abrir.close();
        abrir.open(documento, ios::out);
        abrir << linea;
        abrir.close();
    }
    else if(elegir_metodo_compresion == 2){
        char nombre_documento[30], contenido_documento[500] = {};
        char *nombre = nombre_documento;
        char nombre_compresion[] = "comprimido2.txt";
        nombre = lista_nombre(nombre);

        fstream documento, compresion;
        documento.open(nombre);

        if (documento.fail()){
            texto(contenido_documento);
            documento.close();
            agregarTxt(nombre);
            documento.open(nombre, ios::out);
            documento << contenido_documento;
        }
        documento.close();
        leer(contenido_documento, nombre, 500);
        imprimirContenido(contenido_documento);
        documento.open(nombre, ios::in);
        int tamano_diccionario = 1, capacidad = 10;
        int *prefijo = new int[capacidad];
        char *caracter = new char[capacidad];
        int pref = 0;
        char ch;
        fstream comp;
        comp.open(nombre_compresion, ios::out);
        while(documento.get(ch)){
            int encontrar = -1;
            for(int i = 1; i < tamano_diccionario; i++){
                if (prefijo[i] == pref && caracter[i] == ch){
                    encontrar = i;
                    break;
                }
            }
            if (encontrar != -1){
                pref = encontrar;
            }
            else{
                cout << "(" << pref << "," << ch << ")\n";
                comp << pref << " " << ch << "\n";

                if (tamano_diccionario == capacidad){
                    int nuevaCap = capacidad * 2;

                    int* nuevoPref = new int[nuevaCap];
                    char* nuevoChar = new char[nuevaCap];

                    for (int i = 0; i < tamano_diccionario; i++){
                        nuevoPref[i] = prefijo[i];
                        nuevoChar[i] = caracter[i];
                    }
                    delete[] prefijo;
                    delete[] caracter;
                    prefijo = nuevoPref;
                    caracter = nuevoChar;
                    capacidad = nuevaCap;
                }
                prefijo[tamano_diccionario] = pref;
                caracter[tamano_diccionario] = ch;
                tamano_diccionario++;
                pref = 0;
            }
        }
        if (pref != 0){
            comp << pref << " " << '#' << "\n";
        }
        comp.close();
        documento.close();
        fstream comprimido;
        comprimido.open(nombre_compresion, ios::in);
        fstream cifrado;
        cifrado.open("cifrado.txt", ios::out);
        char c;
        while (comprimido.get(c)){
            if (c != ' '){
                c = (c << bit) | (c >> (8 - bit));
                c ^= llave;
            }
            cout << c;
            cifrado << c;
        }
        comprimido.close();
        cifrado.close();
        cifrado.open("cifrado.txt", ios::in);
        fstream descifrado;
        descifrado.open("descifrado.txt", ios::out);
        char chs;
        while (cifrado.get(chs)){
            if (chs != ' '){
                chs ^= llave;
                chs = (chs >> bit) | (chs << (8 - bit));
            }

            cout << chs;
            descifrado << chs;
        }
        cifrado.close();
        descifrado.close();
        descomprimir(nombre_compresion);
        delete[] prefijo;
        delete[] caracter;
    }
}


