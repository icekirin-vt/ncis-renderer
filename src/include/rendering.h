#pragma once


int renderInit(GLFWwindow* window){
		
}
int renderLoop(GLFWwindow* window){
		const GLubyte *version= glGetString(GL_VERSION);
		printf ("Supported GL version is: %s\n", version);

		glClearColor(1.0f, 0.569f, 0.204f, 1.0f);
		while( !glfwWindowShouldClose(window)){

				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(window);
				glfwPollEvents();


		}
		glfwTerminate();
		return 0;
}


