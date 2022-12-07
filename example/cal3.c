#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE	*src;
	int		ch;
    int     sum = 0;
    int     min = 999;
    int     max = 0;

	if (argc != 2)  {
		fprintf(stderr, "Usage: %s source\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

    int num;
    int cnt =0;

	while (fscanf(src, "%d", &num) != EOF)  {
        cnt++;
        sum = sum + num;
        if(num > max){
            max = num;
        }
        if(num < min){
            min = num;
        }
	}
    printf("MAX : %d\n", max);
    printf("MIN : %d\n", min);
    printf("AVG : %d\n", sum/cnt);

	fclose(src);
}
