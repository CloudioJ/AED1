#include <stdio.h>
#include <stdbool.h>

bool ePalindrome(int cNum, int revNum) 		
						                    
{
    bool check;
    if (cNum == 0 || cNum - revNum != 0) 	
    {						                
        printf("\nNão é palindrome\n");
        check = false;				        
    } else {
        printf("\nÉ palindrome\n");
        check = true;				        
    }
    return check;				            
}

int main()
{
    int num, cNum, revNum = 0, auxNum;
    printf("Digite um número: ");
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
