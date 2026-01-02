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
				size_t counter=-2;
				int isVec3=0;
				int isVec2=0;
				vec3 tmpVec3;
				vec2 tmpVec2;
				glm_vec2_zero(tmpVec2);
				glm_vec3_zero(tmpVec3);
				while(tokenized){
						counter++;
						if( (strcmp(tokenized,"v")==0) ||  (strcmp(tokenized,"vn")==0) ) {
								isVec3=1;
						};	
					
						if( (strcmp(tokenized,"vt")==0)) {
								isVec2=1;
						};	



						
						printf("v:%d  c:%d |%s",isVec3,counter,&tokenized[0]);
						if (isVec3==1 && counter>=0 && counter<3){
								tmpVec3[counter]=strtof(tokenized, NULL);
								//printf(" vector member %d ",counter);
						}
						if (isVec2==1 && counter>=0 && counter<2){
								tmpVec2[counter]=strtof(tokenized, NULL);
								//printf(" vector member %d ",counter);
						}

						if(counter==2 && isVec3==1)
								printf("   vec3:%f,%f,%f \n",tmpVec3[0],tmpVec3[1],tmpVec3[2]);
						else{
								if(counter==1 && isVec2==1)
										printf("   vec2:%f,%f    \n",tmpVec2[0],tmpVec2[1]);
								else printf(" \n");
						}
												

						tokenized=strtok(NULL," ");
				}

				lineStart=lineEnd+1;
				lineEnd=strchr(lineEnd+1,'\n');	
				isVec3=0;
				isVec2=0;
				if(lineEnd==NULL)
						break;
		}
		free((void*) objSource);
		return 0;

}
