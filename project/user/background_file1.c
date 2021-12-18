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

	fd = open("input.txt",O_RDWR);
	fstat(fd,&st);
	file = mmap(NULL,st.st_size, PROT_READ|PROT_WRITE,MAP_SHARED,fd,(off_t)0);
	if(file == MAP_FAILED) { perror("mmap"); exit(1); } 

	for(int i=0;i<st.st_size;i++){
		temp = file[i];
	}

	for(int i=0;i<st.st_size;i++){
		temp = file[i];
	}

	for(int i=0;i<st.st_size;i++){
		file[i]='p';
	}

	while(1);


	return 0;
}