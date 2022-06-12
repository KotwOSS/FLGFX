#include<stdio.h>
#include<stdlib.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stdbool.h>
#include "gfx/shader.h"

// GLFW stuff
const size_t width = 500;
const size_t height = 500;
const char* title = "KEKW";
GLFWwindow* window;

// OpenGL stuff
GLuint vertexArrayID;
GLuint vertexBuffer;
GLuint programID;

// Our verticies
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f,
};

// Initialize OpenGL, GLFW and GLEW
void init() {
	printf("Initializing...\n");
	
	if(!glfwInit()) {
		printf("Failed to initialize GLFW!\n");
		exit(1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window == NULL) {
		printf("Failed to create window!\n");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if(glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW!\n");
		exit(1);
	}

	// Setup VAO
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	// Bind verticies to vertexBuffer
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(g_vertex_buffer_data), // size of data
		g_vertex_buffer_data,         // data
		GL_STATIC_DRAW
	);

	// Load shader
	programID = loadShader("shaders/sample.vsh", "shaders/sample.fsh");

	printf("Initialization successful!\n");
}

void loop() {
	printf("Running main loop...\n");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	do {
		// Clear the 'draw' buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnableVertexAttribArray(0); // enable attrib array

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,        // attribute 0, must match shader type
			3,        // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,        // stride
			(void*) 0 // offset
		);

		// Use shader
		glUseProgram(programID);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // vertex 0; 3 total -> 1 triangle
		
		glDisableVertexAttribArray(0); // disable attrib array

		// Swap the 'draw' buffer with the current display buffer
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		  glfwWindowShouldClose(window) == 0);						
}   							


void cleanup() {
	printf("Cleaning up...\n");
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main() {
	init();
	loop();
	cleanup();
}
					
