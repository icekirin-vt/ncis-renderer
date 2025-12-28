#include <stdio.h>
#include "glad.h"
#include "GLFW/glfw3.h"


int main(){
  printf("welcome to my world\n");
  printf("Initializing the NCIS engine\n");


  
  GLFWwindow* window;
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, );
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window=glfwCreateWindow(700,400, "NCIS Core v0.0.1", NULL, NULL);
  
  if(window== NULL){
    printf("failed to create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    printf("Failed to init glad\n");
    return -1;
  }
  

  glClearColor(1.0f, 0.569f, 0.204f, 1.0f);


  while( !glfwWindowShouldClose(window)){
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;


}

