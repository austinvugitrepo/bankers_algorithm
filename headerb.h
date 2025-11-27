#ifndef HEADERB_H
#define HEADERB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//banker safe algorithim prototype for part g
bool safealgo(int n, int m, int* allocmtrx, int* needmtrx, int* availablev, int* safe_sequence);
// resource request algorithim protoype for part i
void resource_grant(int n, int m, int* reqvec, int reqpidx, int* allocmtrx, int* needmtrx, int* availablev);
#endif 
