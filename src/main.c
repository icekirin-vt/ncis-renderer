#include <stdio.h>
#include "glad.h"
#include "GLFW/glfw3.h"
#include "windowing.h"
#include "fileworks.h"

int main(){
		printf("welcome to my world\n");
		printf("Initializing the NCIS engine\n");
		
		GLFWwindow* window=windowInit(4,5, 400,200, "Hello cgl!");
		if(!window) return -1;
		

		char *fragSource=FWLoad("shaders/basic.vert");
		
		printf(" shader source : \n%s\n",fragSource);
		renderLoop(window);
		return 0;
}

