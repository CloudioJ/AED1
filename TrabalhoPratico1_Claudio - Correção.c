#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool judgeCircle(char *moves);

int main(){
    char *moves; 
    char choice;
    do{
        printf("\nWrite a command string\nU = Up\nD = Down\nL = Left\nR = Right\n\n");
        do{
            scanf("%ms", &moves);
            if (strlen(moves) < 1 || strlen(moves) > 2 * pow(10,4)){
                printf("\nSize of string outside of bounds, write again: ");
                free(moves);
                moves = NULL;
            }
        } while (strlen(moves) < 1 || strlen(moves) > 2 * pow(10,4));

        judgeCircle(moves);
        free(moves);

        printf("\nNew command? (Y/N)\n");
        scanf("%s", &choice);
    } while (toupper(choice) == 'Y');

    return 0;
}

bool judgeCircle(char *moves){
    int x = 0, y = 0;
    
    for(int i = 0; moves[i] != '\0'; i++){
        switch(toupper(moves[i])){
            case 'U':
            y++;
            break;
            case 'D':
            y--;
            break;
            case 'R':
            x++;
            break;
            case 'L':
            x--;
            break;
            default:
            printf("Command inserted not valid!");
            return false;
        }
    }

    printf("\nX: %d,Y: %d\n", x, y);

    if (x == 0 && y == 0){
        printf("\nTrue\n");
        return true;
    }
    printf("\nFalse\n");
    return false;   
}