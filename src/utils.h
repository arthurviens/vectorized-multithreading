#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


double now();

void unit_checks(double *U);

double mean(double* a, int n);

double std(double* a, int n);

double drand ( double low, double high );

double* timeOfKCalls(double (*f)(double*, double, double, double, double, int), 
						double* U, double a, double b, double c, double d, int N);

double* timeOfKCallsThread(double (*f)(double*, double, double, double, double, int, int, int), 
						double* U, double a, double b, double c, double d, int N, int nb_thread, int mode);						