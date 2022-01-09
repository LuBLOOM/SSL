#include <stdio.h>

#include "../include/ui.h"
#include "../include/shader.h"

static GLuint shader_pid;
static GLfloat *shader_vertices;
static GLuint vertex_buffer;
static GLuint *shader_indices;
static GLuint index_buffer;

static void shader_setup(const char *, const char *);
static void shader_render(void);
static void shader_free(void);

int main(int argc, char **argv)
{
	ui_init(UI_WINDOW_NAME, UI_WINDOW_WIDTH, UI_WINDOW_HEIGHT, UI_WINDOW_FLAGS);

	shader_setup("./shaders/shader.glvs", "./shaders/shader.glfs");

	SDL_Event event;
	while (ui_active) {
		while (SDL_PollEvent(&event)) {
			ui_events(event);
		}
		ui_render_start();
		shader_render();
		ui_render_end();
	}

	shader_free();
	ui_free();
	return printf("SSL - Closed\n");
}


static void shader_setup(const char *vertex_path, const char *fragment_path)
{
 	shader_vertices = (GLfloat *)malloc(12 * sizeof *shader_vertices);
	shader_indices = (GLuint *)malloc(6 * sizeof *shader_indices);

	*(shader_vertices+0) = 0.f;
	*(shader_vertices+1) = 0.f;
	*(shader_vertices+2) = 1.f;
	*(shader_vertices+3) = 0.f;
	*(shader_vertices+4) = 1.f;
	*(shader_vertices+5) = 1.f;
	*(shader_vertices+6) = 1.f;
	*(shader_vertices+7) = 1.f;
	*(shader_vertices+8) = 0.f;
	*(shader_vertices+9) = 1.f;
	*(shader_vertices+10) = 0.f;
	*(shader_vertices+11) = 0.f;

	for (int i = 0; i < 6; i++) {
		*(shader_indices+i) = i;
	}

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof *shader_vertices, shader_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof *shader_indices, shader_indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	shader_pid = glCreateProgram();
	GLuint vertex_shader = shader_load(vertex_path, GL_VERTEX_SHADER);
	if (0 == vertex_shader) {
		glDeleteProgram(shader_pid);
		shader_pid = 0;
		return;
	}
	glAttachShader(shader_pid, vertex_shader);

	GLuint fragment_shader = shader_load(fragment_path, GL_FRAGMENT_SHADER);
	if (0 == fragment_shader) {
		glDeleteShader(vertex_shader);
		glDeleteProgram(shader_pid);
		shader_pid = 0;
		return;
	}
	glAttachShader(shader_pid, fragment_shader);

	glLinkProgram(shader_pid);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);	
}

static void shader_render(void)
{
	glUseProgram(shader_pid);
	glLoadIdentity();
	glScalef(UI_WINDOW_WIDTH, UI_WINDOW_HEIGHT, 1.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexPointer(2, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	glUseProgram(0);
}

static void shader_free(void)
{
	glDeleteProgram(shader_pid);
	free(shader_vertices);
	free(shader_indices);
	shader_pid = 0;
}
