#include <iostream>
#include <assert.h>
#include <math.h>
#include "BinaryTreePositionalLogic.h"
#include "BinaryTreeManipulation.h"
#include "IntervalLogic.h"
#include <bits/stdc++.h>

using namespace std;

struct elementContainer{
    int biggestElement;
    int secondBiggestElement;
};

std::ostream &operator<<(std::ostream &os, elementContainer const &a) {
    os << a.biggestElement << "+" << a.secondBiggestElement;
    return os;
}

elementContainer ecMax(elementContainer a, elementContainer b){
    elementContainer newEc;
    newEc.biggestElement = max(a.biggestElement, b.biggestElement);
    newEc.secondBiggestElement = max(
                                    min(
                                        a.biggestElement,
                                        b.biggestElement
                                        ),
                                    max(
                                        a.secondBiggestElement,
                                        b.secondBiggestElement
                                        )
                                    );
    return newEc;
}

int main(int argc , char *argv[])
{
    ///    ETAPA 1,
    /// CARGO LOS DATOS
    //cout << "start"<< endl;
    string str;
    int cantidadDias; int cantidadIntervalos;int sizeArbol;
    elementContainer *Arbol;
    //Matriz target; Matriz *inputs; Matriz *Arbol;

    cin >> cantidadDias;
    cin >> cantidadIntervalos;
    //cin >>target;

    elementContainer* inputs = new elementContainer[cantidadDias];
    for(int x=0; x < cantidadDias; x++){
            elementContainer ec;
            cin >> ec.biggestElement;
            ec.secondBiggestElement = 0;
          //  cout << ec.biggestElement<< endl;
            inputs[x] = ec;
    }

    /// ETAPA 2,
    /// CREO EL ARBOL Y LO POBLO CON LA INFORMACION QUE TENEMOS
    sizeArbol = (proximoCuadrado(cantidadDias)*2)-1;
    Arbol =  new elementContainer[sizeArbol];

    elementContainer ecNeutro;
    ecNeutro.biggestElement = 0;
    ecNeutro.secondBiggestElement = 0;
    poblarArbol(ecMax, ecNeutro, Arbol, sizeArbol, inputs, cantidadDias);

   // printArbol(Arbol, sizeArbol, false);

    //actualizarArbol(iMax, Arbol,sizeArbol,1,15);

    //printArbol(Arbol, sizeArbol, false);
    /// ETAPA 3,
    /// PARA TODOS LOS INTERVALOS QUE ESTAN DENTRO DE LOS DATOS QUE SUBIMOS,
    /// CALCULAMOS LA MULTIPLICACION Y NOS FIJAMOS SI ES TARGET

    int comienzoIntervalo,finintervalo;
    elementContainer ecAnswer;
    for(int x=0; x < cantidadIntervalos; x++){
        cin >> comienzoIntervalo >> finintervalo;
        ecAnswer = resolverIntervalo(ecMax, ecNeutro,Arbol,sizeArbol,comienzoIntervalo,finintervalo);
        cout << ecAnswer.biggestElement + ecAnswer.secondBiggestElement << endl;
    };


    delete [] inputs;
    delete [] Arbol;

    return 0;
}
