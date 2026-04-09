#include <iostream>
#include <fstream>
#include "libreria_lz78.h"
using namespace std;

void texto(char *a);
int longitud(char* a);
char *lista_nombre(char *a);
void agregarTxt(char* a);
void leer(char *contenido, char* nombre,int tamano_total);
void imprimirContenido(char* contenido);
void descomprimir(char *nombre);
int main()
{
    fstream documento, compresion;
    int tamano_diccionario = 1, capacidad = 10;
    int *prefijo = new int[capacidad];
    char *caracter = new char[capacidad];
    char *nombre;
    char nombre_documento[30], contenido_documento[500] ={};
    char *contenido = contenido_documento;
    char nombre_compresion[] = "comprimido.txt";
    nombre = nombre_documento;
    nombre = lista_nombre(nombre);
    documento.open(nombre);
    if (documento.fail()){
        texto(contenido);
        documento.close();
        agregarTxt(nombre);
        documento.open(nombre, ios::out);
        documento << contenido;
    }
    documento.close();
    leer(contenido, nombre, 500);
    imprimirContenido(contenido);
    documento.open(nombre, ios:: in);
    int pref = 0;
    char ch;
    fstream comp(nombre_compresion, ios::out);
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
            if (tamano_diccionario == capacidad) {
                int nuevaCap = capacidad * 2;

                int* nuevoPref = new int[nuevaCap];
                char* nuevoChar = new char[nuevaCap];

                for (int i = 0; i < tamano_diccionario; i++) {
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
    if (pref != 0) {
        comp << pref << " " << '#' << "\n";
    }
    comp.close();
    descomprimir(nombre_compresion);
    documento.close();
    delete[] prefijo;
    delete[] caracter;
    return 0;
}
