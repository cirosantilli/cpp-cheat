#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int main(){

  printf("%d\n",INT_MAX);
  printf("%ld\n",LONG_MAX);
  printf("%ld\n",strtol("2000000000",NULL,10L));
  printf("%ld\n",strtol("4000000000",NULL,10L));

  return 0;

}
