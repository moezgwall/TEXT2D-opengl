#ifndef TEXT2D_H
#define TEXT2D_H

#include <GL/glew.h>

#define TEXT_BUFFER_SIZE 10000

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint shader;
    int screenWidth;
    int screenHeight;
    float color[3];
} TextS;

void InitTextS(TextS *txt, int w, int h, const char *vertexShaderSource, const char *fragmentShaderSource);
void SetTextColor(TextS *txt, float r, float g, float b);
void UpdateTextToScreenSize(TextS *txt, int w, int h);
void RenderTextS(TextS *txt, const char *text, float x, float y);
void framebufferSizeCallbackTXT(GLFWwindow *window, int w, int h);

#endif