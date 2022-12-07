#include <stdio.h>
#include <stdlib.h>

int power(int a, int b){
    if(b == 0){
        return 1;
    } else{
        return a * power(a, b - 1);
    }
}

int main(int argc, char* argv[]){
    int a, b;
    a = atoi(argv[1]);
    b = atoi(argv[2]);

    int result = power(a,b);
    printf("%d\n", result);
}
