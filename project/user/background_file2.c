#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>
#define NUM 11000000

int main(void) {
	int start, end;


	int n=NUM;
	int a=NUM;
	char* arr;

	char *file;
	struct stat st;
	int fd;
	char temp;
	FILE* fd1;
	//FILE *output_file = fopen("output.txt","w+");
	//FILE *input_file = fopen("input.txt","r");

	fd = open("input2.txt",O_RDWR);
	//fd = fopen("input.txt","r");
	fstat(fd,&st);
	file = mmap(NULL,st.st_size, PROT_READ|PROT_WRITE,MAP_SHARED,fd,(off_t)0);
	if(file == MAP_FAILED) { perror("mmap"); exit(1); } 



	/*while(n--){
		fputs("This is temp string to alloc file-backed page.\n",output_file);
	};*/
	/*while(a--){
		fgets(arr,50,input_file);
	}*/
	//fclose(output_file);
	while(1);


	return 0;
}