#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

void usage () {
	printf("\nUsage: stats samples population lowerbound upperbound\n       samples: number of samples\n       population: number of random variables to generate in each sample\n       lowerbound: bottom of random number range\n       upperbound: top of random number range\n");

	exit(EXIT_FAILURE);
}

int *generate_population(int size, int lower, int upper){
	int *array = (int *)malloc(size * sizeof(int));

	if (array == NULL){
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		array[i] = rand() % (upper-lower + 1) + lower;
	}
	return array;
}
void get_stats(int *a, int size, int *min, int *max, double *mean, double *stddev){
	*min = *max = a[0];
	double summy = 0;

	for (int i = 1; i < size; i++){
		if (a[i] < *min) {
			*min = a[i];
		}
		if (a[i] > *max) {
			*max = a[i];
		}
		summy += a[i]; 
	}
	*mean = summy / size;

	double sqer = 0;
	for (int i = 0; i< size; i++){
		sqer += pow(a[i] - *mean, 2);
	}
	*stddev = sqrt(sqer/size);
}

int is_valid_int(char *s)
{
    if (s == NULL || *s == '\0'){


        return -1;
    }

    if (*s == '-')
    {
        ++s;
    }
    while (*s != '\0')
    {
        if (!isdigit(*s))
        {
            return 0;
        }
        ++s;
    }
    return 1;
}


int main(int argc, char *argv[])
{
	if (argc !=5) {
		printf("incorrect number of arguments\n");
		usage();
}
	int num_samples = atoi(argv[1]);
	int population_size = atoi(argv[2]);
	int lower_bound = atoi(argv[3]);
	int upper_bound = atoi(argv[4]);

	if (num_samples <= 0) {
		printf("samples must be a positive integer\n");
		usage();
	}

	if (population_size <= 0){
		printf("population must be a positive integer\n");
		usage();
	}
	
	if (!is_valid_int(argv[3]) || !is_valid_int(argv[4])){
		printf("all arguments must be integers\n");
		usage();
	}

	if (lower_bound > upper_bound) {
		printf("upperbound must be >= lowerbound\n");
		usage();
	}
	
	for (int sample = 0; sample < num_samples; sample++) {
		int *population = generate_population(population_size, lower_bound, upper_bound);
		int min, max;
		double mean, stddev;
		get_stats(population, population_size, &min, &max, &mean, &stddev);
		printf("Sample %d: ", sample + 1);
		printf("min=%d, ", min);
		printf("max=%d, ", max);
		printf("mean=%g, ", mean);
		printf("stddev=%g\n", stddev);

		free(population);
	}
 
		
    return 0;
}


