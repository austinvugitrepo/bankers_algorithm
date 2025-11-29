#include "headerb.h"
#include <string.h> // for memcpy
void resource_grant(int n, int m, int* reqvec, int reqpidx, int* allocmtrx, int* needmtrx, int* availablev){

bool reqrcheck = true;
int i = reqpidx;

// check request <= need 
for (int j = 0; j < m; j++){
    int idx = (i * m) + j;
    if (reqvec[j] > needmtrx[idx]){
      reqrcheck = false;
      printf("THE REQUEST CAN NOT BE GRANTED!\n");
      break;
    } else if (reqvec[j] > availablev[j]){// if above true check request <= available 
      reqrcheck = false;
      printf("THE REQUEST CAN NOT BE GRANTED!\n");
      break;

    }
    
  }
// step 3 pretend to allocate request resources to pi by modifying state 
// back up memory via allocation
int mtrxsize = m * n;
int* availableb = malloc(m * sizeof(int));
int* allocmtrxb = malloc(mtrxsize * sizeof(int));
int* needmtrxb = malloc(mtrxsize * sizeof(int));

// copy memory to backups
memcpy(availableb, availablev, m * sizeof(int));
memcpy(allocmtrxb, allocmtrx, mtrxsize * sizeof(int));
memcpy(needmtrxb, needmtrx, mtrxsize * sizeof(int));

//fake allocation  
for (int j = 0; j < m; j++) {
  int idx = (i * m) + j;
  // available = available - request
  availablev[j] -= reqvec[j];
  // allocation[i] = allocation[i] + request
  allocmtrx[idx] += reqvec[j];
  // need[i] = need[i] - request
  needmtrx[idx] -= reqvec[j];
}

//if safe allocate
int safe_sequence[n];
if(safealgo(n, m, allocmtrx, needmtrx, availablev, safe_sequence)){
   printf("THE REQUEST CAN BE GRANTED!\n");
  } else{
      printf("THE REQUEST CAN NOT BE GRANTED!\n");
      memcpy(availablev, availableb, m * sizeof(int));
      memcpy(allocmtrx, allocmtrxb, mtrxsize * sizeof(int)); //undo fake allocation
      memcpy(needmtrx, needmtrxb, mtrxsize * sizeof(int));
  }

free(availableb);
free(allocmtrxb);
free(needmtrxb);

}
