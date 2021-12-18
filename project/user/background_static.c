#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <immintrin.h>
#include <string.h>

#define NUM 200000


int arr20[NUM];
int arr19[NUM];
int arr18[NUM];
int arr17[NUM];
int arr16[NUM];
int arr15[NUM];
int arr14[NUM];
int arr13[NUM];
int arr12[NUM];
int arr11[NUM];

int main(void) {
	long long start, end;

	start = __rdtsc();

	int arr20[NUM];
	int arr19[NUM];
	int arr18[NUM];
	int arr17[NUM];
	int arr16[NUM];
	int arr15[NUM];
	int arr14[NUM];
	int arr13[NUM];
	int arr12[NUM];
	int arr11[NUM];


	for(int i=0;i<NUM;i++){
		arr20[i]=i;
		arr19[i]=i;
		arr18[i]=i;
		arr17[i]=i;
		arr16[i]=i;
		arr15[i]=i;
		arr14[i]=i;
		arr13[i]=i;
		arr12[i]=i;
		arr11[i]=i;

	}

	end = __rdtsc();

	printf("alloc time : %ld\n",end-start);

	while(1);



	return 0;
}