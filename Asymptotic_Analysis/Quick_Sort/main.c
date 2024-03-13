#include "quickSort.h"

int main()
{
    // ARRUMAR AQUI PRA SEGUIR O EXEMPLO DELA
    int A[5];

    A[0] = 25;
    A[1] = 1;
    A[2] = 50;
    A[3] = 1000;
    A[4] = 2;

    quicksortHoare(A, 0, 4);

    for(int i = 0; i < 5; i++)
        printf("%d ", A[i]);

    return 0;
}
