#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int n = 11000;

	int** arr_d = (int**)malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
		arr_d[i] = (int*)malloc(sizeof(int)*n);
	}
	for(int j=0;j<n;j++){
		for(int k=0; k<n;k++){
			arr_d[j][k]=k;
		}
	}
	//int arr_s[1024][1024]={{1,},};

	while(1);


	return 0;
}