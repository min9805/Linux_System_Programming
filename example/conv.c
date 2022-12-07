#include<stdio.h>

void ten_to_two_j(unsigned n) {
    if (n < 2) { // n==1 (이전 n이 2이거나 3)
        printf("%d", n);
    }
    else {
        ten_to_two_j(n / 2);
        printf("%d", n % 2);
    }
}

int main() {
	int num;
	printf("정수를 입력해주세요\n");
	scanf_s("%d", &num);

	printf("10진수 : %d\n", num); // 서식문자 : %d
	printf("8진수 : %o\n", num); // 서식문자 : %o 
	printf("16진수(소문자) : %x\n", num); // 서식문자 : %x
	printf("16진수(대문자) : %X\n", num); // 서식문자 : %X
	
	printf("8진수(표기) : %#o\n", num); // 서식문자 : %#o
	printf("16진수(표기) : %#x\n", num); // 서식문자 : %#x

	printf("8진수(8자리까지 0으로 채움) : %0.8o\n", num); // 서식문자 : %0.8o
	printf("16진수(8자리까지 0으로 채움) : %0.8x\n", num); // 서식문자 : %0.8x

	unsigned int num;
    printf("정수를 입력해주세요\n");
    scanf_s("%d", &num);

    printf("2진수 변환 : ");
    //이진수 출력
    for (int i = 7; i >= 0; --i) { //8자리 숫자까지 나타냄
        int result = num >> i & 1;
        printf("%d", result);
    }
	//stdlib.h _itoa, _itoa_s
	printf("10진수 %d를 2진수로 변환 : %s\n", n, itoa(n, arr, 2));
    printf("10진수 %d를 8진수로 변환 : %s\n", n, itoa(n, arr, 8));
    printf("10진수 %d를 16진수로 변환 : %s\n", n, itoa(n, arr, 16));

}

