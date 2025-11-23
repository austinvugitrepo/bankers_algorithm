#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[]) { //accepting cli args

//argument checker
if(argc != 2){
  fprintf(stderr, "Too many arguments or none was provided! Only 1 file can be used for this program.\n");
  return 1;
}

printf("Exact amount of arguments have been provided\n");

  return 0;
}
