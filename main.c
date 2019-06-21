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

void padding ( char ch, int n )
{
    int i;

    for ( i = 0; i < n; i++ )
        putchar ( ch );
}

void printree( NODO* root, int level ){ //char** table, char* binary, int column
    int i;
    // Change to test for leaf
    if(root == NULL) {
        // table[column] = &node->letter;
        // table[column+1] = binary;
        // column = column + 2;
        padding ('\t', level);
        puts ("~");
    } else {
        printree(root->dir, level + 1 );
        // RIGHT
            // strcat(binary, "1");
            // gentable(node->right, table, binary, column);
        padding('\t', level );
        printf("%c:%d\n", root->letra, root->valor);
        printree(root->esq, level + 1 );
        // LEFT
            // strcat(binary, "0");
            // gentable(node->left, table, binary, column);
    }
}

int busca(NODO* root, char target, char path[])
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->letra == target)
    {
        return 1;
    }
    int buscaE = busca(root->esq, target, path);
    if(buscaE == 1)
    {
        strcat(path, "0");
        return 1;
    }
    int buscaD = busca(root->dir, target, path);
    if(buscaD == 1)
    {
        strcat(path, "1");
        return 1;
    }
    return 0;
}



int main()
{
    FILE* arq = fopen("teste.txt", "r");
    if(arq == NULL)
    {
        printf("Erro! Arquivo não encontrado!\n");
        exit(EXIT_FAILURE);
    }
    rewind(arq);

    char c;
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

    char vet[count];
    memset(vet, 0, sizeof vet);
    int qvar = 0;
    NODO* raiz[count];
    memset(raiz, NULL, sizeof raiz);

    for(int i = 0; i < 256; i++)
    {
        if(vetor[i] > 0)
        {
            inserir(&raiz[qvar], vetor[i], i);
            qvar++;
            //printf("%c: %d\n",i,vetor[i]);
        }
    }

    bubbleSort(raiz, count);
    for (int i = 0; i < count; i++)
    {
        vet[i] = raiz[i]->letra;
    }

    for(int i = count-1; i > 0; i--)
    {
        NODO* x = NULL;
        inserir(&x, raiz[i]->valor + raiz[i-1]->valor, NULL);
        x->esq = raiz[i];
        x->dir = raiz[i-1];
        raiz[i-1] = x;
        bubbleSort(raiz, i);
    }

    for(int i = 0; i < count; i++)
    {
        char path[] = {0};
        busca(*raiz,vet[i], path);
        printf("\nLetra: %c\tCodigo: %s", vet[i],strrev(path));
    }
    printf("\n");
    printree(raiz[0],0);
    fclose(arq);
    return 0;
}






















