#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void *FWload(char path[]){
		FILE *fptr=fopen(path, "rb");
		if(!fptr) {
				printf("error loading file at %s\n",path);
				return NULL;
		}
		fseek(fptr, 0L, SEEK_END);
		size_t size=ftell(fptr);
		rewind(fptr);
		if(size<1)  return NULL; 
								 
		char *stringStorage	=malloc((size+1)*sizeof(char));
		size_t bytesRead 	=fread(stringStorage,1,size,fptr);
		fclose(fptr);
		if(	bytesRead!=size	){
				printf("failure to read entire file\n");
				free(stringStorage);
				return NULL;
		}
		stringStorage[size]= '\0';
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
