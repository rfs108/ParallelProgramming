#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int NUM_HASHES = 47988;

	char * hash_array[NUM_HASHES];
	FILE *file = fopen("hash.txt", "r");


	for(int i = 0; i < NUM_HASHES; i++){
		// Allocate space for length of each hash
		hash_array[i] = malloc(128);
		fscanf(file,"%s", hash_array[i]);
	}
	
	for(int i = 0; i < NUM_HASHES; i++){
		printf("%s\n", hash_array[i]);
	}

	for(int i = 0; i < NUM_HASHES; i++){
		free(hash_array[i]);
	}

	return 0;
}