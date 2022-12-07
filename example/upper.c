#include <stdio.h> 
#include <string.h>

void strupper(char str[]){
	int i;
	for(i = 0; i <= strlen(str); i++){
		if(str[i] > 96 && str[i] < 123) {
			str[i] = str[i] - 32;
		} 
	}
	printf("%s\n", str);
}

int main(){	
	char str[] = "hello, world!";
	printf("%s\n", str);
	strupper(str);
	printf("%s\n", str);
}
