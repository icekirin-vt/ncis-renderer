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
		GLuint shader= 	glCreateShader( shaderType );
		glShaderSource(	shader,	1,(const char* const*) shaderSource, NULL);
		glCompileShader(shader);

		int success;
		char infolog[1024];
		glGetShaderiv(	shader, GL_COMPILE_STATUS, &success);
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



size_t getMentionCount(char* string, char* subj){	
		size_t subjCounter=0;
		char* result=string;
		while((result=strstr(result,subj))!=NULL){
				result=result+strlen(subj);
				subjCounter++;
		}
		return subjCounter;
		
}



int FWloadOBJ(char path[]){
		char *ObjSource=FWload(path);
		if(ObjSource==NULL){
				printf("INVALID OBJ FILE, FAILURE TO READ\n");
				return -1;
		}
	
		char* 	LineStart=		ObjSource;
		char* 	LineEnd=		strchr(ObjSource, '\n'); //gets pointer to EXACTLY newLine break
		size_t 	LineLenght;
		
		size_t Lines=		FWgetLineCount(ObjSource);
		
		size_t VertCount=	getMentionCount(ObjSource,"v ");
		size_t NormCount=	getMentionCount(ObjSource,"vn ");
		size_t UVCount=		getMentionCount(ObjSource,"vt ");
		size_t FaceCount=	getMentionCount(ObjSource,"f ");
		
		vec3 Vertecies[VertCount];
		vec3 Normals[NormCount];
		vec2 UVCoords[UVCount];
		char Faces[FaceCount];

		size_t VertInd	=0;
		size_t NormInd	=0;
		size_t UVInd	=0;
		size_t FaceInd	=0;
		
		while(true){
				LineLenght=LineEnd-LineStart;
				size_t counter=-2;
				char* currentLine=strndup(LineStart,LineLenght);
				char* tokenized=strtok(currentLine, " ");
				int isVert3	=0;
				int isNorm3	=0;
				int isVec2	=0;
				int isString=0;

				vec3 tmpVec3;
				vec2 tmpVec2;
				char* tmpFace="";

				glm_vec2_zero(tmpVec2);
				glm_vec3_zero(tmpVec3);

				while(tokenized){
						counter++;
						if(strcmp(tokenized,"v")==0) {
								isVert3=1;
						};
						if(strcmp(tokenized,"vn")==0){
								isNorm3=1;
						}
						if( (strcmp(tokenized,"vt")==0)) {
								isVec2=1;
						};	
						if( (strcmp(tokenized,"f ")==0)){
								isString=1;								
						}
						
						if ((isVert3==1 || isNorm3==1) && counter>=0 && counter<3){
								tmpVec3[counter]=strtof(tokenized, NULL);
						}
						if (isVec2==1 && counter>=0 && counter<2){
								tmpVec2[counter]=strtof(tokenized, NULL);
						}
						if (isString==1 && counter>=0 && counter<4){
								tmpVec2[counter]=strtof(tokenized, NULL);
						}


						
						if( isVec2==1 && counter==1){
								
								UVCoords[UVInd++]		=tmpVec2;
						}
						if( isVert3==1 && counter==2){
								Vertecies[VertInd++]	=tmpVec3;
						}
						if( isNorm3==1 && counter==2){
								Normals[NormInd++]		=tmpVec3;
						}
						if( isString==1 && counter==2){
								//Faces[FaceInd++]=   //TODO: Face saving
						}

						tokenized=strtok(NULL," ");
				}

				LineStart=LineEnd+1;
				LineEnd=strchr(LineEnd+1,'\n');	
				isVert3	=0;
				isVec2	=0;
				isString=0;
				if(LineEnd==NULL)
						break;
		}
		free((void*) ObjSource);
		return 0;

}
