#include <string>
#include <iostream>

using namespace std;

//int borrados = 0;
//int creados = 0;
int maximo_global = 0; // Guarda el maximo valor de palabrasPertenecientes de los nodos que son finPrefijo.

struct Nodo {
  Nodo() {
    palabrasPertenecientes = 0;
    finPalabra = false;
    finPrefijo = false;
    for(int i = 0; i < 58; i++) {
      hijos[i] = NULL;
    }
  }
  ~Nodo() {
    for(int i = 0; i < 58; i++) {
      if(hijos[i] != NULL) {
        delete hijos[i];
      }
    }
  }
  Nodo* hijos[58]; //ascii de la A mayuscula hasta la z minuscula. en el medio hay 6 caracteres q no sirven... u.u
  int palabrasPertenecientes; // La cantidad de palabras que usan todo el prefijo del trie hasta el nodo
  bool finPalabra; // Indica si el nodo es el fin de un mail del trie
  bool finPrefijo; // Indica si el nodo es el fin del prefijo de un mail del trie
};

void insertar(Nodo* trie, string mail, int prefijo) {
  //cout << "palabra a insertar: " << mail << ", y prefijo: " << prefijo << endl;
  for(unsigned int i = 0; i < mail.length(); i++) {
    //cout << "voy por la letra " << mail[i] << endl;
    if(trie->hijos[(int)mail[i]-(int)'A'] == NULL) {
      //cout << "creo el nodo porq no existia" << endl;
      trie->hijos[(int)mail[i]-(int)'A'] = new Nodo();
     // creados++;
    }
    trie = trie->hijos[(int)mail[i]-(int)'A'];
    trie->palabrasPertenecientes++;
    //cout << "le sume uno a palabras pertenecientes, ahora vale: " << trie->palabrasPertenecientes << endl;
    if(trie->finPrefijo) {
      //cout << "era un fin de prefijo, actualizo el maximo global" << endl;
      maximo_global = max(maximo_global, trie->palabrasPertenecientes);
      //cout << "el maximo global ahora vale " << maximo_global << endl;
    }
    prefijo--;
    //cout << "le reste uno a prefijo, y ahora vale " << prefijo << endl;
    if(prefijo == 0) {
      //cout << "estoy en el final del prefijo, le pongo true a fin de prefijo y actualizo el maximo global" << endl;
      trie->finPrefijo = true;
      maximo_global = max(maximo_global, trie->palabrasPertenecientes);
      //cout << "el maximo global ahora vale " << maximo_global << endl;
    }
  }
  trie->finPalabra = true;
  //cout << "le pongo fin de palabra" << endl;
}

/*void borrar(Nodo* ptr) {
  cout << "entre a borrar" << endl;
  for(int i = 0; i < 58; i++) {
    if(ptr->hijos[i] != NULL) {
      cout << "este hijo existe. " << (char)(i+(int)'A') << ". lo vamos a borrar" << endl;
      borrar(ptr->hijos[i]);
    }
  }
  cout << "ya borre todos los hijos, ahora borro el puntero." << endl;
  delete ptr;
  borrados++;
}*/

int main() {
  int A;
  cin >> A;
  
  Nodo* raiz = new Nodo();
  //creados++;
  for(int i = 0; i < A; i++) {
    string D;
    int P;
    cin >> D >> P;
    insertar(raiz, D, P);
  }
  
  cout << maximo_global << endl;

  delete raiz;

  //cout << "borre " << borrados << " punteros, de " << creados << " punteros creados" << endl;
  
  return 0;
}