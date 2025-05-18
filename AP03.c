#include <stdio.h>
#include <stdlib.h>

void insertionsort(int *v, int inicio, int fim, int *comp) {
    for (int i = inicio + 1; i <= fim; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= inicio && (++(*comp), v[j] > chave)) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}


void merge(int *v, int inicio, int meio, int fim, int *comp) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *esq = malloc(n1 * sizeof(int));
    int *dir = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) esq[i] = v[inicio + i];
    for (int j = 0; j < n2; j++) dir[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        (*comp)++;
        if (esq[i] <= dir[j]) v[k++] = esq[i++];
        else v[k++] = dir[j++];
    }
    while (i < n1) {
        v[k++] = esq[i++];
        (*comp)++;
    }
    while (j < n2){
        v[k++] = dir[j++];
        (*comp)++;
    }
    free(esq);
    free(dir);
}

void mergesort(int *v, int inicio, int fim, int *comp) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergesort(v, inicio, meio, comp);
        mergesort(v, meio + 1, fim, comp);
        merge(v, inicio, meio, fim, comp);
    }
}


int medianadetres(int *v, int inicio, int fim, int *comp) {
    int meio = inicio + (fim - inicio) / 2;

    if ((++(*comp), v[inicio] > v[meio])) {
        int temp = v[inicio];
        v[inicio] = v[meio];
        v[meio] = temp;
    }
    if ((++(*comp), v[inicio] > v[fim])) {
        int temp = v[inicio];
        v[inicio] = v[fim];
        v[fim] = temp;
    }
    if ((++(*comp), v[meio] > v[fim])) {
        int temp = v[meio];
        v[meio] = v[fim];
        v[fim] = temp;
    }

    return meio;
}


int particiona(int *v, int inicio, int fim, int *comp) {
    int pivo = v[fim];
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++) {
        (*comp)++;
        if (v[j] <= pivo) {
            i++;
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
    int aux = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = aux;
    return i + 1;
}


void quicksortmedianatres(int *v, int inicio, int fim, int *comp) {
    if (inicio < fim) {
        int m = medianadetres(v, inicio, fim, comp);
        int aux = v[m];
        v[m] = v[fim];
        v[fim] = aux;

        int p = particiona(v, inicio, fim, comp);
        quicksortmedianatres(v, inicio, p - 1, comp);
        quicksortmedianatres(v, p + 1, fim, comp);
    }
}


void quicksorthibrido(int *v, int inicio, int fim, int *comp) {
    if (fim - inicio + 1 <= 5) {
        insertionsort(v, inicio, fim, comp);
        return;
    } else if (inicio < fim) {
        int m = medianadetres(v, inicio, fim, comp);
        int aux = v[m];
        v[m] = v[fim];
        v[fim] = aux;

        int p = particiona(v, inicio, fim, comp);
        quicksorthibrido(v, inicio, p - 1, comp);
        quicksorthibrido(v, p + 1, fim, comp);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int *v = malloc(n * sizeof(int));
    int *v1 = malloc(n * sizeof(int));
    int *v2 = malloc(n * sizeof(int));
    int *v3 = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        v1[i] = v[i];
        v2[i] = v[i];
        v3[i] = v[i];
    }

    int comp1 = 0, comp2 = 0, comp3 = 0;

    mergesort(v1, 0, n - 1, &comp1);
    for (int i = 0; i < n; i++) printf("%d ", v1[i]);
    printf("\n%d\n", comp1);

    quicksortmedianatres(v2, 0, n - 1, &comp2);
    for (int i = 0; i < n; i++) printf("%d ", v2[i]);
    printf("\n%d\n", comp2);

    quicksorthibrido(v3, 0, n - 1, &comp3);
    for (int i = 0; i < n; i++) printf("%d ", v3[i]);
    printf("\n%d\n", comp3);

    free(v);
    free(v1);
    free(v2);
    free(v3);

    return 0;
}
