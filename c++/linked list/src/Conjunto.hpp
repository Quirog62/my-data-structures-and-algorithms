
#include "Conjunto.h"

//FUNCIONAS PUBLICAS

template <class T>
Conjunto<T>::Conjunto():_cardinal(0),_raiz(){
}

template <class T>
Conjunto<T>::~Conjunto() {
    Nodo *nodoTemp=_raiz;
    if(this->_raiz!= nullptr)
        destruir(nodoTemp);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* nodoTemp = _raiz;
    while(nodoTemp!=nullptr && clave!=nodoTemp->valor){
        if(clave < nodoTemp->valor)
            nodoTemp=nodoTemp->izq;
        else nodoTemp=nodoTemp->der;
    }
    if(nodoTemp!= nullptr) return clave==nodoTemp->valor;
    else return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!pertenece(clave)){
        Nodo* nodoPadre = nullptr;
        Nodo* nodoTemp = _raiz;
        Nodo* nodoNuevo = new Nodo(clave);
        while(nodoTemp!= nullptr){
            nodoPadre=nodoTemp;
            if(clave < nodoTemp->valor)
                nodoTemp=nodoTemp->izq;
            else nodoTemp=nodoTemp->der;
        }
        nodoNuevo->padre=nodoPadre;
        if(nodoPadre== nullptr)
            _raiz=nodoNuevo;
        else if(nodoNuevo->valor < nodoPadre->valor)
            nodoPadre->izq=nodoNuevo;
        else
            nodoPadre->der=nodoNuevo;
        _cardinal++;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo* nodoAEliminar = _raiz;
    //Busco el nodo
    while(nodoAEliminar!=nullptr && clave!=nodoAEliminar->valor){
        if(clave < nodoAEliminar->valor)
            nodoAEliminar=nodoAEliminar->izq;
        else nodoAEliminar=nodoAEliminar->der;
    }
    //Si el nodo existe y se puede eliminar, entonces le resto 1 al cardinal
    if(nodoAEliminar!= nullptr) _cardinal--;
    //Procedo a eliminar
    if(nodoAEliminar->izq== nullptr) {
        rotar(nodoAEliminar, nodoAEliminar->der);
        delete nodoAEliminar;
    }
    else if(nodoAEliminar->der== nullptr) {
        rotar(nodoAEliminar, nodoAEliminar->izq);
        delete nodoAEliminar;
    }
    else{
        Nodo* nodoTemp = nodoAEliminar->der;
        //Busco el minimo en la parte derecha del nodo
        while(nodoTemp->izq!= nullptr){
            nodoTemp=nodoTemp->izq;
        }

        if(nodoTemp->padre!=nodoAEliminar){
            rotar(nodoTemp,nodoTemp->der);
            nodoTemp->der=nodoAEliminar->der;
            nodoTemp->der->padre=nodoTemp;
        }
        rotar(nodoAEliminar,nodoTemp);
        nodoTemp->izq=nodoAEliminar->izq;
        nodoTemp->izq->padre=nodoTemp;
        delete nodoAEliminar;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* nodoTemp = _raiz;
    //Busco el nodo al que le tengo que buscar el sucesor
    while(nodoTemp!=nullptr && clave!=nodoTemp->valor){
        if(clave < nodoTemp->valor)
            nodoTemp=nodoTemp->izq;
        else nodoTemp=nodoTemp->der;
    }

    if(nodoTemp->der!= nullptr)
        return min(nodoTemp->der);
    Nodo* nodoTempAntecesor = nodoTemp->padre;
    while(nodoTempAntecesor!= nullptr && nodoTemp==nodoTempAntecesor->der){
        nodoTemp=nodoTempAntecesor;
        nodoTempAntecesor=nodoTempAntecesor->padre;
    }
    return nodoTempAntecesor->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* nodoTemp = _raiz;
    while(nodoTemp->izq!= nullptr){
        nodoTemp=nodoTemp->izq;
    }
    return nodoTemp->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* nodoTemp = _raiz;
    while(nodoTemp->der!= nullptr){
        nodoTemp=nodoTemp->der;
    }
    return nodoTemp->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

//FUNCIONES PRIVADAS

template <class T>
void Conjunto<T>::destruir(Nodo *n) {
    if(n!= nullptr){
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }
}

template <class T>
const T& Conjunto<T>::min(Nodo *n) {
    while(n->izq!= nullptr){
        n=n->izq;
    }
    return n->valor;
}

template <class T>
void Conjunto<T>::rotar(Nodo *n1, Nodo *n2) {
    if(n1->padre== nullptr)
        _raiz=n2;
    else if(n1==n1->padre->izq)
        n1->padre->izq=n2;
    else n1->padre->der=n2;
    if(n2!= nullptr)
        n2->padre=n1->padre;
}