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

double *rs;

/*-------------------------------------------------------------*/
/* This is the thread version of the selected code portion     */
/*-------------------------------------------------------------*/
void *thread_function(void *threadarg) {
    /* Association between shared variables and their correspondances */
    struct data_thread *thread_pointer_data = threadarg;
    /* Body of the thread */

    if (thread_pointer_data->mode == 0) {
        rs[thread_pointer_data->thread_id] = norm4(thread_pointer_data->U, thread_pointer_data->a, 
                thread_pointer_data->b, thread_pointer_data->c, 
                thread_pointer_data->d, thread_pointer_data->n);
    } else {
        rs[thread_pointer_data->thread_id] = vect_norm4(thread_pointer_data->U, thread_pointer_data->a, 
                thread_pointer_data->b, thread_pointer_data->c, 
                thread_pointer_data->d, thread_pointer_data->n);
    }

    pthread_exit(NULL);
}


/*-------------------------------------------------------------*/
double norm4Par(double *U, double a, double b, double c, double d, int n, int nb_threads, int mode) {
    struct data_thread *thread_data_array;
    unsigned int i, slice;
    pthread_t *thread_ptr;
    double sum;

    /* Create and launch threads */
    thread_data_array = malloc(nb_threads * sizeof(struct data_thread));
    thread_ptr = malloc(nb_threads * sizeof(pthread_t));
    rs = malloc(nb_threads * sizeof(double));

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

    sum = 0;
    for (i = 0; i < nb_threads; i++) {
        sum += rs[i];
    }
    
    return sum;
}
/* -------------------------------------------------------------------*/
