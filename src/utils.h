#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


double now();
void unit_checks(double *U);
double mean(double* a, int n);
double std(double* a, int n);
double* timeOf100Calls(double (*f)(double*, double, double, double, double, int), 
						double* U, double a, double b, double c, double d, int N);