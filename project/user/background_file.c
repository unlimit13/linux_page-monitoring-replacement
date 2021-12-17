#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 11000000
int main(void) {
	int n=NUM;
	int a=NUM;
	char arr[50];
	FILE *output_file = fopen("output.txt","w+");
	FILE *input_file = fopen("input.txt","r");
	/*while(n--){
		fputs("This is temp string to alloc file-backed page.\n",output_file);
	};*/
	while(a--){
		fgets(arr,50,input_file);
	}
	//fclose(output_file);
	while(1);


	return 0;
}