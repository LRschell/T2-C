#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int valor;
    char letra;
    struct Node* esq;
    struct Node* dir;
};

typedef struct Node NODO;

// prototipos
void inserir(NODO** arv, int val);
void mostrar(NODO* arv);
NODO* pesquisar(NODO* arv, int val);

void inserir(NODO** arv, int val) {
    if ( *arv == NULL ) {
        NODO* novo;
        novo = malloc(sizeof(NODO));
        novo->valor = val;   //(*novo).valor = val;
        novo->esq = NULL;
        novo->dir = NULL;

        *arv = novo;
    } else {
        //if ( val < (**arv)valor)
        if ( val < (*arv)->valor)
           //inserir(&((**arv).esq),val);
           inserir(&((*arv)->esq), val);
        else
           inserir(& ((*arv)->dir), val);
    }
}

NODO* pesquisar(NODO* arv, int val) {
    if ( arv ==NULL) return NULL;

    if ( arv->valor == val)
        return arv;
    else if ( arv->valor > val)
            return pesquisar(arv->esq, val);
         else
            return pesquisar(arv->dir, val);
}

void mostrar(NODO* arv) {
    if (arv == NULL) return;

    mostrar(arv->esq);
    printf("%d ", arv->valor);
    mostrar(arv->dir);

}

void bubbleSort(int vet[], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (vet[j] < vet[i])
            {
                int aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

int main()
{
    FILE* arq = fopen("teste.txt", "r");
    if(arq == NULL)
    {
        printf("Erro! Arquivo não encontrado!\n");
        exit(EXIT_FAILURE);
    }
    // Leitura
    char c;

    rewind(arq); // volta ao início do arquivo

    int vetor[256]= {0};
    int count = 0;

    while ((c = fgetc(arq)) != EOF)
    {
        vetor[c]++;
        if(vetor[c] == 1)
        {
            count++;
        }
    }

    int vet[count];
    memset( vet, 0, count*sizeof(int) );

    int qvar = 0;
    for(int i = 0; i<256; i++)
    {
        if(vetor[i] > 0)
        {
            vet[qvar] = vetor[i];
            qvar++;
            printf("%c: %d\n",i,vetor[i]);
        }
    }

    bubbleSort(vet, count);

    printf("\nVetor ordenado: ");
    for (int i = 0; i < count; i++)
    {
        printf(" %d ", vet[i]);
    }

    printf("\nCount: %d",count);

    fclose(arq);
    return 0;
}
