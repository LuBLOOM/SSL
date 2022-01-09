#ifndef __SSL_SHADER_H
#define __SSL_SHADER_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLuint shader_load(const char *, GLenum);
void shader_slog(GLuint);
void shader_plog(GLuint);

#endif /* __SSL_SHADER_H */
