#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

//returns first character pointer, allocated in memory for its lenght
char *load_shadersource(char path[]){
		FILE *fptr=fopen(path, "rb");
		if(!fptr) {
				printf("error loading shader at %s\n",path);
				return NULL;
		}
		
		//this here gets position of EOF, for size reference for reading further
		fseek(fptr, 0L, SEEK_END);
		size_t size=ftell(fptr);
		rewind(fptr);


		if(size<10)  return NULL; //10 is safe size for too little of file to be valid shader, and yet not 0 in case of stray whitespaces etc
								  //
		char *stringStorage=	malloc(	(size+1)	*	sizeof(char)	); //allocate size+1 for nullterm
		size_t bytesRead = 		fread(	stringStorage, 1, size, fptr	); //read full file and store size for check, close file right after;
		fclose(fptr);
		printf("%d\n",bytesRead);
		if(bytesRead !=size){
				printf("failure to read entire file\n");
				free(stringStorage);
				return NULL;
		} //sanity check

		stringStorage[size]= '\0'; //adding null termination 
					
		return stringStorage;
}
