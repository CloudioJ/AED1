#include <stdio.h>
#include <stdbool.h>

bool ePalindrome(int cNum, int revNum) 		//Não funciona de certa forma, não consegui fazer
						                    //funcionar o print do resultado booleano, apenas pelo printf
{
    bool check;
    if (cNum == 0 || cNum - revNum != 0) 	//É feito o comparativo entre o número digitado e o inverso dele, se a subtração de um pelo
    {						                //outro resultar em 0 então é palindrome
        printf("\nNão é palindrome\n");
        check = false;				        //Se não for torna o check em falso, não funciona
    } else {
        printf("\nÉ palindrome\n");
        check = true;				        //Se for torna o check em verdadeiro, não funciona
    }
    return check;				            //Retorna o check booleano, não funciona
}

int main()
{
    int num, cNum, revNum = 0, auxNum;
    printf("Digite um número: ");
    scanf("%d", &num);
    cNum = num;
    while(num != 0)
    {
        auxNum = num % 10;			        // O número é invertido e guardado em um auxiliar para a comparação depois
        revNum = revNum * 10 + auxNum;		// Funciona normalmente
        num = num/10;				        //
    }
    printf("%d", revNum);
    ePalindrome(cNum, revNum);			    // É chamada a função para comparar os números, funciona normalmente
    return 0;
}
