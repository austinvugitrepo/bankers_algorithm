#include "headerb.h"

bool safealgo(int n, int m, int* allocmtrx, int* needmtrx, int* availablev, int* safe_sequence) {

// work vector
int* workvec;
workvec = malloc(m * sizeof(int));

//if allocation fails
if(workvec == NULL){
  fprintf(stderr, "Could not allocate memory for work vector.\n");
  free(allocmtrx);
  free(needmtrx);
  free(availablev);
  return false;

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
  free(allocmtrx);
  free(needmtrx);
  free(availablev);
  free(workvec);
  return false;

  }
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
// safety result, check if all processes are finished  
bool isSafe = (counter == n);
free(workvec);
free(finishvec);

 return isSafe;
}
