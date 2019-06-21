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
void inserir(NODO** arv, int val, char let);
NODO* pesquisar(NODO* arv, int val);

void inserir(NODO** arv, int val, char let)
{
    if ( *arv == NULL )
    {
        NODO* novo;
        novo = malloc(sizeof(NODO));
        novo->valor = val;   //(*novo).valor = val;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->letra = let;

        *arv = novo;
    }
    else
    {
        //if ( val < (**arv)valor)
        if ( val < (*arv)->valor)
            //inserir(&((**arv).esq),val);
            inserir(&((*arv)->esq), val, let);
        else
            inserir(&((*arv)->dir), val, let);
    }
}

NODO* pesquisar(NODO* arv, int val)
{
    if ( arv ==NULL)
        return NULL;

    if ( arv->valor == val)
        return arv;
    else if ( arv->valor > val)
        return pesquisar(arv->esq, val);
    else
        return pesquisar(arv->dir, val);
}

void bubbleSort(NODO* vet[], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (vet[j]->valor < vet[i]->valor)
            {
                NODO* aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

void mostrar(NODO* arv)
{
    if (arv == NULL)
        return;

    mostrar(arv->esq);
    printf("%d ", arv->letra);
    mostrar(arv->dir);

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

    int vetor[256] = {0};
    int count = 0;

    while ((c = fgetc(arq)) != EOF)
    {
        vetor[c]++;
        if(vetor[c] == 1)
        {
            count++;
        }
    }

    int qvar = 0;
    NODO* raiz[256] = {NULL};
    for(int i = 0; i < 256; i++)
    {
        if(vetor[i] > 0)
        {
            inserir(&raiz[qvar], vetor[i], i);
            qvar++;
            printf("%c: %d\n",i,vetor[i]);

        }
    }

    bubbleSort(raiz, count);



    printf("\nVetor ordenado: ");
    for (int i = 0; i < count; i++)
    {
        printf(" %c ", raiz[i]->letra);
    }

    printf("\nCount: %d",count);


    for(int i = count-1; i > 0; i--)
    {
        NODO* x = NULL;
        inserir(&x, raiz[i]->valor + raiz[i-1]->valor, NULL);
        x->esq = raiz[i];
        x->dir = raiz[i-1];
        raiz[i-1] = x;
        bubbleSort(raiz, i);
    }

    printf("\n\n\nValor final: %d", raiz[0]->valor);


    fclose(arq);
    return 0;
}






















