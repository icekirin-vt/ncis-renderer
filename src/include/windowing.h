#pragma once

#include "rendering.h"


void  glfw_windowSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0,0, width,height);
}


GLFWwindow* windowInit(int major_ver,int minor_ver, GLuint width, GLuint height, char tittle[]){
		GLFWwindow* window;
		if (!glfwInit())
				return NULL;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		
		window=glfwCreateWindow(width,height, tittle, NULL, NULL);

		if(!window){
				printf("failed to create window\n");
				glfwTerminate();
				return NULL; 
		}

		glfwMakeContextCurrent(window);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
				printf("Failed to init glad\n");
				return NULL;
		}
		
		glfwSetWindowSizeCallback(window,glfw_windowSizeCallback);
		return window;

}




