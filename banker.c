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

// allocating memory for n * m allocation matrix
int mtrxsize = n * m; // size of matrix by combining processes and resources
int* allocmtrx;
allocmtrx = malloc(mtrxsize * sizeof(int));

//if allocation fails
if (allocmtrx == NULL){
  fprintf(stderr, "Could not allocate memory for allocation matrix.\n");
  fclose(f);
  return 1;
}

//read from file, add to array, then print array for allocation matrix 
printf("---> Allocation Matrix <---\n\n");
//label resource column with A,B,C,D....
printf("     "); //spacing so the label aligns
for(int j = 0; j < m; j++){
 if(j > 25){ // z caps at 25
    printf("m%d", j);
  } else{
   printf("%c ", 'A'+ j); //print character for letters (ascii: A is 65 so and is incrementing via j)
}

}
printf("\n\n");
for(int i = 0; i < n; i++){
//label process row
printf("%d:   ", i);

  for(int j = 0; j < m; j++){
    //index for 2D effect because I allocated memory in a 1d way
     int idx = (i * m) + j; // (row index (i in this case) * column) = you get a 2D effect and add j (column index) to simulate incrementing 
    //read one integer at a time
    int readint = fscanf(f, "%d", &allocmtrx[idx]);

    //if read fails
    if(readint != 1){
      fprintf(stderr, "Could not read array or failure while reading array.\n");
      free(allocmtrx); // free memory cuz of failure
      fclose(f);
      return 1;
    }

  printf("%d ", allocmtrx[idx]);
  }
  printf("\n"); //new line for matrix 
}

free(allocmtrx);
fclose(f);

  return 0;
}
