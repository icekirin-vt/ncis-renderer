#pragma once
#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "cglm/vec3.h"
#include "cglm/vec2.h"

// Source - https://stackoverflow.com/a
// Posted by chqrlie, modified by community. See post 'Timeline' for change history
// Retrieved 2026-01-02, License - CC BY-SA 4.0
char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p != NULL) {
        memcpy(p, s, size);
    }
    return p;
}

char *strndup(const char *s, size_t n) {
    char *p;
    size_t n1;

    for (n1 = 0; n1 < n && s[n1] != '\0'; n1++)
        continue;
    p = malloc(n + 1);
    if (p != NULL) {
        memcpy(p, s, n1);
        p[n1] = '\0';
    }
    return p;
}
// end of stackoverflow segment


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

size_t FWgetLineCount(char string[]){
		char* result=string;
		size_t count=0;
		while((result=strchr(result,'\n'))!=NULL){
				++count;
				++result;
		}
		return count;
}




int FWloadOBJ(char path[]){
		char *objSource=FWload(path);
		if(objSource==NULL){
				printf("INVALID OBJ FILE, FAILURE TO READ\n");
				return -1;
		}
	
		printf("load start\n\n");
		char* lineStart=objSource;
		char* lineEnd=strchr(objSource, '\n'); //gets pointer to EXACTLY newLine break
		size_t lineLenght;
		
		size_t lines=FWgetLineCount(objSource);
		printf("Total lines :%d\n",lines);
		

		while(true){
				lineLenght=lineEnd-lineStart;
				char* currentLine=strndup(lineStart,lineLenght);
				//printf("current line: |%s|\n",currentLine);

				char* tokenized=strtok(currentLine, " ");
				size_t counter=0;
				int isVector=0;
				while(tokenized){
						puts(&tokenized[0]);
						if((tokenized[0]=='v') && (isalpha(tokenized[0]))) {
								isVector=1;
						}
						if((tokenized[0]!='v') && (isalpha(tokenized[0]))) {
								isVector=0;
						}

						
						if(isVector==1) ++counter;
						printf(" is Vector: %d\n",isVector);
						tokenized=strtok(NULL," ");
				}

				lineStart=lineEnd+1;
				lineEnd=strchr(lineEnd+1,'\n');	
				if(lineEnd==NULL)
						break;
		}
		free((void*) objSource);
		return 0;

}
