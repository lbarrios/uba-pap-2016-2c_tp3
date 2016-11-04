#include <string>
#include <iostream>

using namespace std;

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
  for(unsigned int i = 0; i < mail.length(); i++) {
    if(trie->hijos[(int)mail[i]-(int)'A'] == NULL) {
      trie->hijos[(int)mail[i]-(int)'A'] = new Nodo();
    }
    trie = trie->hijos[(int)mail[i]-(int)'A'];
    trie->palabrasPertenecientes++;
    if(trie->finPrefijo) {
      maximo_global = max(maximo_global, trie->palabrasPertenecientes);
    }
    prefijo--;
    if(prefijo == 0) {
      trie->finPrefijo = true;
      maximo_global = max(maximo_global, trie->palabrasPertenecientes);
    }
  }
  trie->finPalabra = true;
}

int main() {
  int A;
  cin >> A;
  
  Nodo* raiz = new Nodo();
  for(int i = 0; i < A; i++) {
    string D;
    int P;
    cin >> D >> P;
    insertar(raiz, D, P); // Inserto la palabra D al trie
  }
  
  cout << maximo_global << endl;

  delete raiz;
  
  return 0;
}