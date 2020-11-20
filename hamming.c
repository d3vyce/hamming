#include "hamming.h"


Matrice MatriceVide(int n, int m) {
    Matrice *A;
    int i, j, k;

    A = (Matrice *) malloc(sizeof(Matrice));
    
    A->x = n;
    A->y = m;

    A->Matrice = (int **) malloc(n*sizeof(int*));
    for(k=0; k<n; k++) {
        A->Matrice[k] = (int *) malloc(m*sizeof(int));
    }

    for(i=0; i<A->x; i++) {
        for(j=0; j<A->y; j++) {
            A->Matrice[i][j] = 0;
        }
    }

    return *A;
}

void DisplayMatrice(Matrice A) {
    int i, j;

    for(i=0; i<A.x; i++) {
        for(j=0; j<A.y; j++) {
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
    Matrice control = MatriceVide(3, 7);

    for(i=0; i<A.x; i++) {
        for(j=A.y-A.x+1; j<A.y; j++) {
            //printf("%d-%d -> %d-%d \n", i, j, i, k); //DEBUG
            control.Matrice[k][i] = A.Matrice[i][j];
            k++;
        }
        k = 0;
    }

    for(z=A.y-A.x+1; z<A.y; z++) {
        control.Matrice[w][z] = 1;
        w++;
    }

    return control;
}

Matrice Transpose(Matrice Acontrol) {
    int i, j;
    Matrice H = MatriceVide(Acontrol.y, Acontrol.x);
    for(i=0; i<Acontrol.y; i++) {
        for(j=0; j<Acontrol.x; j++) {
            H.Matrice[i][j] = Acontrol.Matrice[j][i];
        }
    }
    return H;
}

void MotCode(Matrice A, Matrice H) {
    long int binary = 0;
    int ligne = 2, i, j, remainder, k, result = 0, w;
    int l0, l1, l2, l3;

    for (i=1 ; i<A.x ; ++i) ligne = ligne*2;

    for(i=0; i < ligne; i++) {
        k = i;
        for(j = 1; k != 0; j = j * 10) {
            remainder = k % 2;
            k /= 2;
            binary += remainder * j;
        }

        int l0 = binary/1000;
        binary = binary%1000;
        int l1 = binary/100;
        binary = binary%100;
        int l2 = binary/10;
        binary = binary%10;
        int l3 = binary;
        binary = 0;

        printf("%d%d%d%d -> ", l0, l1, l2, l3);
        
        for(w = 0; w<A.y; w++) {
            if(l0 == 1 && A.Matrice[0][w] == 1) result++;
            if(l1 == 1 && A.Matrice[1][w] == 1) result++;
            if(l2 == 1 && A.Matrice[2][w] == 1) result++;
            if(l3 == 1 && A.Matrice[3][w] == 1) result++;

            if(result%2 == 0) {
                printf("%d", 0);
            } else {
                printf("%d", 1);
            }
            result = 0;
        }

        printf(" -> ");

        //Syndrome

        printf("\n");
    }
}

void Syndrome(Matrice H) {

}

int main() {
    Matrice A, Acontrol, H;

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
    MotCode(A, H);

    return 0;
}