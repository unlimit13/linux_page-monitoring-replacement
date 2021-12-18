#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <x86intrin.h>
#include <immintrin.h>
#include "backheader.h"

#define ANON_1 7200


int main(void) {
	long long start, end;


	int n = ANON_1;

	start = __rdtsc();
	int** arr_1 = (int**)malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
		arr_1[i] = (int*)malloc(sizeof(int)*n);
	}
	for(int j=0;j<n;j++){
		for(int k=0; k<n;k++){
			arr_1[j][k]=k;
		}
	}
	end = __rdtsc();
	printf("alloc time : %ld\n",end-start);

	int k=0;
	int times==5;
	while(times--){
		if(k==0){
			k=1;
			for(int i=0;i<ANON_1;i++){
				arr_1[i]++;
			}
		}
		else{
			k=0;
			for(int i=0;i<ANON_1;i++){
				arr_1[i]--;
			}
		}
	}


	return 0;
}