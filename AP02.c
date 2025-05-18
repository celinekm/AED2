#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b, int *mov) {
    if (a != b) {
        int temp = *a;
        *a = *b;
        *b = temp;
        (*mov)++;
    }
}

// Selection Sort
void selection_sort(int v[], int n, int *cmp, int *mov) {
    *cmp = 0;
    *mov = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*cmp)++;
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(&v[i], &v[min], mov);
        }
    }
}

// Bubble Sort
void bubble_sort(int v[], int n, int *cmp, int *mov) {
    *cmp = 0;
    *mov = 0;
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - 1 - i; j++) {
            (*cmp)++;
            if (v[j] > v[j + 1]) {
                swap(&v[j], &v[j + 1], mov);
                trocou = true;
            }
        }
        if (!trocou) break;
    }
}

// Insertion Sort
void insertion_sort(int v[], int n, int *cmp, int *mov) {
    *cmp = 0;
    *mov = 0;
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key) {
            (*cmp)++;
            v[j + 1] = v[j];
            (*mov)++;
            j--;
        }
        if (j >= 0) (*cmp)++;  
        if (j + 1 != i) {
            v[j + 1] = key;
            (*mov)++;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int *original = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &original[i]);
    }

    // Selection Sort
    int *v1 = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) v1[i] = original[i];
    int cmp1, mov1;
    selection_sort(v1, n, &cmp1, &mov1);
    printf("%d %d\n", cmp1, mov1);
    free(v1);

    // Bubble Sort
    int *v2 = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) v2[i] = original[i];
    int cmp2, mov2;
    bubble_sort(v2, n, &cmp2, &mov2);
    printf("%d %d\n", cmp2, mov2);
    free(v2);

    // Insertion Sort
    int *v3 = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) v3[i] = original[i];
    int cmp3, mov3;
    insertion_sort(v3, n, &cmp3, &mov3);
    printf("%d %d\n", cmp3, mov3);
    free(v3);

    free(original);
}
