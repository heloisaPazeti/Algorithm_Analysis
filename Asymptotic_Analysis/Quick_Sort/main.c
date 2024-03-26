#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define maxSize 1000000
typedef int TypeData;

/////////////////////////////////// QUICK EXPLANATION

    // TER O ARRAY DE ELEMENTOS
    // ENCONTRAR UM ELEMENTO EM ALGUMA POSIÇÃO DO ARRAY (PIVO)
    // PEGA UM INDEX INICIAL E UM FINAL
    // ELES AVANÇAM EM DIREÇÃO UM DO OUTRO [startIndex -> .. pivô .. <- endIndex]
    // COMPARAÇÃO ENTRE ELES E O PIVO
    // O QUE FOR MAIOR QUE O PIVO FICA NA DIREITA, MENOR PARA A ESQUERDA
    // QUANDO OS INDEX SE ENCONTRAM RETONA-SE O INDEX DO ENCONTRO


    // OBS: PARA ABRANGER TODOS OS CASOS FOI UTILIZADO UMA LISTA ENCADEADA QUE, PORTANTO, VARIA O TAMANHO.

/////////////////////////////////// DECLARATIONS

int HoarePartition(int A[], int startIndex, int endIndex);
void QuickSort(int A[], int startIndex, int endIndex);
void Swap(int A[], int i, int j);

typedef struct _doubly_List List;
typedef struct _doubly_node Node;
List *List_Create();
Node *Node_Create(TypeData val);
bool List_IsEmpty(List *L);
void List_AddLast(List *L, TypeData val);
int List_GetSize(List *L);
void List_Print(List *L);

void BuildArray(List* L, int*);
void CountTime(List* L, int times);
void PrintArray(List* L);

/////////////////////////////////// MAIN

int main()
{
    char values[maxSize];                           // STRING WITH A MAX SIZE
    char *pch;                                      // PONTEIRO PARA SEPARAR STRING
    List *L;                                        // LISTA ENCADEADA
    L = List_Create();

    scanf("%[^\n]", values);                        // RECEBE TODOS OS VALORES QUE IRÃO ENTRAR NA LISTA

    pch = strtok (values," ");                      // COMEÇA A SEPARAR ESSES VALORES A CADA ESPAÇO
    while (pch != NULL)                             // ENQUANTO AINDA TIVER NUMEROS CONTINUAR REPARTINDO
    {
        List_AddLast(L, atoi(pch));                 // ADICIONAR CADA VALOR DENTRO DA LISTA
        pch = strtok (NULL, " ");                   // MOVER O PONTEIRO
    }

    //CountTime(L, 10);                               // TEMPO DE EXECUÇÃO N VEZES
    PrintArray(L);                                  // PRINTA LISTA ORDENADA


    return 0;
}

/////////////////////////////////// CODE

int HoarePartition(int A[], int startIndex, int endIndex)
{
    int pivo = A[startIndex];               // ESCOLHE ARBITRARIAMENTE O PIVO
    int i = startIndex + 1;                 // startIndex É APÓS O PIVO
    int j = endIndex;                       // ESCOLHE endIndex

    while (i <= j)                          // ENQUANTO NÃO SE ATRAVESSAM
    {
        while (i <= j && A[i] <= pivo)      // AVANÇA I ATÉ ENCONTRAR VALOR MAIOR/IGUAL QUE PIVO OU PASSAR J
            i = i + 1;

        while (i <= j && A[j] > pivo)       // VOLTA J ATÉ ENCONTRAR VALOR MENOR QUE PIVO OU PASSAR I
            j = j - 1;

        if (i < j)                          // SE J FOR MENOR ELES TROCAM DE LUGAR
            Swap(A, i, j);
    }

    Swap(A, startIndex, j);                 // TROCAM I E J DE LUGAR
    return j;
}

void QuickSort(int A[], int startIndex, int endIndex)
{
    if (startIndex < endIndex)                              // SE NÃO FOSSE O CODIGO DEVERIA SER INVERTIDO
    {
        int q = HoarePartition(A, startIndex, endIndex);    // PEGA O INDEX EM QUE SE ENCONTRAM
        QuickSort(A, startIndex, q - 1);                    // FAZ DE NOVO PARA UM MENOR QUE O INDEX DE ENCONTRO
        QuickSort(A, q + 1, endIndex);                      // FAZ DE NOVO PARA UM MAIOR QUE O INDEX DE ENCONTRO
    }
}

/////////////////////////////////// HELPERS

void Swap(int A[], int i, int j)                            // TROCA VALORES DE DOIS INDEX
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

/////////////////////////////////// LINKED LIST

typedef struct _doubly_node                                 // ESTRUTURA DO NÓ DA LISTA
{
    TypeData val;
    struct _doubly_node *prev;
    struct _doubly_node *next;

} Node;

typedef struct _doubly_List                                 // ESTRUTURA DA LISTA
{
    Node *begin;
    Node *end;
    Node *cursor;
    int size;

} List;


Node *Node_Create(TypeData val)                             // CRIA UM NOVO NÓ
{
    Node *node = (Node*)calloc(1, sizeof(Node));
    node -> next = NULL;
    node -> prev = NULL;
    node -> val = val;

    return node;
}

List *List_Create()                                         // INICIALIZA A LISTA
{
    List *L = (List*)calloc(1, sizeof(List));

    L -> begin = NULL;
    L -> end = NULL;
    L -> size = 0;

    return L;
}

void List_AddLast(List *L, TypeData val)                    // ADICIONA NOVO VALOR NO ULTIMO ESPAÇO
{
    Node *p = Node_Create(val);
    p -> prev = L -> end;

    if(List_IsEmpty(L))
        L -> begin = p;
    else
        L -> end -> next = p;

    L -> end = p;
    L -> size++;
}

bool List_IsEmpty(List *L)                                  // CONFERE SE LISTA VAZIA
{
    return (L -> size <= 0);
}

int List_GetSize(List *L)                                   // PEGA O TAMANHO DA LISTA
{
    return L -> size;
}

void List_Print(List *L)                                    // PRINTA A LISTA
{
    Node *p = L->begin;

    while(p != NULL)
    {
        printf("%d ", p -> val);
        p = p -> next;
    }
}


/////////////////////////////////// ARRAY AND COUNT TIME

void BuildArray(List* L, int* array)                        // CRIA O ARRAY USADO NO QUICK SORT
{
    int i = 0;
    Node *r = L -> begin;                                   // PRIMEIRO ELEMENTO DA LISTA
    while(r != NULL)                                        // ENQUANTO NÃO CHEGAR AO FINAL DA LISTA
    {
        array[i] = r -> val;                                // COLOCA O VALOR NO ARRAY
        r = r -> next;                                      // PASSA PRO PRÓXIMO
        i++;                                                // AVANÇA NO INDEX
    }
}

void CountTime(List* L, int times)                          // CONTA O TEMPO DE EXECUÇÃO
{
    for(int i = 0; i < times; i++)                              // CONTA N VEZES
    {
        int array[List_GetSize(L)];                             // CRIAR ARRAY DO TAMANHO CERTO
        BuildArray(L, array);                                   // COLOCA OS VALORES

        clock_t t = clock();                                    // TEMPO DE INICIAL
        QuickSort(array, 0, List_GetSize(L)-1);
        printf("%lf\n", ((double)clock()-t)/((CLOCKS_PER_SEC)));
    }
}

void PrintArray(List* L)
{
    int array[List_GetSize(L)];                     // CRIAR ARRAY COM O TAMANHO CERTO DE ELEMENTOS
    BuildArray(L, array);                           // CONSTROI ARRAY BASEADO NO TAMANHO DA LISTA
    QuickSort(array, 0, List_GetSize(L)-1);
    for(int j = 0; j < List_GetSize(L); j++)        // PRINTANDO OS VALORES ORDENADO DO ARRAY
        printf("%d ", array[j]);
}
