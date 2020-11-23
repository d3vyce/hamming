#include <stdio.h>
#include <stdlib.h>

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
int MotCode(Matrice A, Matrice H);