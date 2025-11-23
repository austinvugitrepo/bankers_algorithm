#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[]) { //accepting cli args

//argument checker
if(argc != 2){
  fprintf(stderr, "Too many arguments or none was provided! Only 1 file can be used for this program.\n");
  return 1;
}
//opening file
FILE *f = fopen(argv[1], "r"); //opening file in read mode
 
//error checking for if file does not exist
if(f == NULL){
    fprintf(stderr, "Can't open file.\n");
    return 1;
  }

printf("file exists!\n");

fclose(f);

  return 0;
}
