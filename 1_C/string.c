#include <stdio.h>

//배열의 마지막은 \0이기 때문에 마지막을 찾을 때까지 while문을 반복하고 그 동안 cnt로 카운팅 한 후 반환해서 글자 수를 반환한다.
int strlen_p(char *p) {
    int cnt = 0;
    while(*p != '\0'){
        p++;
        cnt++;
    }
    return cnt;
}

//파라미터가 배열로 들어온다면 for문을 통해 \0이 되는 인덱스를 찾아 반환하면 인덱스 값이 문자열의 총 길이이다.
int strlen_a(char str[]){
    int i = 0;
    for(i = 0; str[i] != '\0'; i++);
    return i;
}
/*
str1, str2를 포인터로 받아 복사할 str2가 0이 되어 false가 되기 전까지 while문을 반복하며
포인터를 통한 실제 값을 대입하고 각각의 포인터 주솟값을 ++시켜 다음 글자로 넘어가게 한다.
*/
void strcpy_p(char *str1, char *str2){
    while(*str2){
        *str1 = *str2;
        str1++;
        str2++;
    }
}

/*
str1, str2를 배열로 받아와 복사할 str2의 길이만큼 for문을 반복하면서
i 인덱스를 이용해 하나하나 값을 집어넣는다. 마지막 \0이 되었을 때 for문이 반복되지 않으므로
마지막으로 i 인덱스에 값을 복사한다.
*/
void strcpy_a(char str1[], char str2[]){
    int i = 0;
    for(i = 0; str2[i] != '\0'; i++){
        str1[i] = str2[i];
    }
    str1[i] = str2[i];
}

/*
str1이후에 str2를 붙여야한다. str1의 마지막 주솟값에 접근해야하기 때문에
while문을 통해 str의 주솟값에 접근해서 마지막 주솟값을 알아낸다.
이후 뒤에 str2가 끝날때까지 str1의 마지막 주솟값부터 str2의 값을 대입하고
각 주솟값을 1씩 증가시켜 str2의 마지막까지 str1 뒷부분에 복사한다.
*/
void strcat_p(char *str1, char *str2){
    while(*str1){
        str1++;
    }
    while(*str2){
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = *str2;
}

/*
str1의 마지막 주솟값에 접근하기 위해 for문을 돌리고
다시 str2의 마지막 주솟값까지 접근하기 위해 for문을 돌린다.
이때 str1에 마지막 주솟값인 i와 0부터 str2의 마지막 주솟값까지 접근하는 j를 이용해
str1[i+j] 에 str2[j] 를 대입한다. 
*/
void strcat_a(char str1[], char str2[]){
    int i = 0;
    for(i = 0; str1[i] != '\0'; i++);
    int j = 0;
    for(j = 0; str2[j] != '\0'; j++){
        str1[i+j] = str2[j];
    }
    str1[i+j] = str2[j];
    
}

/*
result=0 으로 설정해두고, str1가 끝날 때까지 while문을 돌리면서
만약 값을 비교했을 때 대소가 비교되면 result에 값을 넣고 break;
비교가 되지 않으면 str1, str2의 주솟값을 하나씩 증가시킨다.
마지막까지 비교되지 않으면 처음 설정한대로 result = 0
*/
int strcmp_p(char *str1, char *str2){
    int result = 0;
    while (*str1){
        if(*str1 > *str2){
            result = 1;
            break;
        } else if(*str1 < *str2){
            result = -1;
            break;
        }
        str1++;
        str2++;
    }
    return result;
}

/**
 * 동일하게 result = 0 으로 설정해두고, for문으로 str1이 끝날 때까지 반복
 * 인덱스로 접근해 동일하게 값의 대소가 있으면 break;
 * 인덱스값을 증가시키면서 그대로 끝나면 result = 0
**/
int strcmp_a(char str1[], char str2[]){
    int result = 0;
    int i = 0;
    for(i = 0; str1[i] != '\0'; i++){
        if(str1[i] > str2[i]){
            result = 1;
            break;
        } else if (str1[i] < str2[i]){
            result = -1;
            break;
        }
    }
    return result;
}


int main()
{
	int		len1, len2;
	char	str1[20], str2[20];

	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

    strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	strcat_p(str1, ", World!");
	strcat_a(str2, ", World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);

    int strcmp1 = strcmp_p(str1, str2);
    int strcmp2 = strcmp_a(str1, str2);
	printf("strcmp: p=%d, a=%d\n", strcmp1, strcmp2);

	return 0;
}