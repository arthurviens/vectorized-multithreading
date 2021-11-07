/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fichier main
 */
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "utils.h"

int N = 1024 * 1024;


/*! 
 * \fn int main(int argc, char** argv)
 * \brief Exécute le programme
 * \param argc : nombre d'arguments
 * \param char** argv : tableau des arguments
 * \return 0
 */
int main(int argc, char** argv) {
	/* Declarations */
	unsigned int L, i, nb_threads;
	double a, b, c, d, t_seq, t_vect;
	double* U, *mean_std;

	/* Initialisations */
	a = 2.;
	b = 3.;
	c = 4.;
	d = 5.;
	L = 32;
	U = malloc(N * sizeof(double) + L);
	while (((long int)U % L) != 0) {
		U =(double*)((long int)U + 1);
	}

	for(i = 0; i < N; i++) {
		U[i] = 1.;
	}

	/* Body */
	unit_checks(U);

	printf("######################### Scalaire #########################\n");
	mean_std = timeOfKCalls(norm4, U, a, b, c, d, N);
	printf("# Resultat correct. Temps d'exécution de norm4 (scalaire) pour N = %i \n", N);
	printf("# --> Temps moyen pour 1000 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	t_seq = mean_std[0];
	
	printf("############################################################\n");
	printf("######################### Vectoriel ########################\n");
	mean_std = timeOfKCalls(vect_norm4, U, a, b, c, d, N);
	printf("# Resultat correct. Temps d'exécution de vect_norm4 (vectoriel) pour N = %i \n", N);
	printf("# --> Temps moyen pour 1000 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	t_vect = mean_std[0];
	printf("#\n");

	printf("# L'accélération séquentielle Scalaire -> Vectorielle %f\n", t_seq / t_vect);
	printf("############################################################\n");
	printf("\n");
	printf("############################################################\n");
	printf("######################### Multi-Thread #####################\n");

	nb_threads = 8;
	printf("# MODE 0 : Multi-Thread scalaire \n");
	mean_std = timeOfKCallsThread(norm4Par, U, a, b, c, d, N, nb_threads, 0);
	printf("# Resultat correct. Temps d'exécution de norm4Par (scalaire) pour N = %i \n", N);
	printf("# --> Temps moyen pour 1000 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	printf("#\n");
	printf("# Accélération scalaire -> multi-thread scalaire %f\n", t_seq / mean_std[0]);
	printf("############################################################\n");

	printf("# MODE 1 : Multi-Thread vectoriel \n");
	mean_std = timeOfKCallsThread(norm4Par, U, a, b, c, d, N, nb_threads, 1);
	printf("# Resultat correct. Temps d'exécution de norm4Par (vectoriel) pour N = %i \n", N);
	printf("# --> Temps moyen pour 1000 executions = %fms et ecart type = %fms \n", mean_std[0] * 1000, mean_std[1] * 1000);
	printf("#\n");
	printf("# Accélération vectorielle et multi-thread vectorielle %f\n", t_vect / mean_std[0]);
	printf("############################################################\n");

	printf("\n");
	printf("-----> Accélération pour N = %d entre version \n", N);
	printf("-----> Séquentielle scalaire et Multi_Thread Vectorielle (Accélération max) : %f\n", t_seq / mean_std[0]);


	
	return 0;
}