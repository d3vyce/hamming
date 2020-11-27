#include <stdio.h>
#include <stdlib.h>

/*
Code par Nicolas Sudres
Groupe : Janaudy - Corazza - Sudres - Martin
*/

typedef struct Matrice {
    int x;
    int y;
    int **Matrice;
}Matrice;

Matrice MatriceVide(int n, int m);
void DisplayMatrice(Matrice A);
Matrice LireMatrice(const char * nom, Matrice A);
Matrice Control(Matrice A);
Matrice Transpose(Matrice Acontrol);

Matrice binaire(Matrice A);
Matrice motcode(Matrice A, Matrice BlocBinaire);
Matrice syndrome(Matrice MotCode, Matrice H, Matrice A);
void DisplayResult(Matrice BlocBinaire, Matrice MotCode, Matrice Syndrome);

int distanceMin(Matrice MotCode);