#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct data_thread{
    int thread_id;
    double *U;
    double a;
    double b;
    double c;
    double d;
    int n;
    int mode;
};

void *thread_function(void *threadarg);
double norm4Par(double *U, double a, double b, double c, double d, int n, int nb_threads, int mode);
void unit_check_vect_norm4_thread();