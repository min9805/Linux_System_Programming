#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char buf[256];
	char* temp;
	FILE* fr = fopen(argv[2], "rt");
	int line = 1;

	while( fgets(buf, 256, fr) )
	{
		if( (temp = strstr(buf, argv[1])) != NULL)
		{
			printf("%d: %s", line, buf);
		}
		line++;
	}

	fclose(fr);
	return 0;
}
