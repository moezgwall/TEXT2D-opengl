#include "2dText.h"
#include "stb_ezfont.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* function implementation*/
/*  glfwSetFramebufferSizeCallback(window, framebuffer_size_callbackTXT);*/
/*glfwSetWindowUserPointer(window, &txt);*/
void framebufferSizeCallbackTXT(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
    TextS *txt = (TextS *)glfwGetWindowUserPointer(window);
    if (txt)
    {
        UpdateTextToScreenSize(txt, w, h);
    }
}

void InitTextS(TextS *txt, int w, int h, const char *vertexShaderSource, const char *fragmentShaderSource)
{
    txt->screenWidth = w;
    txt->screenHeight = h;
    txt->shader = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    glGenVertexArrays(1, &txt->vao);
    glGenBuffers(1, &txt->vbo);

    glBindVertexArray(txt->vao);
    glBindBuffer(GL_ARRAY_BUFFER, txt->vbo);
    glBufferData(GL_ARRAY_BUFFER, TEXT_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, (void *)0);
    glBindVertexArray(0);

    SetTextColor(txt, 1.0f, 1.0f, 1.0f);
}
void SetTextColor(TextS *txt, float r, float g, float b)
{
    txt->color[0] = r;
    txt->color[1] = g;
    txt->color[2] = b;
}
void UpdateTextToScreenSize(TextS *txt, int w, int h)
{
    txt->screenWidth = w;
    txt->screenHeight = h;
}
void RenderTextS(TextS *txt, const char *text, float x, float y)
{
    char buffer[TEXT_BUFFER_SIZE];
    int numQuads = stb_easy_font_print(x, y, (char *)text, NULL, buffer, TEXT_BUFFER_SIZE);

    float projection[16];
    CreateOrthoProjection(0.0f, (float)txt->screenWidth, (float)txt->screenHeight, 0.0f, projection);

    glUseProgram(txt->shader);
    glUniformMatrix4fv(glGetUniformLocation(txt->shader, "uProjection"), 1, GL_FALSE, projection);
    glUniform3fv(glGetUniformLocation(txt->shader, "uColor"), 1, txt->color);

    glBindVertexArray(txt->vao);
    glBindBuffer(GL_ARRAY_BUFFER, txt->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, numQuads * 4 * 16, buffer);
    glDrawArrays(GL_QUADS, 0, numQuads * 4); // this is cause problems in rendering TODO find a FIX!!!
    glBindVertexArray(0);
}
