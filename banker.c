#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main( int argc, char *argv[]) { //accepting cli args
printf("\n");

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

printf("\n");

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
 if(j >= 26){ // z caps at 25
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

// allocating memory for n * m max matrix
int* maxmtrx;
maxmtrx = malloc(mtrxsize * sizeof(int));

//if allocation fails
if (maxmtrx == NULL){
  fprintf(stderr, "Could not allocate memory for max matrix.\n");
  free(allocmtrx);
  fclose(f);
  return 1;
}

//read from file, add to array, then print array for max matrix 
printf("\n---> Max Matrix <---\n\n");
//label resource column with A,B,C,D....
printf("     "); //spacing so the label aligns
for(int j = 0; j < m; j++){
 if(j >= 26){ // z caps at 25
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
    int readint = fscanf(f, "%d", &maxmtrx[idx]);

    //if read fails
    if(readint != 1){
      fprintf(stderr, "Could not read array or failure while reading array.\n");
      free(maxmtrx); // free memory cuz of failure
      free(allocmtrx);
      fclose(f);
      return 1;
    }

  printf("%d ", maxmtrx[idx]);
  }
  printf("\n"); //new line for matrix 
}

// allocating memory for n * m need matrix (max - allocation)
int* needmtrx;
needmtrx = malloc(mtrxsize * sizeof(int));

//if allocation fails
if (needmtrx == NULL){
  fprintf(stderr, "Could not allocate memory for need matrix.\n");
  free(maxmtrx); // free memory cuz of failure
  free(allocmtrx);
  fclose(f);
  return 1;
}

//calculate need matrix then print array for it 
printf("\n---> Need Matrix <---\n\n");
//label resource column with A,B,C,D....
printf("     "); //spacing so the label aligns
for(int j = 0; j < m; j++){
 if(j >= 26){ // z caps at 25
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
    //calculate need matrix
    needmtrx[idx] = maxmtrx[idx] - allocmtrx[idx];
    printf("%d ", needmtrx[idx]);
  }
  printf("\n"); //new line for matrix 
}


// allocating memory for 1 * m available vector
int* availablev;
availablev = malloc(m * sizeof(int));

//if allocation fails
if (availablev == NULL){
  fprintf(stderr, "Could not allocate memory for available vector.\n");
  free(allocmtrx);
  free(maxmtrx);
  free(needmtrx); 
  fclose(f);
  return 1;
}

//read from file, add to array, then print array for max matrix 
printf("\n---> Available Vector <---\n\n");
//label resource column with A,B,C,D....
for(int j = 0; j < m; j++){
 if(j >= 26){ // z caps at 25
    printf("m%d", j);
  } else{
   printf("%c ", 'A'+ j); //print character for letters (ascii: A is 65 so and is incrementing via j)
}

}
printf("\n\n");

for(int j = 0; j < m; j++){
    //read one integer at a time
    int readint = fscanf(f, "%d", &availablev[j]);
    //if read fails
    if(readint != 1){
      fprintf(stderr, "Could not read array or failure while reading array.\n");
      free(maxmtrx); // free memory cuz of failure
      free(allocmtrx);
      free(needmtrx);
      free(availablev);
      fclose(f);
      return 1;
    }
    printf("%d ", availablev[j]);
  }

// work vector
int* workvec;
workvec = malloc(m * sizeof(int));

//if allocation fails 
if(workvec == NULL){
  fprintf(stderr, "Could not allocate memory for work vector.\n");
  free(maxmtrx); // free memory cuz of failure
  free(allocmtrx);
  free(needmtrx);
  free(availablev);
  fclose(f);
  return 1;

  }
//make work vector same as available vector 
for(int j = 0; j < m; j++){
 workvec[j] = availablev[j];
  }

// finish vector 
int* finishvec;
// have to initialize to 0 (false) as well when mallocing so i will use calloc instead
finishvec = calloc(n, sizeof(int)); // , instead of *

//if allocation fails 
if(finishvec == NULL){
  fprintf(stderr, "Could not allocate memory for finish vector.\n");
  free(maxmtrx); // free memory cuz of failure
  free(allocmtrx);
  free(needmtrx);
  free(availablev);
  free(workvec);
  fclose(f);
  return 1;

  }
// start of banker saftey algorithim portion
int safe_sequence[n]; //to hold the sequence of processes
int counter = 0; // for processes added to safe_sequence[n]

bool foundProcess; // for finding process 

do{
    foundProcess = false;
    // go through all processes
    for(int i = 0; i < n; i++){
      // if process has not finished
      if(finishvec[i] == 0){
       //we also want need <=work 
       bool can_run = true; //processes can run, go through processes
       for(int j = 0; j < m; j++){
        int idx = (i * m) + j; // for need matrix
        if(needmtrx[idx] > workvec[j]){
            can_run = false;
            break;
          }
        }
      if(can_run == true){
        // update workvec and finishvec
        for(int j = 0; j < m; j++){
         int idx = (i * m) + j;
         workvec[j] += allocmtrx[idx];
         
          }
          finishvec[i] = 1;
          safe_sequence[counter++] = i;
          foundProcess = true;
        }
      }

      

    }


  } while( foundProcess == true);

//saftey result, check if all processes are finished
printf("\n\n");
if(counter == n){
    printf("THE SYSTEM IS IN A SAFE STATE!");
  } else {
    printf("THE SYSTEM IS NOT IN A SAFE STATE!");
  }

free(allocmtrx);
free(maxmtrx);
free(needmtrx);
free(availablev);
free(workvec);
free(finishvec);
fclose(f); //close file

return 0;
}
