/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fonctions pour l'exercice 2
 */
#include <pmmintrin.h>
#include <immintrin.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "exo3.h"
#include "exo2.h"
#include "exo1.h"
#include "utils.h"

pthread_mutex_t mutexsum;
double sum;

/*-------------------------------------------------------------*/
/* This is the thread version of the selected code portion     */
/*-------------------------------------------------------------*/
void *thread_function(void *threadarg) {
    /* Association between shared variables and their correspondances */
    double s;
    struct data_thread *thread_pointer_data = threadarg;
    /* Body of the thread */

    if (thread_pointer_data->mode == 0) {
        s = norm4(thread_pointer_data->U, thread_pointer_data->a, 
                thread_pointer_data->b, thread_pointer_data->c, 
                thread_pointer_data->d, thread_pointer_data->n);
    } else {
        s = vect_norm4(thread_pointer_data->U, thread_pointer_data->a, 
                thread_pointer_data->b, thread_pointer_data->c, 
                thread_pointer_data->d, thread_pointer_data->n);
    }

    pthread_mutex_lock(&mutexsum);
    sum += s;
    pthread_mutex_unlock(&mutexsum);


    pthread_exit(NULL);
}


/*-------------------------------------------------------------*/
double norm4Par(double *U, double a, double b, double c, double d, int n, int nb_threads, int mode) {
    struct data_thread *thread_data_array;
    unsigned int i, slice;
    pthread_t *thread_ptr;
    

    /* Create and launch threads */
    thread_data_array = malloc(nb_threads * sizeof(struct data_thread));
    thread_ptr = malloc(nb_threads * sizeof(pthread_t));

    sum = 0;

    slice = n / nb_threads;
    for(i = 0; i < nb_threads; i++) {
        /* Prepare data for this thread */
        thread_data_array[i].thread_id = i;
        thread_data_array[i].U = U + i * slice;
        thread_data_array[i].a = a;
        thread_data_array[i].b = b;
        thread_data_array[i].c = c;
        thread_data_array[i].d = d;
        thread_data_array[i].mode = mode;
        thread_data_array[i].n = slice;
        /* Create and launch this thread */
        pthread_create(&thread_ptr[i], NULL, thread_function, (void *) &thread_data_array[i]);
    }

    /* Wait for every thread to complete  */
    for(i = 0; i < nb_threads; i++) {
        pthread_join(thread_ptr[i], NULL);
    }
    
    return sum;
}
/* -------------------------------------------------------------------*/

void unit_check_vect_norm4_thread() {
    /* Declarations */
    int n, i, L;
	double a, b, c, d, res;
	double* U;

    /* Initialisations */
	a = 1.;	b = 2.;	c = 3.;	d = 4.;
	n = 64; 
    L = 32;

    /* Body */
	U = malloc(n * sizeof(double) + L);
	while (((long int)U % L) != 0) {
		U =(double*)((long int)U + 1);
	}

    for (i = 0; i < n; i++) {
	    U[i] = i;
    }
	
	res = norm4Par(U, a, b, c, d, n, 4, 1);

	/* Should be equal to */
	assert(abs(res -  471.336990) < 0.00001);
}