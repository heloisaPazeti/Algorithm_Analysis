#include "quickSort.h"

//***********************FUNÇÕES AUXILIARES***********************
void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
//***********************QUICKSORT DE HOARE******************************
int hoarePartition(int A[], int inicio, int fim) {
    int pivo = A[inicio];
    int i = inicio + 1;
    int j = fim;

    while (i <= j) {
        while (i <= j && A[i] <= pivo) {
            i = i + 1;
        }

        while (i <= j && A[j] > pivo) {
            j = j - 1;
        }

        if (i < j) {
            swap(A, i, j);
        }
    }
    swap(A, inicio, j);
    return j;
}

void quicksortHoare(int A[], int inicio, int fim) {
    if (inicio < fim) {
        int q = hoarePartition(A, inicio, fim);
        quicksortHoare(A, inicio, q - 1);
        quicksortHoare(A, q + 1, fim);
    }
}

