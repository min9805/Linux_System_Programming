#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrrchr (char *str, char c){
    char i, c2;
    int tmp = -1;
    if( c <= 90){
        c2 = c + 32;
    } else 
        c2 = c - 32;

    for(i = 0; i < strlen(str); i++){
        if (str[i] == c || str[i] == c2){
            tmp = i;
        }
    }
    return str + tmp;
}

int main() {
    char str[] = "Hello hello HELLO";
    char *str2 = mystrrchr(str, 'l');
    printf("Last %c in %s : %s\n", 'l', str, str2);
}
