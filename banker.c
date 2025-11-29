#include "headerb.h"

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
bool process = fscanf(f, "%d", &n);

//checker for if not able to read processes
if(process != true){
  fprintf(stderr, "Could not read processes.\n");
  fclose(f);
  return 1;
  }
//print result
printf("There are %d processes in the system.\n", n);
  
//reading resources
int m;
bool resource = fscanf(f, "%d", &m);

//checker for if not able to read resources
if(resource != true){
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
    bool readint = fscanf(f, "%d", &allocmtrx[idx]);

    //if read fails
    if(readint != true){
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
    bool readint = fscanf(f, "%d", &maxmtrx[idx]);

    //if read fails
    if(readint != true){
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

//read from file, add to array, then print array for available vector  
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
    bool readint = fscanf(f, "%d", &availablev[j]);
    //if read fails
    if(readint != true){
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

printf("\n\n");
// start of banker saftey algorithim portion
int safe_sequence[n]; //to hold the sequence of processes
if(safealgo(n, m, allocmtrx, needmtrx, availablev, safe_sequence)){
    printf("THE SYSTEM IS IN A SAFE STATE!"); 
  } else {
    printf("THE SYSTEM IS NOT IN A SAFE STATE!");
  }

printf("\n\n");


// request vector
int* reqvec;
reqvec = malloc(m * sizeof(int));

//if allocation fails 
if(reqvec == NULL){
  fprintf(stderr, "Could not allocate memory for request vector.\n");
  free(maxmtrx); // free memory cuz of failure
  free(allocmtrx);
  free(needmtrx);
  free(availablev);
  fclose(f);
  return 1;

  }
// request process index
int reqpidx;
//reading index
bool readprocid = fscanf(f, "%d:", &reqpidx);
if(readprocid != true){
 fprintf(stderr, "Could not read request process index.\n");  
 free(allocmtrx);
 free(maxmtrx);
 free(needmtrx);
 free(availablev);
 free(reqvec);
 fclose(f);
 return 1;

  }

//read from file, add to array, then print array for request vector  
printf("\n---> Request Vector <---\n\n");
//label resource column with A,B,C,D....
for(int j = 0; j < m; j++){
 if(j >= 26){ // z caps at 25
    printf("m%d", j);
  } else{
   printf("%c ", 'A'+ j); //print character for letters (ascii: A is 65 so and is incrementing via j)
}

}

printf("\n\n");

printf("%d:", reqpidx);
for(int j = 0; j < m; j++){
    //read one integer at a time
    bool readint = fscanf(f, "%d", &reqvec[j]);
    //if read fails
    if(readint != true){
      fprintf(stderr, "Could not read array or failure while reading array.\n");
      free(allocmtrx);
      free(maxmtrx);
      free(needmtrx);
      free(availablev);
      free(reqvec);
      fclose(f); //close file
     return 1;
    }
    printf("%d ", reqvec[j]);
  }
printf("\n\n");
// start of resource-request algorithim
resource_grant(n, m, reqvec, reqpidx, allocmtrx, needmtrx, availablev);

printf("\n\n");
free(allocmtrx);
free(maxmtrx);
free(needmtrx);
free(availablev);
free(reqvec);
fclose(f); //close file

return 0;
}
