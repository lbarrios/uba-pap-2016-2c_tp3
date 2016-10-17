#include<iostream>
#include<vector>

using namespace std;

//Devuelve la querie que esta en la diapo 21
int querie(int c1, int c2, int a1, int a2, vector<vector<int> >* arreglo_acumulado){
  return ((*arreglo_acumulado)[c2][a2] - (*arreglo_acumulado)[c1][a2] - (*arreglo_acumulado)[c2][a1] + (*arreglo_acumulado)[c1][a1]);
}

int main(int argc, char const *argv[]) {
  int A,C,Q;
  cin >> C >> A >> Q;
  vector<vector<int> > sueldos(A, vector<int>(C));
  vector<vector<int> > arreglo_acumulado(A+1, vector<int>(C+1));
  for(int i = 0; i < C; i++){
    for (int j = 0; j < A; j++) {
      cin >> sueldos[i][j];
    }
  }
  for(int i = 0; i < C+1; i++){
    arreglo_acumulado[i][0] = 0;
  }
  for(int j = 0; j < A+1; j++){
    arreglo_acumulado[0][j] = 0;
  }
  for(int i = 0; i < C; i++){
    for(int j = 0; j < A; j++){
      arreglo_acumulado[i+1][j+1] = sueldos[i][j] + arreglo_acumulado[i][j+1] + arreglo_acumulado[i+1][j] - arreglo_acumulado[i][j];
    }
  }
  int c1,c2,a1,a2;
  for(int i = 0; i < Q; i++){
    cin >> c1 >> a1 >> c2 >> a2;
    int q = querie(c1,c2,a1,a2, &arreglo_acumulado);
    cout << q << endl;
  }
  return 0;
}
