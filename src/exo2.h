#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <pmmintrin.h>
#include <immintrin.h> 

void print_m256d(__m256d vec);
double vect_norm4(double *U, double a, double b, double c, double d, int n);
void unit_check_vect_norm4();