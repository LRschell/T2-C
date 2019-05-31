#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* arq = fopen("teste.txt", "r");
    if(arq == NULL) {
        printf("Erro! Arquivo não encontrado!\n");
        exit(EXIT_FAILURE);
    }
    // Leitura
    char c;

    rewind(arq); // volta ao início do arquivo

    int vetor[256]= {0};
    int count;

    while ((c = fgetc(arq)) != EOF){
        vetor[c]++;
    }

    for(int i = 0; i<256;i++){
        if(vetor[i] > 0){
            printf("%c: %d\n",i,vetor[i]);
        }
    }

    fclose(arq);
    return 0;
}
