#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void *pBuffer);
void insertName(void *pBuffer, void *sentinel);
void removeName(void *pBuffer, void *sentinel);
void listNames(void *pBuffer, void *sentinel);
void searchName(void *pBuffer, void *sentinel);

int main(){
    void *pBuffer, *sentinel, *aux;

    //Aloca o tamanho que vai ser necessário para a manipulação dos ponteiros
    pBuffer = (void *)malloc(sizeof(int) + sizeof(void **));
    sentinel = (void *)malloc(sizeof(int) + sizeof(void **)*2);

    //Inicializa os ponteiros
    *(int *)sentinel = 0;
    *(void **)(sentinel + sizeof(int)) = NULL;
    *(void **)(sentinel + sizeof(int) + sizeof(void **)) = NULL;
    *(void **)(pBuffer + sizeof(int)) = NULL;

    do{
        menu(pBuffer);

        switch(*(int *)pBuffer){
            case 1:
            //Insere um nome
            insertName(pBuffer, sentinel);
            break;
            case 2:
            //Remove um nome
            removeName(pBuffer, sentinel);
            break;
            case 3:
            //Procura por um nome
            searchName(pBuffer, sentinel);
            break;
            case 4:
            //Mostra todos os nomes
            listNames(pBuffer, sentinel);
            break;
            default:
            break;
        }
    } while(*(int *)pBuffer > 0 && *(int *)pBuffer < 5);

    //Libera os ponteiros alocados no fim da execução
    if(*(int *)sentinel != 0){
        aux = *(void **)(sentinel + sizeof(int) + sizeof(void **));
        do{
            if (*(int *)sentinel == 1){
                free(aux);
                *(int *)sentinel -= 1;
            } else {
                aux = *(void **)(aux + sizeof(char)*20 + sizeof(int)*2);
                void *aux2 = *(void **)(aux + sizeof(char)*20 + sizeof(int)* + sizeof(void **));
                free(aux2);

                *(int *)sentinel -= 1;
            }
        } while(*(int *)sentinel != 0);
    }

    return 0;
} 

void menu(void *pBuffer){
    //Menu
    *(int *)pBuffer = 0;
    printf("\n1 - Add name\n");
    printf("2 - Remove name\n");
    printf("3 - Search name\n");
    printf("4 - List names\n");
    printf("5 - Exit\n\n");
    scanf("%d", &*(int *)pBuffer);
    return;
}

void insertName(void *pBuffer, void *sentinel){

    //Aloca o tamanho de uma pessoa para node
    void *node = (void *)malloc(sizeof(int)*2+sizeof(char)*20+sizeof(void**)*2);
    void *temp = NULL;

    //Checa se node foi alocado apropriadamente
    if (!node){
        printf("\nMemory couldn't be allocated!");
        return;
    }

    //Insere os dados da pessoa
    printf("Insert name: ");
    scanf("%s", (char*)node);
    printf("\nInsert age: ");
    scanf("%d", &*(int*)(node + sizeof(char)*20));
    printf("\nInsert phone: ");
    scanf("%d", &*(int*)(node + sizeof(char)*20 + sizeof(int)));

    //Node do tamanho "passado", que fica depois do endereço inteiro da pessoa recebe NULL, 
    //e o "proximo", que vem após, também recebe NULL
    *(void **)(node + sizeof(char)*20 + sizeof(int)*2) = NULL;
    *(void **)(node + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **)) = NULL;

    if (*(int *)sentinel == 0){
        //Se for a primeira pessoa ela estara no inicio e no fim
        *(void **)(sentinel + sizeof(int)) = node;
        *(void **)(sentinel + sizeof(int) + sizeof(void**)) = node;

        //Incrementa o contador
        (*(int *)sentinel) += 1; 
        return;
    }

    //pBuffer recebe o endereço da primeira pessoa
    pBuffer = *(void **)(sentinel + sizeof(int)); 

    //Enquanto existir elementos no pBuffer
    do{
        //Se a comparação entre o nome inserido e o nome em pBuffer for menor que 0
        if(strcmp((char *)node, (char *)pBuffer) < 0){
        *(void **)(node + sizeof(char)*20 + sizeof(int)*2) = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2);
        *(void **)(node + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **)) = pBuffer;

        //Se o contador for maior que 1 e o endereço da primeira pessoa não for nulo então
        //temp recebe o endereço da primeira pessoa e o endereço da proxima pessoa de temp recebe node
            if(*(int *)sentinel > 1 && *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2) != NULL) {
                temp = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2);
                *(void **)(temp + sizeof(char)*20 + sizeof(int)*2 + sizeof(void**)) = node;
            }

            //O endereço da primeira pessoa em pBuffer recebe node
            *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2) = node;

            //Se o endereço da pessoa atual em node for nulo então o endereço da primeira pessoa recebe node
            if(*(void **)(node + sizeof(char)*20) + sizeof(int)*2 == NULL){
                *(void **)(sentinel + sizeof(int)) = node;
            }

            //Se for a primeira pessoa no contador e a pessoa seguinte em pBuffer for nulo então o endereço da ultima pessoa no sentinela recebe pBuffer
            if(*(int *)sentinel == 1 && *(void **)(pBuffer + sizeof(char)*20+sizeof(int)*2+sizeof(void**)) == NULL){
                *(void **)(sentinel + sizeof(int) + sizeof(void **)) = pBuffer;
            }

            //Incrementa 1 no contador
            *(int *)sentinel += 1;
            return;
        }

        //Se o endereço da proxima pessoa for igual a nulo então temp recebe o mesmo endereço de pBuffer
        if(*(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **)) == NULL){
            temp = pBuffer;
        }

        //pBuffer vai para o próximo
        pBuffer = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));
    } while(pBuffer != NULL);

    //A posição da pessoa atual no node recebe o endereço de temp
    *(void **)(node + sizeof(char)*20 + sizeof(int)*2) = temp;
    //O endereço da proxima pessoa em temp recebe o endereço de node
    *(void **)(temp + sizeof(char)*20 + sizeof(int)*2 + sizeof(void**)) = node;
    //O endereço da ultima pessoa no sentinela recebe o endereço de node
    *(void **)(sentinel + sizeof(int) + sizeof(void **)) = node;

    //Incrementa no contador
    *(int *)sentinel += 1;
    return;
}

void removeName(void *pBuffer, void *sentinel){
    void *auxPerson;
    void *aux = (void *)malloc(sizeof(char)*20);

    //pBuffer recebe o endereço da primeira pessoa
    pBuffer = *(void **)(sentinel + sizeof(int));

    //Se nenhuma pessoa foi adicionada retorna um aviso
    if (*(int *)sentinel == 0){
        printf("\nNo person has been added yet!\n");
        return;
    }

    //Escolhe a pessoa a ser removida por nome
    printf("\nPerson you want to remove: ");
    scanf("%s", (char *)aux);

    //Procura pela pessoa inserida, enquanto o conteúdo de pBuffer não for NULL
    do{
        //Compara a string inserida com o nome em pBuffer, se são iguais então:
        if (strcmp((char *)aux, (char *)pBuffer) == 0){
            //Se a pessoa no endereço de pBuffer não for nulo então auxPerson recebe esse mesmo endereço e o próximo do auxiliar recebe o próximo de pBuffer
            if (*(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2) != NULL){
                auxPerson = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2);
                *(void **)(auxPerson + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **)) = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));
            } else {
                //Se for nulo então o primeiro endereço com pessoa recebe a proxima pessoa de pBuffer
                *(void **)(sentinel + sizeof(int)) = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));
            }

            //Se a proxima pessoa de pBuffer não for nulo então auxPerson recebe esse valor
            if (*(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **)) != NULL){
                auxPerson = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));
                *(void **)(auxPerson + sizeof(char)*20 + sizeof(int)*2) = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2);
            } else {
                //Se for nulo, então o ultimo endereço de pessoa recebe o proximo de pBuffer
                *(void **)(sentinel + sizeof(int) + sizeof(void **)) = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void**));
            }

            //Decrementa o contador
            *(int *)sentinel -= 1;

            //Libera os ponteiros, tirando os dados da pessoa da memória
            free(pBuffer);
            free(aux);
            return;
        }

        //Vai para o endereço da proxima pessoa
        pBuffer = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));

    } while (pBuffer != NULL);

    //Caso o nome não exista na lista
    printf("Name not found!");
    free(aux);
}

void listNames(void *pBuffer, void *sentinel){
    //Se nenhuma pessoa foi adicionada ainda, retorna avisando
    if(*(int *)sentinel == 0){
        printf("\nNo person has been added yet!\n");
        return;
    }
    //pBuffer aponta para a primeira pessoa
    pBuffer = *(void **)(sentinel + sizeof(int));

    //Enquanto pBuffer não for NULL, printa as informações
    do{
        printf("\nName: %s\n", (char *)pBuffer);
        printf("Age: %d\n", *(int *)(pBuffer + sizeof(char)*20));
        printf("Phone: %d\n\n", *(int *)(pBuffer + sizeof(char)*20 + sizeof(int)));
        printf("--------------------\n\n");

        //pBuffer recebe o endereço da proxima pessoa
        pBuffer = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));
    } while (pBuffer != NULL);
}

void searchName(void *pBuffer, void *sentinel){
    //Cria um ponteiro pra receber o nome e comparar
    void *name = (void *)malloc(sizeof(char)*20);

    //Retorna um aviso caso não exista uma pessoa na lista ainda
    if (*(int *)sentinel == 0){
        printf("\nNo person has been added yet!\n");
        free(name);
        return;
    }

    //Usuario insere nome da pessoa que busca
    printf("Insert person you're searching for: ");
    scanf("%s", (char *)name);

    //pBuffer aponta para o inicio
    pBuffer = *(void **)(sentinel + sizeof(int));

    //Enquanto pBuffer não for NULL, a busca e comparativo é feita pelo nome, se encontrado, é printado os dados
    do{
        if (strcmp((char *)name, (char *)pBuffer) == 0){
            printf("--------------------");
            printf("\nName: %s\n", (char *)pBuffer);
            printf("Age: %d\n", *(int *)(pBuffer + sizeof(char)*20));
            printf("Phone: %d\n\n", *(int*)(pBuffer + sizeof(char)*20 + sizeof(int)));
            printf("--------------------\n\n");
            free(name);

            return;
        }
        pBuffer = *(void **)(pBuffer + sizeof(char)*20 + sizeof(int)*2 + sizeof(void **));
    } while(pBuffer != NULL);

    //Se não for encontrada a pessoa, retorna um aviso e libera o ponteiro alocado para o nome auxiliar da função
    printf("\nPerson not found!\n\n");
    free(name);
}