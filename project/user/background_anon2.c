#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <x86intrin.h>
#include <immintrin.h>

#define ANON_2 7300

int main(void) {
	long long start, end;


	int n = ANON_2;

	start = __rdtsc();
	int** arr_2 = (int**)malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
		arr_2[i] = (int*)malloc(sizeof(int)*n);
	}
	for(int j=0;j<n;j++){
		for(int k=0; k<n;k++){
			arr_2[j][k]=k;
		}
	}
	end = __rdtsc();
	printf("alloc time : %ld\n",end-start);

	while(1);


	return 0;
}