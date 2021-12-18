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

int main(void) {
	long long start, end;

	char *file1;
	struct stat st;
	int fd;
	char temp;

	start = __rdtsc();
	fd = open("input.txt",O_RDWR);
	fstat(fd,&st);
	file1 = mmap(NULL,st.st_size, PROT_READ|PROT_WRITE,MAP_SHARED,fd,(off_t)0);
	if(file1 == MAP_FAILED) { perror("mmap"); exit(1); } 

	for(int i=0;i<st.st_size;i++){
		temp = file1[i];
	}
	end = __rdtsc();

	printf("alloc time : %ld\n",end-start);

	while(1);


	return 0;
}