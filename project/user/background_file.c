#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	FILE *input_file = fopen("input.txt","rt");

	while(fgetc(input_file));
	
	while(1);


	return 0;
}