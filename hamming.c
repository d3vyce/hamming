#include "hamming.h"

Matrice MatriceVide(int n, int m) {
    Matrice *A;
    int i, j, k;

    A = (Matrice *) malloc(sizeof(Matrice));
    
    A->x = n;
    A->y = m;

    A->Matrice = (int **) malloc(n*sizeof(int*));
    for(k = 0; k < n; k++) {
        A->Matrice[k] = (int *) malloc(m*sizeof(int));
    }

    for(i = 0; i < A->x; i++) {
        for(j = 0; j < A->y; j++) {
            A->Matrice[i][j] = 0;
        }
    }

    return *A;
}

void DisplayMatrice(Matrice A) {
    int i, j;

    for(i = 0; i < A.x; i++) {
        for(j = 0; j < A.y; j++) {
            printf("%d ", A.Matrice[i][j]);
        }
        printf("\n");
    }
}

Matrice LireMatrice(const char * nom, Matrice A) {
    FILE *fichier = fopen(nom, "r");
    int x, y, poids, j=0;
    
    while(fscanf(fichier, "%d %d", &x, &y) != EOF) {
        A.Matrice[x][y] = 1;
    }

    return A;
}

Matrice Control(Matrice A) {
    int i, j, k = 0, z, w = 0;
    Matrice control = MatriceVide(A.x-1, A.y);

    for(i = 0; i < A.x; i++) {
        for(j = A.y-A.x+1; j < A.y; j++) {
            control.Matrice[k][i] = A.Matrice[i][j];
            k++;
        }
        k = 0;
    }

    for(z = A.y-A.x+1; z < A.y; z++) {
        control.Matrice[w][z] = 1;
        w++;
    }

    return control;
}

Matrice Transpose(Matrice Acontrol) {
    int i, j;
    Matrice H = MatriceVide(Acontrol.y, Acontrol.x);
    
    for(i = 0; i < Acontrol.y; i++) {
        for(j = 0; j < Acontrol.x; j++) {
            H.Matrice[i][j] = Acontrol.Matrice[j][i];
        }
    }
    return H;
}

Matrice binaire(Matrice A) {
    Matrice Binaire;
    int i, ligne = 2, k, n, count = A.x-1;

    for (i = 1 ; i < A.x ; ++i) ligne = ligne*2;

    Binaire = MatriceVide(ligne, A.x);

    for(i = 0; i < ligne; i++) {
        for(n = i; n > 0; n = n >> 1) {
            if(n & 1) {
                Binaire.Matrice[i][count] = 1;
            }
            count--;
        }
        count = A.x-1;
    }

    return Binaire;
}

Matrice motcode(Matrice A, Matrice BlocBinaire) {
    Matrice MotCode;
    int i, j, k, result = 0;

    MotCode = MatriceVide(BlocBinaire.x, A.y);

    for(i = 0; i < BlocBinaire.x; i++) {
        for(j = 0; j < A.y; j++) {
            for(k = 0; k < A.x; k++) {
                if(BlocBinaire.Matrice[i][k] == 1 && A.Matrice[k][j] == 1) result++;
            }

            if(result%2 != 0) {
                MotCode.Matrice[i][j] = 1;
            }

            result = 0;
        }
    }

    return MotCode;
}

Matrice syndrome(Matrice MotCode, Matrice H, Matrice A) {
    Matrice Syndrome = MatriceVide(MotCode.x, H.y);
    int i, j, k, result = 0;

    for(i = 0; i < MotCode.x; i++) {
        for(j = 0; j<A.x-1; j++) {
            for(k = 0; k<A.y; k++) {
                if(MotCode.Matrice[i][j] == 1 && H.Matrice[k][j] == 1) result++;
            }

            if(result%2 != 0) {
                Syndrome.Matrice[i][j] = 1;
            }
            result = 0;
        }
    }

    return Syndrome;
}

void DisplayResult(Matrice BlocBinaire, Matrice MotCode, Matrice Syndrome) {
    int i, j;

    for(i = 0; i < BlocBinaire.x; i++) {
        for(j = 0; j < BlocBinaire.y; j++) {
            printf("%d", BlocBinaire.Matrice[i][j]);
        }
        printf(" | ");
        for(j = 0; j < MotCode.y; j++) {
            printf("%d", MotCode.Matrice[i][j]);
        }
        printf(" | ");
        for(j = 0; j < Syndrome.y; j++) {
            printf("%d", Syndrome.Matrice[i][j]);
        }
        printf("\n");
    }
}

int distanceMin(Matrice MotCode) {
    int i, j, distance_min = 99, distance = 0;

    for(i = 0; i < MotCode.x; i++) {
        for(j = 0; j < MotCode.y; j++) {
            if(MotCode.Matrice[i][j] == 1) distance++;
        }

        if(distance < distance_min && distance != 0) {
            distance_min = distance;
        }

        distance = 0;
    }

    return distance_min;
}

int main() {
    Matrice A, Acontrol, H, BlocBinaire, MotCode, Syndrome;
    int distance_min;

    printf("Matrice Systématique :\n");
    A = MatriceVide(4, 7);
    LireMatrice("matrice.txt", A);
    DisplayMatrice(A);
    
    printf("\n Matrice de controle H :\n");
    Acontrol = Control(A);
    DisplayMatrice(Acontrol);

    printf("\n Matrice H(transposé) :\n");
    H = Transpose(Acontrol);
    DisplayMatrice(H);

    printf("\n Matrice Syndrome :\n");
    BlocBinaire = binaire(A);
    MotCode = motcode(A, BlocBinaire);
    Syndrome = syndrome(MotCode, H, A);
    DisplayResult(BlocBinaire, MotCode, Syndrome);

    
    printf("\nDistance minimal : %d \n", distanceMin(MotCode));
    printf("Nombre d'erreurs détectables : %d \n", distanceMin(MotCode)-1);
    printf("Nombre d'erreurs corrigeables : %d \n", (distanceMin(MotCode)-1)/2);

    return 0;
}