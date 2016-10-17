#ifndef __PAP_INTERVALS__
#define __PAP_INTERVALS__
#include <math.h>
#include <stdlib.h>

//Verifica que los intervalos coincidan
bool intervalsMeet(int x1, int x2, int y1, int y2){
    assert(x1 < x2);
    assert(y1 < y2);
    int lengthFirstInterval;

    if (y1 < x1){
        lengthFirstInterval = y2 - y1;
    }else{
        lengthFirstInterval = x2 - x1;
    }
    int distanceBetweenStarts = abs(x1-y1);

    return distanceBetweenStarts < lengthFirstInterval;
}

//Verifica que un intervalo contenga al otro
bool intervalContains(int x1,int x2, int y1, int y2){
    bool ladoIzquierdoEsta = y1 >= x1;
    bool ladoDerechoEsta =  y2 <= x2;

    return ladoIzquierdoEsta and ladoDerechoEsta;
}


#endif
