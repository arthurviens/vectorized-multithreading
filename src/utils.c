#include "math.h"
#include <time.h>
#include <sys/time.h>
#include "utils.h"
#include "exo1.h"

/*! 
 * \fn double now()
 * \brief Renvoie le temps actuel de l'horloge
 * \return Current Time
 */
double now(){
   struct timeval t; double f_t;
   gettimeofday(&t, NULL); 
   f_t = t.tv_usec; f_t = f_t/1000000.0; f_t +=t.tv_sec;
   return f_t; 
}

void unit_checks(double *U) {
	assert(U);
	unit_check_norm4();
}

double mean(double* a, int n) {
	int i;
	double sum;
	sum = 0;
	for (i = 0; i < n; i++) {
		sum += a[i];
	}
	return (sum / n);	
}

double std(double* a, int n){
	int i;
	double var, local_mean;
	local_mean = mean(a, n);
	var = 0;
	for (i = 0; i < n; i++) {
		var += (a[i] - local_mean) * (a[i] - local_mean);
	}
	return sqrt(var / n);	
}

double* timeOf100Calls(double (*f)(double*, double, double, double, double, int), 
						double* U, double a, double b, double c, double d, int N) {
	
	double t0, t1, res, mean_times, mean_val, std_times, std_val;
	int i;
	double* mean_std = malloc(2 * sizeof(double));
	double* times = malloc(100 * sizeof(double));
	double* values = malloc(100 * sizeof(double));
	
	for (i = 0; i < 100; ++i) {
		t0 = now();
		res = f(U, a, b, c, d, N);
		t1 = now();
		times[i] = t1 - t0; 
		values[i] = res;
	}

	mean_times = mean(times, 100);
	mean_val = mean(values, 100);

	assert(mean_val = 1315061951.047256); /* check result */

	std_times = std(times, 100);
	std_val = std(values, 100);

	assert(std_val < 0.001); /* check result */

	mean_std[0] = mean_times;
	mean_std[1] = std_times;

	printf("Résultat : %f\n", mean_val);
	return mean_std;
}
