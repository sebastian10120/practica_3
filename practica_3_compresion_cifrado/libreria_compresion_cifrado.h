#ifndef LIBRERIA_COMPRESION_CIFRADO_H
#define LIBRERIA_COMPRESION_CIFRADO_H
#include <iostream>
#include <fstream>
using namespace std;
void agregarTxt(char* a);
int longitud(char* a);
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
string ingresar_contenido_rle(string a){
    bool valido = false;
    while (!valido){
        try{
            cout << "Escriba el contenido del archivo (RLE):\n";
            getline(cin, a);

            if (a.length() < 1){
                throw runtime_error("No se puede ingresar una cadena vacia");
            }

            if (a.length() > 500){
                throw runtime_error("El contenido es demasiado largo");
            }

            valido = true; // si pasa todo, salimos del while

        } catch(runtime_error& e){
            cout << "Error: " << e.what() << " Intente de nuevo.\n";
        }
    }

    return a;
}
int seleccionar_compresion(){
    int opcion;

    try{
        cout << "Seleccione el tipo de compresion:\n";
        cout << "1. RLE\n";
        cout << "2. LZ78\n";
        cin >> opcion;

        if (cin.fail()){
            throw runtime_error("Entrada no valida");
        }

        if (opcion != 1 && opcion != 2){
            throw runtime_error("Opcion fuera de rango (solo 1 o 2)");
        }
    }
    catch(runtime_error& e){
        cout << "Error: " << e.what() << ". Intente de nuevo.\n";
        cin.clear();
        cin.ignore(50, '\n');
        return seleccionar_compresion();
    }

    return opcion;
}
char *lista_nombre(char *a){
    while(true){
        try {
            cout << "ingrese el nombre de documento:\n";
            cin.ignore();
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
    fstream archivo(nombre, ios::in);
    char diccionario[500][500];
    for (int i = 0; i < 500; i++){
        diccionario[i][0] = '\0';
    }
    int pref;
    char ch;
    int tam = 1;
    while (archivo >> pref >> ch){
        if (pref < 0 || pref >= tam){
            pref = 0;
        }
        int i = 0;
        while (diccionario[pref][i] != '\0'){
            diccionario[tam][i] = diccionario[pref][i];
            i++;
        }
        if (ch != '#'){
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

#endif // LIBRERIA_COMPRESION_CIFRADO_H
