#ifndef __PAP_ARRAYTREE__
#define __PAP_ARRAYTREE__

#include <iostream>
#include <assert.h>
#include <math.h>
#include "BinaryTreePositionalLogic.h"
#include "IntervalLogic.h"

template <class T>
T getNodeValue(T Arbol [], int posicion) {
    return Arbol[posicion-1];
}

template <class T>
void setNodeValue(T Arbol [], int posicion, T value) {
    Arbol[posicion-1] = value;
}

template <class T>
void actualizarArbolIterativo(T (*Generar)(T, T), T Arbol [], int sizeArbol, int posicion) {
    int pos = posicion;
    int left = getLeftChildren(sizeArbol, posicion);
    int right = getRightChildren(sizeArbol, posicion);
    cout << endl << sizeArbol << " ! " << pos << " ! " << endl;
    setNodeValue(Arbol, pos, Generar(getNodeValue(Arbol, left), getNodeValue(Arbol, right)));
    if(!isRoot(sizeArbol, pos))
        actualizarArbolIterativo(Generar, Arbol, sizeArbol, getFather(sizeArbol, pos));
}

template <class T>
void actualizarArbol(T (*Generar)(T, T),T Arbol [], int sizeArbol, int posicion, T valor) {
    int pos = firstLeaf(sizeArbol) + posicion;
    //cout << endl << sizeArbol << " ! " << posicion << " ! " << pos << endl;
    setNodeValue(Arbol, pos, valor);
    if(!isRoot(sizeArbol, pos))
        actualizarArbolIterativo(Generar, Arbol, sizeArbol, getFather(sizeArbol, pos));
}

template <class T>
T poblarArbolIterativo(T (*Generar)(T, T), T neutro, T Arbol [], int sizeArbol, T Inputs[], int sizeInputs, int posicion) {
    //Si es una hoja
    if(isLeaf(sizeArbol, posicion)) {
        bool elInputNoTieneMasValoresParaDevolver = (sizeInputs <= posicionAsLeaf(sizeArbol, posicion));
        if(elInputNoTieneMasValoresParaDevolver) {
            setNodeValue(Arbol, posicion, neutro);
        } else {
            T value = Inputs[posicionAsLeaf(sizeArbol, posicion)];
            setNodeValue(Arbol, posicion, value);
        }
    } else {
        T valorHijoIzquierdo = poblarArbolIterativo(Generar, neutro, Arbol, sizeArbol, Inputs, sizeInputs, getLeftChildren(sizeArbol, posicion));
        T valorHijoDerecho = poblarArbolIterativo(Generar, neutro, Arbol, sizeArbol, Inputs, sizeInputs, getRightChildren(sizeArbol, posicion));
        setNodeValue(Arbol, posicion, Generar(valorHijoIzquierdo, valorHijoDerecho));
    }

    return getNodeValue(Arbol, posicion);
}

//Funcion que empieze a correr el iterativo desde 0
template <typename T>
void poblarArbol(T (*Generar)(T, T), T neutro, T Arbol [], int sizeArbol, T Inputs[], int sizeInputs) {
    assert(sizeInputs <= (sizeArbol + 1)/2);
    poblarArbolIterativo(Generar, neutro, Arbol, sizeArbol, Inputs, sizeInputs, 1);
}

template <typename T>
T resolverIntervaloIterativo(T (*Generar)(T, T), T neutro, T Arbol[], int sizeArbol, int startIntervalo, int endIntervalo, int posicion) {
    assert(endIntervalo <= posicionAsLeaf(sizeArbol, sizeArbol) + 1);
    assert(startIntervalo < endIntervalo);
    T answer;

    //Eligo los descendientes mas lejanos para crear el intervalo con el cual comparar
    int comienzoIntervaloDescendants = comienzoIntervaloDescendientes(sizeArbol, posicion);
    int finalIntervaloDescendants = finalIntervaloDescendientes(sizeArbol, posicion);

    bool estaTotalmenteContenido = intervalContains(startIntervalo, endIntervalo, 
                                    comienzoIntervaloDescendants, finalIntervaloDescendants);

    //Si el nodo actual esta enteramente contenido dentro de ese intervalo
    if(estaTotalmenteContenido) {
        answer = getNodeValue(Arbol, posicion); //Dejo de iterar y devuelvo el valor actual
    } else {
        T leftAnswer = neutro;
        T rightAnswer = neutro;

        //En caso contrario, me fijo en los hijos.

        int leftChildComienzoDescendientes = comienzoIntervaloDescendientes(sizeArbol, getLeftChildren(sizeArbol, posicion));
        int leftChildFinalDescendientes = finalIntervaloDescendientes(sizeArbol, getLeftChildren(sizeArbol, posicion));
        
        bool hijoIzquierdoEsta = intervalsMeet(startIntervalo, endIntervalo, 
                                leftChildComienzoDescendientes, leftChildFinalDescendientes);

        int rightChildComienzoDescendientes = comienzoIntervaloDescendientes(sizeArbol, getRightChildren(sizeArbol, posicion));
        int rightChildFinalDescendientes = finalIntervaloDescendientes(sizeArbol, getRightChildren(sizeArbol, posicion));
        bool hijoDerechoEsta = intervalsMeet(startIntervalo, endIntervalo, 
                                rightChildComienzoDescendientes, rightChildFinalDescendientes);

        if(hijoIzquierdoEsta) leftAnswer = resolverIntervaloIterativo(
                                Generar, neutro, Arbol, sizeArbol, startIntervalo, endIntervalo, getLeftChildren(sizeArbol, posicion));

        if(hijoDerechoEsta)rightAnswer = resolverIntervaloIterativo(
                                Generar, neutro, Arbol, sizeArbol, startIntervalo, endIntervalo, getRightChildren(sizeArbol, posicion));

        answer = Generar(leftAnswer, rightAnswer);
    }
    return answer;
}

//Funcion que empieze a correr el iterativo desde 0
template <typename T>
T resolverIntervalo(T (*Generar)(T, T), T neutro, T Arbol[], int sizeArbol, int startIntervalo, int endIntervalo) {
    return resolverIntervaloIterativo(Generar, neutro, Arbol, sizeArbol, startIntervalo, endIntervalo, 1);
}

/*void printArbol(int Arbol[], int sizeArbol, bool showdepth){
    int actualDepth = -1;
    //int unidadBasica = 3;
    //int i = 0;
    //bool showdepth = true;
    cout << "TREE" << endl << "------";
    for(int posicion = 1; posicion < sizeArbol+1; posicion++){
        if(depth(posicion) != actualDepth){
            //i = 1;
            actualDepth = depth(posicion);
            cout << endl;
            if(showdepth) cout << "Profundidad : {" << actualDepth << "}" << endl;
        }else{
            for (int spaces = 0; spaces < pow(2,depth(sizeArbol+1) - actualDepth) ; ++spaces) cout << " ";
        }

        for (int spaces = 0; spaces < (pow(2,depth(sizeArbol+1) - actualDepth)) -1; ++spaces) cout << " ";
        cout << "" << Arbol[posicion-1] <<"";
    }
    cout << endl;
}*/

template <typename T>
void printArbol(T Arbol[], int sizeArbol, bool showdepth) {
    int actualDepth = -1;
    //int unidadBasica = 3;
    //int i = 0;
    //bool showdepth = true;
    cout << "TREE" << endl << "------";
    for(int posicion = 1; posicion < sizeArbol+1; posicion++) {
        if(depth(posicion) != actualDepth) {
            //i = 1;
            actualDepth = depth(posicion);
            cout << endl;
            if(showdepth) cout << "Profundidad : {" << actualDepth << "}" << endl;
        } else {
            for(int spaces = 0; spaces < pow(2, depth(sizeArbol+1) - actualDepth) ; ++spaces) cout << " ";
        }

        for(int spaces = 0; spaces < (pow(2, depth(sizeArbol+1) - actualDepth)) -1; ++spaces) cout << " ";
        cout << "" << Arbol[posicion-1] <<"";
    }
    cout << endl;
}

#endif