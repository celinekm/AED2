#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXP 1000
#define MAXT 21 

int chaveordenacao[128];

void normalizarp(char palavras[][MAXT], int n) {
    char maiusculas[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char minusculas[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < n; i++) {
        int tam = strlen(palavras[i]);
        for (int j = 0; j < tam; j++) {
            for (int k = 0; k < 26; k++) {
                if (palavras[i][j] == maiusculas[k]) {
                    palavras[i][j] = minusculas[k];
                    break;
                }
            }
        }
    }
}


int maiort(char palavras[][MAXT], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        int tam = strlen(palavras[i]);
        if (tam > max) max = tam;
    }
    return max;
}


void padronizart(char palavras[][MAXT], int n, int tammax) {
    for (int i = 0; i < n; i++) {
        int tam = strlen(palavras[i]);
        for (int j = tam; j < tammax; j++) {
            palavras[i][j] = ' ';
        }
        palavras[i][tammax] = '\0';
    }
}


void countingsort(char A[][MAXT], char B[][MAXT], int n, int pos) {
    int C[27] = {0}; 
    int i, j;

    for (i = 0; i <= 26; i++)
        C[i] = 0;
    for (j = 0; j < n; j++) {
        char ch = A[j][pos];
        int idx = (ch == ' ') ? 0 : chaveordenacao[(int)ch] + 1;
        C[idx]++;
    }

    for (i = 1; i <= 26; i++)
        C[i] = C[i] + C[i - 1];
    for (i = 0; i <= 26; i++) {
        printf("%d", C[i]);
        if (i < 26) printf(" ");
    }
    printf("\n");

    for (j = n - 1; j >= 0; j--) {
        char ch = A[j][pos];
        int idx = (ch == ' ') ? 0 : chaveordenacao[(int)ch] + 1;
        int p = C[idx] - 1;
        strcpy(B[p], A[j]);
        C[idx]--;
    }

    for (i = 0; i < n; i++) {
        strcpy(A[i], B[i]);
    }
}

void radixsort(char A[][MAXT], int n, int d) {
    char B[MAXP][MAXT];
    for (int i = d - 1; i >= 0; i--) {
        countingsort(A, B, n, i);
    }
}

int main() {
    int N;
    char chave[27];
    char palavras[MAXP][MAXT];
    scanf("%d", &N);
    scanf("%s", chave);
    for (int i = 0; i < 26; i++) {
        chaveordenacao[(int)chave[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        scanf("%s", palavras[i]);
    }
    normalizarp(palavras, N);
    for (int i = 0; i < N; i++) {
        printf("%s.\n", palavras[i]);
    }

    int d = maiort(palavras, N);
    padronizart(palavras, N, d);
    printf("%d\n", d);

    radixsort(palavras, N, d);

    for (int i = 0; i < N; i++) {
        printf("%s\n", palavras[i]);
    }

    return 0;
}
