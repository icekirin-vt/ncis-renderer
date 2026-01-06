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
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		


		renderInit(window);
		
		char* simpleVert=FWload("shaders/basic.vert");
		char* unshadeFrag=FWload("shaders/unshade.frag");
		GLuint vertShad=FWconstructShader(GL_VERTEX_SHADER, simpleVert);
		GLuint fragShad=FWconstructShader(GL_FRAGMENT_SHADER, unshadeFrag);
		
		GLuint shadersStack[]={vertShad,fragShad};
		GLuint shaderProg=FWconstructProgram(shadersStack,2);	
		GLuint linkedProg=FWlinkShaderProgram(shaderProg);	
		free(unshadeFrag);
		free(simpleVert);

		float vertices[]= {
				 0.5f,  0.5f, 0.0f,  // top right
				 0.5f, -0.5f, 0.0f,  // bottom right
				-0.5f, -0.5f, 0.0f,  // bottom left
				-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[]= {
				0, 1, 3,
				1, 2, 3
		};

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0); 


		renderLoop(window, shaderProg);
		
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProg);
		glfwTerminate();
		return 0;
}

