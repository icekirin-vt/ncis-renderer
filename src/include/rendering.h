#pragma once
#include "cglm/cglm.h"




int renderInit(GLFWwindow* window){
		
}
int renderLoop(GLFWwindow* window, GLuint shaderProgram){
		const GLubyte *version= glGetString(GL_VERSION);
		printf ("Supported GL version is: %s\n", version);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		while( !glfwWindowShouldClose(window)){

				glClear(GL_COLOR_BUFFER_BIT);
				
				glUseProgram(shaderProgram);
				glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


				glfwSwapBuffers(window);
				glfwPollEvents();


		}
		return 0;
}


