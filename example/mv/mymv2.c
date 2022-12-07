#include <stdio.h>

int main()
{
  if ( rename("./mymv2.c", "./mv/mymv2.c") )
    perror( NULL );
  return 0;
}
