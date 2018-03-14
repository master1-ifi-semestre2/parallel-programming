#include <omp.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	#pragma omp parallel
	printf("Test\n");
	printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
	return 0;
}