
#include "string_map.h"

template <typename T>
string_map<T>::string_map():raiz(),_size(0){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if(d._size==0){
        this->destruir(this->raiz);
        this->_size=0;
        this->raiz= nullptr;
    }
    else{
        this->destruir(this->raiz);
        this->raiz= nullptr;
        this->_size=0;
        copiarTrie(d,d.raiz,nullptr);
    }
    return *this;
}

template <class T>
void string_map<T>::destruir(Nodo *n) {
    if(raiz!= nullptr) {
        for (int i = 0; i <= n->siguientes.size(); i++) {
            if (i < 256 && n->siguientes[i] != nullptr) {
                destruir(n->siguientes[i]);
            } else if (i == 256) {
                if (n->definicion != nullptr) delete n->definicion;
                delete n;
                break;
            }
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    if(raiz!= nullptr)
        destruir(raiz);
}

template <class T>
void string_map<T>::insert(const pair<string, T> & par) {
    if(raiz== nullptr) {
        Nodo *nuevoNodo = new Nodo();
        raiz=nuevoNodo;
    }
    Nodo* nodoTemp = raiz;
    int i = 0;
    int caracter = 0;
    while(i < par.first.size()) {
        caracter = int(par.first[i]);
        //Si no existe el nodo en siguientes, lo agrego
        if (nodoTemp->siguientes[caracter] == nullptr) {
            //Si llego al ultimo caracter, entonces agrego el nodo con su definicion
            if(i == par.first.size()-1){
                T* valor = new T(par.second);
                Nodo* nuevoNodoConDef = new Nodo(valor);
                nodoTemp->siguientes[caracter] = nuevoNodoConDef;
            }
            //Si no, agrego un nodo sin definicion
            else{
                Nodo *nuevoNodo = new Nodo();
                nodoTemp->siguientes[caracter] = nuevoNodo;
                nodoTemp = nodoTemp->siguientes[caracter];
            }
        }
        //Si el nodo ya existe, sigo en el nodo siguiente y cambio su significado si hace falta
        else if (nodoTemp->siguientes[caracter] != nullptr){
            nodoTemp = nodoTemp->siguientes[caracter];
            if(i==par.first.size()-1) {
                T* valor = new T(par.second);
                delete nodoTemp->definicion;
                nodoTemp->definicion = valor;
                //Para evitar que me devuelva un tamaño incorrecto si no agregue ninguna clave, uso esto
                _size--;
            }
        }
        i++;
    }
    _size++;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* nodoActual = raiz;
    int contador = 0;
    int caracter = int(clave[0]);
    if(raiz== nullptr)
        return 0;
    else{
        int i=0;
        while(i <= clave.size() && (nodoActual->siguientes[caracter]!= nullptr || nodoActual->definicion!= nullptr) && contador!=1){

            //Si encontre la clave en la definicion, entonces esta existe y devuelvo 1
            if(i==clave.size())
                contador++;
            //Voy avanzando en el Trie
            else{
                nodoActual=nodoActual->siguientes[caracter];
                i++;
                caracter=int(clave[i]);
            }
        }
    }
    return contador;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* nodoActual = raiz;
    if(nodoActual!= nullptr){
        int i = 0;
        char caracter = int(clave[0]);
        while(i <= clave.size() && nodoActual->siguientes[caracter]!= nullptr){
            //Voy avanzando en el Trie
            nodoActual=nodoActual->siguientes[caracter];
            i++;
            caracter=int(clave[i]);
        }
        if(nodoActual->definicion!= nullptr && i == clave.size()){
            const T valor = *nodoActual->definicion;
            return valor;
        }
    }
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* nodoActual = raiz;
    if(nodoActual!= nullptr){
        int i = 0;
        char caracter = int(clave[0]);
        while(i < clave.size() && nodoActual->siguientes[caracter]!= nullptr){
            //Voy avanzando en el Trie
            nodoActual=nodoActual->siguientes[caracter];
            i++;
            caracter=int(clave[i]);
        }
        if(nodoActual->definicion!= nullptr && i == clave.size()){
            return *nodoActual->definicion;
        }
    }
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* nodoActual = raiz;
    Nodo* ultNodo = raiz;
    int i = 0;
    int cantOtrosHijos = 0;
    int caracter = int(clave[i]);
    int ultCaracter = caracter;
    //int letraSiguiente = int(clave.at(0));
    while(i < clave.size()){
        if (nodoActual->siguientes[caracter] != nullptr) {
            nodoActual = nodoActual->siguientes[caracter];
            i++;
            caracter=int(clave[i]);
            for(int j = 0; j < 256; j++){
                if (nodoActual->siguientes[j] != nullptr && j != caracter) {
                    ultNodo = nodoActual;
                    ultCaracter = clave[i];
                }
                if(i < clave.size()-1 && nodoActual->definicion != nullptr){
                    ultNodo = nodoActual;
                    ultCaracter = clave[i];
                }
            }
        }
    }
    //Chequeo que el nodo a eliminar no tenga otros hijos
    for(int j = 0; j < 256; j++){
        if(ultNodo->siguientes[j] != nullptr)
            cantOtrosHijos++;
    }
    if(cantOtrosHijos>=1 && ultNodo->definicion== nullptr){
        destruir(ultNodo->siguientes[ultCaracter]);
        ultNodo->siguientes[ultCaracter] = nullptr;
    }
    else if(ultNodo->definicion!= nullptr){
        delete ultNodo->definicion;
        ultNodo->definicion= nullptr;
    }

    _size--;
}

template <typename T>
int string_map<T>::size() const{
    int tamano = _size;
    return tamano;
}

template <typename T>
bool string_map<T>::empty() const{
    return raiz== nullptr;
}

template<typename T>
void string_map<T>::copiarTrie(const string_map<T>& d, Nodo *n, Nodo* nodoActual) {

    if(this->raiz== nullptr) {
        Nodo *nodo = new Nodo();
        this->raiz = nodo;
        nodoActual=this->raiz;
    }
    for(int i = 0; i < n->siguientes.size(); i++){
        if(n->siguientes[i]!= nullptr) {
            Nodo* nuevoNodo = new Nodo();
            nodoActual->siguientes[i]=nuevoNodo;
            if(n->siguientes[i]->definicion != nullptr){
                int valor=*n->siguientes[i]->definicion;
                T* def = new T(valor);
                nodoActual->siguientes[i]->definicion=def;
            }
            copiarTrie(d,n->siguientes[i],nodoActual->siguientes[i]);
        }
    }
    this->_size=d._size;

}

