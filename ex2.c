#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETRAS 100

void menu();
char* addNome(char *nome);
char* removNome(char *nome);

int quantNomes = 0;

void main(){
    int opcao = 0;
    char *nomes;
    nomes = (char *)calloc(10, sizeof(nomes));

    while (opcao != '4'){

        menu();
        opcao = getch();
        
        switch(opcao){
        case '1':
            nomes = addNome(nomes);
            quantNomes++;
            break;
        case '2':
            nomes = removNome(nomes);
            break;
        case '3':
            printf("\n%s\n", nomes);
            getch();
            break;
        }
    }
}

char* addNome(char *nome){
    char buffer[MAX_LETRAS];

    printf("Digite o nome que quer adicionar: ");
    scanf("%s", buffer);
    strcat(buffer, " ");
    nome = (char *)realloc(nome, strlen(nome)+strlen(buffer)+1);
    strcat(nome, buffer);
    return nome;
}

char* removNome(char *nome){
    char buffer[MAX_LETRAS];
    int cont, tamanho = strlen(nome);

    printf("Digite o nome que queira remover: ");
    scanf("%s", buffer);
    char *compNomes = strstr(nome, buffer);

    if(compNomes){
        for (cont = 0; cont < strlen(buffer); cont++){
            memmove(compNomes, compNomes+1, strlen(compNomes+1)+1);
        }

        if (tamanho == cont){
            nome = (char*)realloc(nome, tamanho-cont+1);
            quantNomes--;
        }
    } else {
        printf("\nNome nao consta na string\n");
    }

    return nome;
}

void menu(){
    printf("\nEscolha uma opcao\n\n");
    printf("1 - Adicionar um nome\n");
    printf("2 - Deletar um nome\n");
    printf("3 - Mostrar string\n");
    printf("4 - Sair\n");
}