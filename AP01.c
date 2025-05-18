#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000 

int buscalinear(long int *vetor, long int chave, int n) {
    for (int i = 0; i < n; i++) {
        if (vetor[i] == chave)
            return i;
    }
    return -1;
}

int buscabinariai(long int *vetor, long int chave, int n) {
    int esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (vetor[meio] == chave)
            return meio;
        else if (vetor[meio] < chave)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    return -1;
}

int buscabinariar(long int *vetor, long int chave, int esquerda, int direita) {
    if (esquerda > direita)
        return -1;
    int meio = esquerda + (direita - esquerda) / 2;
    if (vetor[meio] == chave)
        return meio;
    else if (vetor[meio] < chave)
        return buscabinariar(vetor, chave, meio + 1, direita);
    else
        return buscabinariar(vetor, chave, esquerda, meio - 1);
}

long long tempoexecucaoms(clock_t inicio, clock_t fim) {
    return (fim - inicio) * 1000 / CLOCKS_PER_SEC;
}

void executar(long int *vetor, long int chave, const char *caso) {
    clock_t inicio, fim;
    int resultado;
    long long tempo;

    printf("\n %s \n", caso);

    inicio = clock();
    resultado = buscalinear(vetor, chave, N);
    fim = clock();
    tempo = tempoexecucaoms(inicio, fim);
    printf("Busca Linear: índice = %d, tempo = %lld ms\n", resultado, tempo);

    inicio = clock();
    resultado = buscabinariai(vetor, chave, N);
    fim = clock();
    tempo = tempoexecucaoms(inicio, fim);
    printf("Busca Binária Iterativa: índice = %d, tempo = %lld ms\n", resultado, tempo);

    inicio = clock();
    resultado = buscabinariar(vetor, chave, 0, N - 1);
    fim = clock();
    tempo = tempoexecucaoms(inicio, fim);
    printf("Busca Binária Recursiva: índice = %d, tempo = %lld ms\n", resultado, tempo);
}

int main() {
    long int *vetor = malloc(N * sizeof(long int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    for (long int i = 0; i < N; i++) {
        vetor[i] = i;
    }

    executar(vetor, 0, "Melhor Caso");
    executar(vetor, N - 1, "Pior Caso");
    printf("\n Caso Médio \n");

    long long total_linear = 0, total_bin_iter = 0, total_bin_rec = 0;
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        long int chave = rand() % N;

        clock_t inicio = clock();
        buscalinear(vetor, chave, N);
        clock_t fim = clock();
        total_linear += tempoexecucaoms(inicio, fim);

        inicio = clock();
        buscabinariai(vetor, chave, N);
        fim = clock();
        total_bin_iter += tempoexecucaoms(inicio, fim);

        inicio = clock();
        buscabinariar(vetor, chave, 0, N - 1);
        fim = clock();
        total_bin_rec += tempoexecucaoms(inicio, fim);
    }

    printf("Busca Linear: tempo médio = %lld ms\n", total_linear / 20);
    printf("Busca Binária Iterativa: tempo médio = %lld ms\n", total_bin_iter / 20);
    printf("Busca Binária Recursiva: tempo médio = %lld ms\n", total_bin_rec / 20);

    free(vetor);
    return 0;
}
