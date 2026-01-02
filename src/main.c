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
		

			

		renderInit(window);
		FWloadOBJ("assets/tiltTrig.obj");
		renderLoop(window);

		return 0;
}

