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

//reading processes
int n;
int process = fscanf(f, "%d", &n);

//checker for if not able to read processes
if(process != 1){
  fprintf(stderr, "Could not read processes.\n");
  fclose(f);
  return 1;
  }
//print result
printf("There are %d processes in the system.\n", n);
  
//reading resources
int m;
int resource = fscanf(f, "%d", &m);

//checker for if not able to read resources
if(resource != 1){
  fprintf(stderr, "Could not read resources.\n");
  fclose(f);
  return 1;
  }
//print result
printf("There are %d resources in the system.\n", m);


fclose(f);

  return 0;
}
