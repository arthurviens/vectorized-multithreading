/*!
 * \file exo1.c
 * \author VIENS Arthur
 * \date 31/10/2021
 * \version 0.1
 * \brief Fichier main
 */
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "utils.h"

int N = 1024 * 1024;
int K = 1000;

/*! 
 * \fn int main(int argc, char** argv)
 * \brief Exécute le programme
 * \param argc : nombre d'arguments
 * \param char** argv : tableau des arguments
 * \return 0
 */
int main(int argc, char** argv) {
	/* Declarations */
	unsigned int L, i;
	long nb_logical_processor;
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
		U[i] = drand(0, 15); /* Initialisation aléatoire du vecteur */
	}


	/* Body */
	unit_checks(U);
	
	printf("######################### Scalaire #########################\n");
	mean_std = timeOfKCalls(norm4, U, a, b, c, d, N);
	printf("# Temps d'exécution de norm4 (scalaire) pour N = %i \n", N);
	printf("# --> Temps moyen pour %d executions = %fms et écart type = %fms \n", K, mean_std[0] * 1000, mean_std[1] * 1000);
	t_seq = mean_std[0];
	
	printf("############################################################\n");
	printf("######################### Vectoriel ########################\n");
	mean_std = timeOfKCalls(vect_norm4, U, a, b, c, d, N);
	printf("# Temps d'exécution de vect_norm4 (vectoriel) pour N = %i \n", N);
	printf("# --> Temps moyen pour %d executions = %fms et écart type = %fms \n", K, mean_std[0] * 1000, mean_std[1] * 1000);
	t_vect = mean_std[0]; 
	printf("#\n");

	printf("# L'accélération séquentielle Scalaire -> Vectorielle %f\n", t_seq / t_vect);
	printf("############################################################\n");
	printf("\n");
	printf("############################################################\n");
	printf("######################### Multi-Thread #####################\n");


	nb_logical_processor = sysconf(_SC_NPROCESSORS_CONF);
	printf("# MODE 0 : Multi-Thread scalaire. Nombre de threads : %ld \n", nb_logical_processor);
	mean_std = timeOfKCallsThread(norm4Par, U, a, b, c, d, N, nb_logical_processor, 0);
	printf("# Temps d'exécution de norm4Par (scalaire) pour N = %i \n", N);
	printf("# --> Temps moyen pour %d executions = %fms et écart type = %fms \n", K, mean_std[0] * 1000, mean_std[1] * 1000);
	printf("#\n");
	printf("# Accélération scalaire -> multi-thread scalaire %f\n", t_seq / mean_std[0]);
	printf("############################################################\n");
	
	printf("# MODE 1 : Multi-Thread vectoriel. Nombre de threads : %ld \n", nb_logical_processor);
	mean_std = timeOfKCallsThread(norm4Par, U, a, b, c, d, N, nb_logical_processor, 1);
	printf("# Temps d'exécution de norm4Par (vectoriel) pour N = %i \n", N);
	printf("# --> Temps moyen pour %d executions = %fms et écart type = %fms \n", K, mean_std[0] * 1000, mean_std[1] * 1000);
	printf("#\n");
	printf("# Accélération vectorielle et multi-thread vectorielle %f\n", t_vect / mean_std[0]);
	printf("############################################################\n");

	printf("\n");
	printf("-----> Accélération pour N = %d entre version \n", N);
	printf("-----> Séquentielle scalaire et Multi_Thread Vectorielle (Accélération max) : %f\n", t_seq / mean_std[0]);
	printf("Bien que s'agissant d'une division entre deux moyennes sur %d exécutions, l'accélération varie relativement beaucoup.\n", K);
	

	
	return 0;
}