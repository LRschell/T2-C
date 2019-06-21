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

//insere um nodo na arvore
void inserir(NODO** arv, int val, char let)
{
    if ( *arv == NULL )
    {
        NODO* novo;
        novo = malloc(sizeof(NODO));
        novo->valor = val;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->letra = let;

        *arv = novo;
    }
    else
    {
        if ( val < (*arv)->valor)
            inserir(&((*arv)->esq), val, let);
        else
            inserir(&((*arv)->dir), val, let);
    }
}

//ordena o vetor do maior valor para o menor
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

//procura o char na arvore e altera o path com o caminho ate o char
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
    int vetor[1256] = {0};
    int count = 0;
    char msgTemp[1256];
    int cont = 0;

    //leitura da mensagem e da frequencia
    while ((c = fgetc(arq)) != EOF)
    {
        msgTemp[cont] = c;
        cont++;
        vetor[c]++;
        if(vetor[c] == 1)
        {
            count++;
        }
    }

    //cria uma copia da mensagem
    char msg[cont];
    for(int i = 0; i < cont; i++)
    {
        msg[i] = msgTemp[i];
    }

    char vet[count];
    memset(vet, 0, sizeof vet);
    int qvar = 0;
    NODO* raiz[count];
    memset(raiz, NULL, sizeof raiz);

    //insere em um vetor de arvore um nodo contendo o char e a frequencia
    for(int i = 0; i < 256; i++)
    {
        if(vetor[i] > 0)
        {
            inserir(&raiz[qvar], vetor[i], i);
            qvar++;
            printf("%c: %d\n",i,vetor[i]);
        }
    }

    //cria um vetor com as letras da mensagem
    bubbleSort(raiz, count);
    for (int i = 0; i < count; i++)
    {
        vet[i] = raiz[i]->letra;
    }

    //cria um nodo com a soma dos valores de i e i-1, guarda na posicao i-1 e ordena
    for(int i = count-1; i > 0; i--)
    {
        NODO* x = NULL;
        inserir(&x, raiz[i]->valor + raiz[i-1]->valor, NULL);
        x->esq = raiz[i];
        x->dir = raiz[i-1];
        raiz[i-1] = x;
        bubbleSort(raiz, i);
    }

    FILE * fp;
    fp = fopen ("saida.piz","w");

    //printa a tabela de codigo para cada letra
    for(int i = 0; i < count; i++)
    {
        char path[] = {0};
        busca(*raiz,vet[i], path);
        printf("Letra: %c\tCodigo: %s\n", vet[i],strrev(path));
        fprintf(fp,"Letra: %c\tCodigo: %s\n", vet[i],path);
    }

    //printa a mensagem compactada
    printf("Mensagem comprimida: ");
    for(int i = 0; i < cont; i++)
    {
        char path[] = {0};
        busca(*raiz, msg[i], path);
        fprintf(fp,"%s", strrev(path));
        printf("%s", path);
    }

    fclose (fp);
    fclose(arq);
    return 0;
}
