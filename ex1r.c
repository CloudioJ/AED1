#include <stdio.h>

void ePalindrome(int cNum, int revNum) 								                    
{
    if (cNum == 0 || cNum - revNum != 0) 	
    {						                
        printf("\nNao e palindrome");			        
    } else {
        printf("\nE palindrome");				         
    }				            
}

int main()
{
    int num, cNum, revNum = 0, auxNum;
    printf("Digite um numero: ");
    scanf("%d", &num);
    cNum = num;
    while(num != 0)
    {
        auxNum = num % 10;			        
        revNum = revNum * 10 + auxNum;		
        num = num/10;				        
    }
    printf("%d", revNum);
    ePalindrome(cNum, revNum);			    
    return 0;
}
