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

#include "exo3.h"
#include "exo2.h"
#include "exo1.h"

pthread_mutex_t mutexsum;
double sum=0;

/*-------------------------------------------------------------*/
/* This is the thread version of the selected code portion     */
/*-------------------------------------------------------------*/
void *thread_function(void *threadarg) {
    /* Local variables */
    double s, a, b, c, d;
    long start, stop, n;
    int thread_id;
    /* Shared variables correspondances */
    double *U;

    /* Association between shared variables and their correspondances */
    struct data_thread *thread_pointer_data;
    thread_pointer_data = (struct data_thread *)threadarg;
    /* Shared variables */
    U = thread_pointer_data->U;
    thread_id = thread_pointer_data->thread_id;
    a = thread_pointer_data->a;
    b = thread_pointer_data->b;
    c = thread_pointer_data->c;
    d = thread_pointer_data->d;
    start = thread_pointer_data->start;
    stop = thread_pointer_data->stop;


    /* Body of the thread */
    U += start;
    n = stop - start;


    s = norm4(U, a, b, c, d, n);
    printf("Thread_id %d (in the function), result is %f\n", thread_id, s);

    pthread_mutex_lock(&mutexsum);
    sum += s;
    pthread_mutex_unlock(&mutexsum);

    pthread_exit(NULL);
}


/*-------------------------------------------------------------*/
double norm4Par(double *U, double a, double b, double c, double d, int n, int nb_threads) {
    struct data_thread thread_data_array[nb_threads];
    unsigned int thread_i, i;
    pthread_t thread_ptr[nb_threads];


   /*-------------------------------------------------------------*/
   /* We prepare and call the thread version of this code portion */
   /*-------------------------------------------------------------*/
   /* Create and launch threads */

   for(i = 0; i < nb_threads; i++) {
        thread_i = i;
        /* Prepare data for this thread */
        thread_data_array[thread_i].thread_id = thread_i;
        thread_data_array[thread_i].U = U;
        thread_data_array[thread_i].a = a;
        thread_data_array[thread_i].b = b;
        thread_data_array[thread_i].c = c;
        thread_data_array[thread_i].d = d;
        thread_data_array[thread_i].start = i * (n / nb_threads);
        thread_data_array[thread_i].stop = (i+1) * (n / nb_threads);
        /* Create and launch this thread */
        printf("Lauching thread %d with start = %d and stop = %d\n", thread_i, thread_data_array[thread_i].start, thread_data_array[thread_i].stop);
        pthread_create(&thread_ptr[thread_i], NULL, thread_function, (void *) &thread_data_array[thread_i]);
   }

   /* Wait for every thread to complete  */
   for(i = 0; i < nb_threads; i++) {
        pthread_join(thread_ptr[thread_i], NULL);
   }

   return sum;
}
/* -------------------------------------------------------------------*/
