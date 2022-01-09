#include "../include/shader.h"

GLuint shader_load(const char *path, GLenum type)
{
	FILE *sf = fopen(path, "r");
	size_t size = 1024;
	GLchar *shader_src = malloc(size);
	GLuint shader = glCreateShader(type);

	if (!sf) {
		printf("Could not open file: %s\n", path);
		return 0;
	}

	int i, c;
	for (i = 0; (c = fgetc(sf)) != EOF; ++i) {
		*(shader_src+i) = c;
		if (i >= size) {
			size <<= 1;
			char *tmp = realloc(shader_src, size);
			if (tmp != 0) {
				memcpy(tmp, shader_src, size);
			} else {
				printf("Could not reallocate memory for shader buffer\n");
				return 0;
			}
		}
	}
	*(shader_src+i) = '\0';

	glShaderSource(shader, 1, (const GLchar **)&shader_src, NULL);
	glCompileShader(shader);

	GLint shader_success = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_success);
	if (shader_success != GL_TRUE) {
		printf("Unable to compile shader %d\nSource: %s\n", shader, shader_src);
		shader_slog(shader);
		glDeleteShader(shader);
		shader = 0;
	}
	fclose(sf);
	return shader;
}

void shader_slog(GLuint shader)
{
	if (glIsShader(shader)) {
		int log_length = 0;
		int max_length = log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
		char *log = malloc(max_length);
		glGetShaderInfoLog(shader, max_length, &log_length, log);
		if (log_length > 0) {
			printf("%s\n", log);
		}
		free(log);
	} else {
		printf("Name %d is not a shader\n", shader);
	}
}

void shader_plog(GLuint program)
{
	if (glIsProgram(program)) {
		int log_length = 0;
		int max_length = log_length;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
		char *log = malloc(max_length);
		glGetProgramInfoLog(program, max_length, &log_length, log);
		if (log_length > 0) {
			printf("%s\n", log);
		}
		free(log);
	} else {
		printf("Name %d is not a program\n", program);
	}
}

