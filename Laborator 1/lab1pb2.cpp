#include <iostream>
#include <fstream>

using namespace std;

const int INF = 1e9; // INF = 1*10^9

int main() {
    int n, adiacenta[101][101], distanta[101][101];

    // Citire din fisier
    ifstream f("matrice.in");
    

    f >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            f >> adiacenta[i][j];
            //Matricea distantelor
            if (i == j) 
                distanta[i][j] = 0;
            else 
                if (adiacenta[i][j] == 1) distanta[i][j] = 1;
            else distanta[i][j] = INF;
        }
    }
    f.close();

    // a. Determinarea nodurilor izolate
    cout << "Noduri izolate: ";
    bool exista_izolate = false;
    int grad_init = 0; // Pentru cerinta b

    for (int i = 1; i <= n; i++) {
        int grad_curent = 0;
        for (int j = 1; j <= n; j++) {
            if (adiacenta[i][j] == 1) grad_curent++;
        }

        if (grad_curent == 0) {
            cout << i << " ";
            exista_izolate = true;
        }

        if (i == 1) grad_init = grad_curent;
    }
    if (!exista_izolate) cout << "nu exista";
    cout << endl;





    // b. Verificare graf regular
    bool regular = true;
    for (int i = 2; i <= n; i++) {
        int grad_curent = 0;
        for (int j = 1; j <= n; j++) {
            if (adiacenta[i][j] == 1) grad_curent++;
        }
        if (grad_curent != grad_init) {
            regular = false;
            break;
        }
    }
    cout << "Graful " << (regular ? "este" : "nu este") << " regular." << endl;





    // c. Determinarea matricei distantelor 
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (distanta[i][k] + distanta[k][j] < distanta[i][j])
                    distanta[i][j] = distanta[i][k] + distanta[k][j];

    cout << "Matricea distantelor:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (distanta[i][j] == INF) cout << "INF ";
            else cout << distanta[i][j] << "   ";
        }
        cout << endl;
    }

    // d. Verificare daca este conex
    bool conex = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (distanta[i][j] == INF) {
                conex = false;
                break;
            }
        }
    }
    cout << "Graful " << (conex ? "este" : "nu este") << " conex." << endl;

    return 0;
}