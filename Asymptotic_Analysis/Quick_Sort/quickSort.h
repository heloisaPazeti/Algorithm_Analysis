#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void swap(int A[], int i, int j);
int hoarePartition(int A[], int inicio, int fim);
void quicksortHoare(int A[], int inicio, int fim);


#endif // QUICKSORT_H_INCLUDED
