#include <iostream>
#include <fstream>
#include "libreria_compresion_cifrado.h"
using namespace std;
string comprobar_nombre_documento(string a);
string sin_numeros(string a);
char ingresar_llave(char a);
int desplazamiento(int a);
int main()
{
    bool documento_abierto = false;
    bool compresion_de_documento = true;
    string documento, fila,texto_descifrado = "",contenido_extraido, contenido_entero,contenido;
    string numero_repetido, linea, linea_descifrada, cadena_comprimida;
    unsigned char chs, llave;
    int bit = 0;
    documento = comprobar_nombre_documento(documento);
    fstream abrir, comprimido;
    abrir.open(documento);
    if (abrir.fail()){
        abrir.close();
        cout << "documento no existe por favor escriba el contenido del nuevo documento:\n";
        abrir.open(documento, ios::out);
        cin.ignore();
        contenido = sin_numeros(contenido);
        abrir << contenido;
    }
    bit = desplazamiento(bit);
    llave = ingresar_llave(llave);
    cin.clear();
    abrir.close();
    abrir.open(documento, ios::in);
    while (getline(abrir, fila)){
        cout << fila << endl;
    }
    abrir.close();
    abrir.open(documento, ios::in);
    char ch_evaluado, ch_antiguo;
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
    abrir.open(documento, ios:: in);
    /*desde aqui voy a copiar la cifracion*/
    abrir.close();
    abrir.open(documento, ios::in);
    comprimido.open("compresion.txt", ios::out);

    while (getline(abrir, fila)){
        linea_descifrada = "";
        for (int a = 0; a < fila.length(); a++ ){
            chs = fila[a];
            if (chs != ' '){
                chs = (chs >> bit) | (chs << (8 - bit));
                chs ^= llave;
                fila[a] = chs;
            }
            cout << fila[a];
            comprimido << fila[a];
        }
        cout << endl;
        comprimido << endl;
    }
    abrir.close();
    comprimido.close();
    comprimido.open("compresion.txt", ios::in);
    abrir.open(documento, ios::out);
    while (getline(comprimido, fila)){
        abrir << fila << endl;
    }
    comprimido.close();
    abrir.close();
    abrir.open(documento, ios::in);
    texto_descifrado = "";
    while (getline(abrir, fila)){
        linea_descifrada = "";
        for (int a = 0; a < fila.length(); a++ ){
            chs = (unsigned char)fila[a];

            if (chs != ' '){
                chs ^= llave;
                chs = (chs << bit) | (chs >> (8 - bit));
            }

            linea_descifrada += (char)chs;
            cout << (char)chs;
        }
        texto_descifrado += linea_descifrada + "\n";
        cout << endl;
    }
    abrir.close();
    abrir.open(documento, ios::out);
    abrir << texto_descifrado;
    abrir.close();
    abrir.open(documento, ios::in);
    char ch;
    int numero = 0;
    linea = "";
    while (getline(abrir,contenido_extraido)){
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

