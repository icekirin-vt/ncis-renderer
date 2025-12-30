#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <extratypes.h>
//returns first character pointer, allocated in memory for its lenght
void *FWload(char path[]){
		FILE *fptr=fopen(path, "rb");
		if(!fptr) {
				printf("error loading file at %s\n",path);
				return NULL;
		}
		
		//this here gets position of EOF, for size reference for reading further
		fseek(fptr, 0L, SEEK_END);
		size_t size=ftell(fptr);
		rewind(fptr);


		if(size<1)  return NULL; //1 is safe size for too little of file to be valid shader, and yet not 0 in case of stray whitespaces etc
								  //
		char *stringStorage=	malloc(	(size+1)	*	sizeof(char)	); //allocate size+1 for nullterm
		size_t bytesRead = 		fread(	stringStorage, 1, size, fptr	); //read full file and store size for check, close file right after;
		fclose(fptr);
		if(bytesRead !=size){
				printf("failure to read entire file\n");
				free(stringStorage);
				return NULL;
		} //sanity check

		stringStorage[size]= '\0'; //adding null termination 
					
		return stringStorage;
}


GLuint FWconstructShader(GLenum shaderType, char shaderSource[]){
		GLuint shader= glCreateShader(shaderType);
		glShaderSource(shader,1,(const char* const*) shaderSource, NULL);
		glCompileShader(shader);

		int success;
		char infolog[1024];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if( !success ){
				glGetShaderInfoLog(shader, 1024, NULL, infolog);
				printf(" ERROR COMPILING SHADER: \n%s\n",infolog);
		}

}

GLuint FWconstructProgram(GLuint shaders[], size_t shadersCount){
		GLuint shaderProgram= glCreateProgram();

		for(int i=0;i<shadersCount;i++){
				GLuint curShader=shaders[i];
				glAttachShader(shaderProgram,curShader);
		}
		return shaderProgram;
}


void FWdeleteShaders(GLuint shaders[], size_t shadersCount){
		for(int i=0;i<shadersCount;i++){
				glDeleteShader(shaders[i]);	
		}
}

GLuint FWlinkShaderProgram(GLuint shaderProgram){
		int success;
		char infolog[1024];

		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if( !success ){
				glGetProgramInfoLog(shaderProgram, 1024, NULL, infolog);
				printf(" ERROR LINKING PROGRAM: \n%s\n",infolog);
				return 0;
		}
		return shaderProgram;
		
}

void FWloadOBJ(char path[]){
		char *objSource=FWload(path);
			

		

		free((void*) objSource);

}
