#include<GL/glew.h>
#include<stdio.h>
#include<stdlib.h>

#include "gfx/shader.h"

GLuint loadShader(const char* vertpath, const char* fragpath) {
	GLint result = GL_FALSE;
	int infoLogLength = 0;
	
	// Create shaders
	GLuint vertid = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragid = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader
	FILE* vertfile = fopen(vertpath, "r");

	if(vertfile == NULL) {
		printf("Vertex shader at %s not found!\n", vertpath);
		exit(1);
	}

	fseek(vertfile, 0L, SEEK_END);
	size_t vertfile_l = ftell(vertfile);
	fseek(vertfile, 0L, SEEK_SET);

	char* vert = malloc(sizeof(char) * (vertfile_l + 1));
	fread(vert, sizeof(char), vertfile_l, vertfile);
	
	// Terminate buffer
	vert[vertfile_l] = 0x0;
	
	fclose(vertfile);

	// Compile vertex shader
	printf("Compiling vertex shader '%s'\n", vertpath);

	glShaderSource(vertid, 1, (const char* const*) &vert, NULL);
	glCompileShader(vertid);

	// Free vertex source buffer
	free(vert);

	// Check vertex shader
	glGetShaderiv(vertid, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertid, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0) {
		char* infoLog = malloc(infoLogLength);

		glGetShaderInfoLog(vertid, infoLogLength, NULL, infoLog);

		printf("%s\n", infoLog);

		free(infoLog);
	}


	// Read fragment shader
	FILE* fragfile = fopen(fragpath, "r");
	
	if(fragfile == NULL) {
		printf("Fragment shader at %s not found!\n", fragpath);
		exit(1);
	}

	fseek(fragfile, 0L, SEEK_END);
	size_t fragfile_l = ftell(fragfile);
	fseek(fragfile, 0L, SEEK_SET);

	char* frag = malloc(sizeof(char) * (fragfile_l + 1));
	fread(frag, sizeof(char), fragfile_l, fragfile);

	// Terminate buffer
	frag[fragfile_l] = 0x0;

	fclose(fragfile);

	// Compile fragment shader
	printf("Compiling fragment shader '%s'\n", fragpath);
	
	glShaderSource(fragid, 1, (const char* const*) &frag, NULL);
	glCompileShader(fragid);

	// Free fragment source buffer
	free(frag);

	// Check fragment shader
	glGetShaderiv(fragid, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragid, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0) {
		char* infoLog = malloc(infoLogLength);

		glGetShaderInfoLog(fragid, infoLogLength, NULL, infoLog);

		printf("%s\n", infoLog);

		free(infoLog);
	}

	// Link program
	printf("Linking program\n");
	GLuint programid = glCreateProgram();
	glAttachShader(programid, vertid);
	glAttachShader(programid, fragid);
	glLinkProgram(programid);

	// Check program
	glGetProgramiv(programid, GL_LINK_STATUS, &result);
	glGetProgramiv(programid, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0) {
		char* infoLog = malloc(infoLogLength);

		glGetShaderInfoLog(fragid, infoLogLength, NULL, infoLog);

		printf("%s\n", infoLog);

		free(infoLog);
	}

	// Cleanup
	glDetachShader(programid, vertid);
	glDetachShader(programid, fragid);

	glDeleteShader(vertid);
	glDeleteShader(fragid);

	return programid;
}

