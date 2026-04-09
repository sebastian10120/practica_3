#include <iostream>
#include <fstream>
#include "libreria_rle.h"
using namespace std;
string comprobar_nombre_documento(string a);
string sin_numeros(string a);
/*to_string convierte datos en string*/
/*substr me genera una nueva string desde el punto que yo marque*/

int main(){
    bool documento_abierto = false;
    bool compresion_de_documento = true;
    string documento, fila;
    documento = comprobar_nombre_documento(documento);
    fstream abrir;
    abrir.open(documento);
    if (abrir.fail()){
        abrir.close();
        cout << "documento no existe por favor escriba el contenido del nuevo documento:\n";
        abrir.open(documento, ios::out);
        string contenido;
        cin.ignore();
        contenido = sin_numeros(contenido);
        abrir << contenido;
    }
    abrir.close();
    abrir.open(documento, ios::in);
    while (getline(abrir, fila)){
        cout << fila << endl;
    }
    abrir.close();
    abrir.open(documento, ios::in);
    string contenido_extraido, contenido_entero;
    char ch_evaluado, ch_antiguo;
    while (getline(abrir,contenido_extraido)){
        /*desde aqui se comprime*/
        string cadena_comprimida = "";
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
                    cadena_comprimida += string(1, ch_antiguo) + to_string(contador_iguales);
                    contador_iguales = 1;
                }
            }
        }
        cadena_comprimida += string(1, ch_antiguo) + to_string(contador_iguales);
        contenido_entero += cadena_comprimida + "\n";
    }
    cout << contenido_entero;
    abrir.close();
    abrir.open(documento, ios::out);
    abrir << contenido_entero;
    abrir.close();
    abrir.open(documento, ios::in);
    char ch;
    string numero_repetido = "", linea = "";
    int numero = 0;
    bool dato_tomado = true;
    while (getline(abrir,contenido_extraido)){
        ch = '\0';
        numero_repetido = "";
        for(int j = 0; j < contenido_extraido.length(); j++){
            if (contenido_extraido[j] <= '9' && contenido_extraido[j] >= '0'){
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
                }
                ch = contenido_extraido[j];
                numero_repetido = "";
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

