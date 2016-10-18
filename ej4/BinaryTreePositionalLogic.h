#ifndef __PAP_ARRAYALGEBRA__
#define __PAP_ARRAYALGEBRA__

///////////// ALGEBRA DE POSICIONES:
///////////// TODO ESTO ES INDEPENDIENTE DEL TIPO DE ARBOL QUE ESTEMOS TRABAJANDO
///////////// FUNCIONA PARA TODO TIPO DE ARBOL

#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;

//Averigua la profundidad de una posicion
//Root tiene profundidad 0
//Como todo arbol es un subIntervalo de los arboles mas grande, es igual para todos
int depth(int posicion) {
    return floor(log2(posicion));
}

// Consigue el proximo valor de 2 cuadrado
int proximoCuadrado(int sizeArbol) {
    return pow(2, ceil(log2(sizeArbol)));
}

int proximoArbolBinario(int sizeArbol) {
    return proximoCuadrado(sizeArbol)-1;
}

// Usamos esto para asegurarnos que el tamanio de los arboles sea el correcto.
// Es decir, que sea n*2 - 1. En caso contrario, devuelve false.
//
bool sizeArbolBinario (int sizeArbol) {
    return sizeArbol == proximoArbolBinario(sizeArbol);
}

// Se asegura que la posicion no sea mas grande que el tamanio del arbol.
bool inRange(int sizeArbol, int posicion) {
    assert(sizeArbolBinario(sizeArbol));
    return (posicion > 0) and (posicion <= sizeArbol);
}

//  Consigue el primer elemento que es una hoja
int firstLeaf(int sizeArbol) {
    assert(sizeArbolBinario(sizeArbol));
    int answer = floor(sizeArbol/2) + 1;
    return answer;
}

int posicionAsLeaf(int sizeArbol, int posicion) {
    assert(inRange(sizeArbol, posicion));
    return posicion - firstLeaf(sizeArbol);
}

// Pregunta si una posicion corresponde a una hoja.
bool isLeaf(int sizeArbol, int posicion) {
    assert(sizeArbolBinario(sizeArbol));
    assert(inRange(sizeArbol, posicion));
    return depth(posicion) == depth(sizeArbol);
}

// Pregunta si una posicion corresponde a roto
bool isRoot(int sizeArbol, int posicion) {
    assert(inRange(sizeArbol, posicion));
    return posicion == 1;
}

// Consigue el hijo de la izquierda
int getLeftChildren(int sizeArbol, int posicion) {
    assert(!(isLeaf(sizeArbol, posicion)));
    int answer = ((posicion) * 2);
    return answer;
}

// Consigue el hijo de la derecha
int getRightChildren(int sizeArbol, int posicion) {
    assert(!(isLeaf(sizeArbol, posicion)));
    int answer = ((posicion) * 2) + 1;
    return answer;
}

// Consigue al padre
int getFather(int sizeArbol, int posicion) {
    assert(!(isRoot(sizeArbol, posicion)));
    int answer = (posicion/2);
    return answer;
}

int comienzoIntervaloDescendientes(int sizeArbol, int posicion) {
    int distanceToLeaves = depth(sizeArbol) - depth(posicion);
    int posicionAnswer = ((posicion) * pow(2, distanceToLeaves));
    int answer = posicionAsLeaf(sizeArbol, posicionAnswer); //Reacomodo para que el Intervalo empieze de 0
    return answer;
}

int finalIntervaloDescendientes(int sizeArbol, int posicion) {
    int distanceToLeaves = depth(sizeArbol) - depth(posicion);
    int ammountOfDescendants = pow(2, distanceToLeaves);
    int distanceRightmostFromLeftmost = ammountOfDescendants;
    int answer = comienzoIntervaloDescendientes(sizeArbol, posicion) + distanceRightmostFromLeftmost;
    return answer;
}

#endif