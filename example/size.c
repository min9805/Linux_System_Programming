#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	DIR				*dp;
	struct dirent	*dep;
	struct stat	statbuf;
    int size = atoi(argv[1]);

	if ((dp = opendir(".")) == NULL)  {
		perror("opendir");
		exit(0);
	}

	while (dep = readdir(dp))  {
        if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0){
			continue;
        }

        if (lstat(dep->d_name, &statbuf) < 0)  {
			perror("lstat");
			continue;
		}
        printf("%s\t%ld\n", dep->d_name,statbuf.st_size);
	}
	
	closedir(dp);
}

