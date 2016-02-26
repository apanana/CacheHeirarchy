// Benchmarking the Memory Heirarchy
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////
// Generates a random 64bit int on the range [0,bound)
// Credit Ryan Reich's code on StackExchange for this version of rand
uint64_t random_at_most(uint64_t max) {
	uint64_t
	num_bins = (uint64_t) max + 1,
	num_rand = (uint64_t) RAND_MAX + 1,
	bin_size = num_rand / num_bins,
	defect   = num_rand % num_bins;

	uint64_t x;
	do {
	x = random();
	}
	while (num_rand - defect <= (uint64_t)x);

	return x/bin_size;
}

// Generates an array of 'size' 64bit ints on the range [0,bound]
uint64_t * generate_random_list(uint64_t size){
	uint64_t *out = (uint64_t *)malloc(sizeof(uint64_t)*size);
	for(int i=0; i<size; i++){
		out[i]=random_at_most(size);
	}
	return out;
}


///////////////////////////////// Main: /////////////////////////////////
int main(int argc, char *argv[]){
	//// Get arguments: size and iters
	if( argc != 3) {
		printf("Required argument: buffer_size(N) and iterations(M).");
		return 0;
	}
	const uint64_t size = atoi( argv[1] );
	const int iters = atoi( argv[2] );

	//// Set random seed using time
	srandom(time(NULL));

	//// Generate a list
	uint64_t *x = generate_random_list(size);

	//// Initialize an index for checking next val in for loop and
	//// an index for iterating through the for loop.
	uint64_t index= random_at_most(size), j=0;

	//// Timing the accesses
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	for(;j<iters;++j){
		index = x[index];
		}
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	//// I literally spent hours trying to figure out why I was getting 0s as my outputs.
	//// As Ben very kindly explained, the optimizer gets rid of my while loop bc it 
	//// wants to make the code as fast as possible. We need this if-statement so that
	//// the optimizer can't just get rid of the for-loop
	if(index == 0) printf("I need this so the optimizer doesn't kill my for-loop");

	/// Calculating the average time per each access
	double total = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	double avg = total/iters;
	// printf("Avg time for all iteration: \t %f \tns\n", avg);

	// I'm actually going to print it as the first column being the size and the second 
	// column being the avg runtime in ns so that it is faster to plot and I don't need
	// to clean up the data.
	printf("%llu \t %f \n",(long long unsigned)size,avg);

	free(x);
	x = NULL;
	return 0;
	}