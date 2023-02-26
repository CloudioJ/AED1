#include <stdio.h>

int main(){
    int numDegraus, numAux = 0, maneiras = 0, fib = 1;
    do{
        printf("\nDigite um número: ");
        scanf("%d", &numDegraus);
        if (numDegraus > 45 || numDegraus < 1){
            printf("Número digitado inválido");
        }
    } while(numDegraus > 45 || numDegraus < 1);

    for (int i = 0; i < numDegraus; i++){
        maneiras = fib + numAux;
        numAux = fib;
        fib = maneiras;
    }
    
    printf("Existem %d maneiras de subir.", maneiras);

    return maneiras;
}