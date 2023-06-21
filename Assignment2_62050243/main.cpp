#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>

#include <ctime>
#include <chrono>
#include <thread>

#include "Shader.h"
#include "Window.h"
#include "Mesh.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;


bool direction = true;
bool direction2 = true;
bool switchLR = true;
int secondDirection = 0;
float triOffset = 0.0f;
float triOffset2 = 0.0f;
float moveCricle = 0.0f;
float triMaxOffset = 0.3f;//7
float triMaxOffset2 = 1.5f;
float triIncrement = 0.5f;


float XOffset = -0.0f;
float YOffset = 0.0f;
float ZOffset = 0.0f;


float curAngle = 0.0f;

//Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//Fragment Shader
static const char* fShader = "Shaders/shader.frag";

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);



void CreateObject()
{
    unsigned int rectIndices[] =    //Square
    {
        0, 2, 1,
        0, 3, 2,
    };
    
    GLfloat rectVertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    Mesh *rect = new Mesh();
    rect->CreateMesh(rectVertices, rectIndices, 12, 6);
    meshList.push_back(rect);

    unsigned int triangleIndices[] =    //Triangle
    {
        0, 1, 2,
    };
    
    GLfloat triangleVertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    Mesh *triangle = new Mesh();
    triangle->CreateMesh(triangleVertices, triangleIndices, 9, 3);
    meshList.push_back(triangle);
    
}
void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}



void Update(long elapsedTime)
{

    float cameraSpeed = 2.5 * elapsedTime / 1000.0;

    if (direction)
    {
        triOffset += (triIncrement * elapsedTime / 1000.0);
    }
    else
    {
        triOffset -= (triIncrement * elapsedTime / 1000.0);
    }

    if (secondDirection == 1)
    {
        XOffset -= (triIncrement * elapsedTime / 100.0);
    }
    else if (secondDirection == -1)
    {
        XOffset += (triIncrement * elapsedTime / 100.0);
    }

    if (secondDirection == -2)
    {
        YOffset -= (triIncrement * elapsedTime / 100.0);
    }
    else if (secondDirection == 2)
    {
        YOffset += (triIncrement * elapsedTime / 100.0);
    }

    if (secondDirection == 3)
    {
        ZOffset -= (triIncrement * elapsedTime / 100.0);
    }
    else if (secondDirection == -3)
    {
        ZOffset += (triIncrement * elapsedTime / 100.0);
    }

    if (secondDirection == 4)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    else if (secondDirection == -4)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (secondDirection == 5)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    else if (secondDirection == -5)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (direction2)
    {
        triOffset2 += (0.1 * elapsedTime / 100.0);
    }

    
    if (switchLR)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    else if (!switchLR)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    

    if(abs(triOffset) >= triMaxOffset) direction = !direction;

    if(abs(triOffset2) >= triMaxOffset2)
    {
        triOffset2 = 0.0;
        if(switchLR) switchLR = false;
        else switchLR = true;
    } 


    curAngle += 0.01f;
    if (curAngle >= 360)
    {
        curAngle -= 360;
    }

}

void KeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    // A D
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        //move triangle left
        secondDirection = 1;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        //move triangle right
        secondDirection = -1;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }
    
    // W S
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        //move triangle up
        secondDirection = 2;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        //move triangle down
        secondDirection = -2;
    }
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }
    
    // zoom in out
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        //
        secondDirection = 3;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        //
        secondDirection = -3;
    }
    else if (key == GLFW_KEY_E && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }

    // J L
    if (key == GLFW_KEY_J && action == GLFW_PRESS)
    {
        //move triangle left
        secondDirection = 4;
    }
    else if (key == GLFW_KEY_J && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        //move triangle right
        secondDirection = -4;
    }
    else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }
    
    // I K
    if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        //move triangle up
        secondDirection = 5;
    }
    else if (key == GLFW_KEY_I && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }

    if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
        //move triangle down
        secondDirection = -5;
    }
    else if (key == GLFW_KEY_K && action == GLFW_RELEASE)
    {
        secondDirection = 0;
    }
}
void draw(float x, float y, float z, float R, float G, float B, GLuint uniformModel, GLuint uniformView, GLuint uniformProjection, GLuint uniformColor)
{
    glm::vec4 color;
    glm::mat4 model (1.0f);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    color = glm::vec4(R/255.0, G/255.0, B/255.0, 1);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(uniformColor, 1, glm::value_ptr(color));
    meshList[0]->RenderMesh();
}

void cockmeat(float x2, float y2, float z2, GLuint uniformModel, GLuint uniformView, GLuint uniformProjection, GLuint uniformColor){
    float Dc1 = y2 + 0.0f;
        draw(x2+0.0f, Dc1, z2,      136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc1, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc1, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc1, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc1, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc1, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc1, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc1, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc1, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc2 = y2 + 0.02f;
        draw(x2-0.08f, Dc2, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc2, z2,     156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc2, z2,     136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc2, z2,     156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.0f, Dc2, z2,      163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc2, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc2, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc2, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc3 = y2 + 0.04f;
        draw(x2+0.0f, Dc3, z2,      163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc3, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc3, z2,     136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc3, z2,     130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc3, z2,     156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc3, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.1f, Dc3, z2,      71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc4 = y2 + 0.06f;
        draw(x2+0.0f, Dc4, z2,      107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc4, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc4, z2,     136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc4, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc4, z2,     124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.1f, Dc4, z2,      71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        
        float Dc5 = y2 + 0.08f;
        draw(x2-0.1f, Dc5, z2,      71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc5, z2,     124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc5, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc5, z2,     156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc5, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        
        float Dc6 = y2 + 0.1f;
        draw(x2-0.02f, Dc6, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc6, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc6, z2,     156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc6, z2,     130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.1f,  Dc6, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc7 = y2 + 0.12f;
        draw(x2-0.1f, Dc7, z2,      82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc7, z2,     130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc7, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc7, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc8 = y2 + 0.14f;
        draw(x2-0.04f, Dc8, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc8, z2,     157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc8, z2,     124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.1f, Dc8, z2,      82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        
        float Dc9 = y2 + 0.16f;
        draw(x2-0.08f, Dc9, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc9, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        
        float Dc10 = y2 - 0.02f;
        draw(x2+0.0f, Dc10, z2,     130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc10, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc10, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc10, z2,    157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc10, z2,    163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.1f, Dc10, z2,     107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc10, z2,    157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc10, z2,    163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc10, z2,    124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc10, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc11 = y2 - 0.04f;
        draw(x2+0.0f, Dc11, z2,     130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc11, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc11, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc11, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc11, z2,    136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.1f, Dc11, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.12f, Dc11, z2,    107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc11, z2,    136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc11, z2,    163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc11, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.08f, Dc11, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc12 = y2 - 0.06f;
        draw(x2+0.0f, Dc12, z2,     136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc12, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc12, z2,    130.0, 72.0, 58.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc12, z2,    136.0, 79.0, 64.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc12, z2,    157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.1f, Dc12, z2,     163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.12f, Dc12, z2,    107.0, 58.0, 42.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc12, z2,    157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc12, z2,    124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc12, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc13 = y2 - 0.08f;
        draw(x2+0.0f, Dc13, z2,     156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc13, z2,    163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc13, z2,    163.0, 112.0, 90.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc13, z2,    156.0, 101.0, 84.0,     uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc13, z2,    157.0, 97.0, 71.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.1f, Dc13, z2,     124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.12f, Dc13, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc13, z2,    124.0, 64.0, 47.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc13, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.06f, Dc13, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        
        float Dc14 = y2 - 0.1f;
        draw(x2+0.0f, Dc14, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc14, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc14, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc14, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc14, z2,    82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.1f, Dc14, z2,     82.0, 47.0, 31.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.12f, Dc14, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.02f, Dc14, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2-0.04f, Dc14, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float Dc15 = y2 - 0.12f;
        draw(x2+0.0f, Dc15, z2,     71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.02f, Dc15, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.04f, Dc15, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.06f, Dc15, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.08f, Dc15, z2,    71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x2+0.1f, Dc15, z2,     71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
}

void meat(float x, float y, float z, GLuint uniformModel, GLuint uniformView, GLuint uniformProjection, GLuint uniformColor){
    //meat
        float D1 = y + 0.0f;
        draw(x+0.0f, D1, z,         221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D1, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D1, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D1, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D1, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D1, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D1, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D1, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D1, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float D2 = y + 0.02f;
        draw(x-0.08f, D2, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D2, z,        226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D2, z,        221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D2, z,        226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.0f, D2, z,         232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D2, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D2, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D2, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float D3 = y + 0.04f;
        draw(x+0.0f, D3, z,         232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D3, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D3, z,        221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D3, z,        209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D3, z,        226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D3, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.1f, D3, z,         71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float D4 = y + 0.06f;
        draw(x+0.0f, D4, z,         173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D4, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D4, z,        211.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D4, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D4, z,        188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.1f, D4, z,         71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        
        float D5 = y + 0.08f;
        draw(x-0.1f, D5, z,         71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D5, z,        188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D5, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D5, z,        226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D5, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        
        float D6 = y + 0.1f;
        draw(x-0.02f, D6, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D6, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D6, z,        226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D6, z,        209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.1f,  D6, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float D7 = y + 0.12f;
        draw(x-0.1f, D7, z,         150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D7, z,        209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D7, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D7, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float D8 = y + 0.14f;
        draw(x-0.04f, D8, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D8, z,        226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D8, z,        188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.1f, D8, z,         150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        
        float D9 = y + 0.16f;
        draw(x-0.08f, D9, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D9, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        
        float D10 = y - 0.02f;
        draw(x+0.0f, D10, z,        209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D10, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D10, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D10, z,       226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D10, z,       232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.1f, D10, z,        173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D10, z,       226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D10, z,       232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D10, z,       188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D10, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float D11 = y - 0.04f;
        draw(x+0.0f, D11, z,        209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D11, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D11, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D11, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D11, z,       221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.1f, D11, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.12f, D11, z,       173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D11, z,       221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D11, z,       232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D11, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.08f, D11, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float D12 = y - 0.06f;
        draw(x+0.0f, D12, z,        221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D12, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D12, z,       209.0, 46.0, 38.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D12, z,       221.0, 56.0, 48.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D12, z,       226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.1f, D12, z,        232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.12f, D12, z,       173.0, 51.0, 46.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D12, z,       226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D12, z,       188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D12, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);

        float D13 = y - 0.08f;
        draw(x+0.0f, D13, z,        226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D13, z,       232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D13, z,       232.0, 138.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D13, z,       226.0, 114.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D13, z,       226.0, 98.0, 90.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.1f, D13, z,        188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.12f, D13, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D13, z,       188.0, 41.0, 34.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D13, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.06f, D13, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        
        float D14 = y - 0.1f;
        draw(x+0.0f, D14, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D14, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D14, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D14, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D14, z,       150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.1f, D14, z,        150.0, 33.0, 27.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.12f, D14, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.02f, D14, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x-0.04f, D14, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);

        float D15 = y - 0.12f;
        draw(x+0.0f, D15, z,        71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.02f, D15, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.04f, D15, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.06f, D15, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.08f, D15, z,       71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x+0.1f, D15, z,        71.0, 10.0, 6.0,        uniformModel,uniformView,uniformProjection,uniformColor);
    
}

void furnace(float x3, float y3, float z3, GLuint uniformModel, GLuint uniformView, GLuint uniformProjection, GLuint uniformColor)
{
    //furnace
        float Df1 = y3 + 0.0f;
        draw(x3-0.14f, Df1, z3,     59.0, 59.0, 59.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df1, z3,     68.0, 68.0, 68.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df1, z3,     120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df1, z3,     130.0, 130.0, 130.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df1, z3,     93.0, 93.0, 93.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df1, z3,     141.0, 141.0, 141.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df1, z3,     140.0, 140.0, 140.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df1, z3,     148.0, 148.0, 148.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df1, z3,     146.0, 146.0, 146.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df1, z3,     144.0, 144.0, 144.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df1, z3,     141.0, 141.0, 141.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df1, z3,     76.0, 76.0, 76.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df1, z3,     119.0, 119.0, 119.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df1, z3,     93.0, 93.0, 93.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df1, z3,     120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df1, z3,     59.0, 59.0, 59.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df2 = y3 + 0.02f;
        draw(x3-0.14f, Df2, z3,     58.0, 58.0, 58.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df2, z3,     92.0, 92.0, 92.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df2, z3,     91.0, 91.0, 91.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df2, z3,     37.0, 37.0, 37.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df2, z3,     112.0, 112.0, 112.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df2, z3,     182.0, 182.0, 182.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df2, z3,     170.0, 170.0, 170.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df2, z3,     169.0, 169.0, 169.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df2, z3,     170.0, 170.0, 170.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df2, z3,     166.0, 166.0, 166.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df2, z3,     165.0, 165.0, 165.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df2, z3,     106.0, 106.0, 106.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df2, z3,     168.0, 168.0, 168.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df2, z3,     88.0, 88.0, 88.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df2, z3,     82.0, 82.0, 82.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df2, z3,     58.0, 58.0, 58.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df3 = y3 + 0.04f;
        draw(x3-0.14f, Df3, z3,     34.0, 34.0, 34.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df3, z3,     97.0, 97.0, 97.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df3, z3,     126.0, 126.0, 126.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df3, z3,     40.0, 40.0, 40.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df3, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df3, z3,     12.0, 12.0, 12.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df3, z3,     14.0, 14.0, 14.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df3, z3,     17.0, 17.0, 17.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df3, z3,     15.0, 15.0, 15.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df3, z3,     18.0, 18.0, 18.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df3, z3,     20.0, 20.0, 20.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df3, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df3, z3,     166.0, 166.0, 166.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df3, z3,     135.0, 135.0, 135.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df3, z3,     97.0, 97.0, 97.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df3, z3,     34.0, 34.0, 34.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df4 = y3 + 0.06f;
        draw(x3-0.14f, Df4, z3,     36.0, 36.0, 36.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df4, z3,     88.0, 88.0, 88.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df4, z3,     126.0, 126.0, 126.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df4, z3,     39.0, 39.0, 39.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df4, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df4, z3,     163.0, 163.0, 163.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df4, z3,     104.0, 104.0, 104.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df4, z3,     55.0, 55.0, 55.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df4, z3,     36.0, 36.0, 36.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df5 = y3 + 0.08f;
        draw(x3-0.14f, Df5, z3,     36.0, 36.0, 36.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df5, z3,     114.0, 114.0, 114.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df5, z3,     120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df5, z3,     76.0, 76.0, 76.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df5, z3,     53.0, 53.0, 53.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df5, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df5, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df5, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df5, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df5, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df5, z3,     0.0, 0.0, 0.0,          uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df5, z3,     55.0, 55.0, 55.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df5, z3,     82.0, 82.0, 82.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df5, z3,     134.0, 134.0, 134.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df5, z3,     112.0, 112.0, 112.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df5, z3,     36.0, 36.0, 36.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df6 = y3 + 0.1f;
        draw(x3-0.14f, Df6, z3,     40.0, 40.0, 40.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df6, z3,     80.0, 80.0, 80.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df6, z3,     92.0, 92.0, 92.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df6, z3,     111.0, 111.0, 111.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df6, z3,     109.0, 109.0, 109.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df6, z3,     37.0, 37.0, 37.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df6, z3,     51.0, 51.0, 51.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df6, z3,     49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df6, z3,     34.0, 34.0, 34.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df6, z3,     40.0, 40.0, 40.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df6, z3,     33.0, 33.0, 33.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df6, z3,     65.0, 65.0, 65.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df6, z3,     105.0, 105.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df6, z3,     138.0, 138.0, 138.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df6, z3,     105.0, 105.0, 105.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df6, z3,     40.0, 40.0, 40.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df7 = y3 + 0.12f;
        draw(x3-0.14f, Df7, z3,     48.0, 48.0, 48.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df7, z3,     82.0, 82.0, 82.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df7, z3,     120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df7, z3,     85.0, 85.0, 85.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df7, z3,     98.0, 98.0, 98.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df7, z3,     143.0, 143.0, 143.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df7, z3,     143.0, 143.0, 143.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df7, z3,     100.0, 100.0, 100.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df7, z3,     79.0, 79.0, 79.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df7, z3,     132.0, 132.0, 132.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df7, z3,     126.0, 126.0, 126.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df7, z3,     94.0, 94.0, 94.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df7, z3,     120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df7, z3,     93.0, 93.0, 93.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df7, z3,     80.0, 80.0, 80.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df7, z3,     47.0, 47.0, 47.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df8 = y3 + 0.14f;
        draw(x3-0.14f, Df8, z3,     49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df8, z3,     107.0, 107.0, 107.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df8, z3,     89.0, 89.0, 89.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df8, z3,     97.0, 97.0, 97.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df8, z3,     71.0, 71.0, 71.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df8, z3,     88.0, 88.0, 88.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df8, z3,     114.0, 114.0, 114.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df8, z3,     114.0, 114.0, 114.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df8, z3,     79.0, 79.0, 79.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df8, z3,     97.0, 97.0, 97.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df8, z3,     100.0, 100.0, 100.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df8, z3,     97.0, 97.0, 97.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df8, z3,     87.0, 87.0, 87.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df8, z3,     69.0, 69.0, 69.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df8, z3,     85.0, 85.0, 85.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df8, z3,     49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df9 = y3 + 0.16f;
        draw(x3-0.14f, Df9, z3,     49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df9, z3,     53.0, 53.0, 53.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df9, z3,     53.0, 53.0, 53.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df9, z3,     53.0, 53.0, 53.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df9, z3,     51.0, 51.0, 51.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df9, z3,     47.0, 47.0, 47.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df9, z3,     47.0, 47.0, 47.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df9, z3,     45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df9, z3,     45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df9, z3,     36.0, 36.0, 36.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df9, z3,     59.0, 59.0, 59.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df9, z3,     55.0, 55.0, 55.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df9, z3,     45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df9, z3,     37.0, 37.0, 37.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df9, z3,     53.0, 53.0, 53.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df9, z3,     49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df10 = y3 - 0.02f;
        draw(x3-0.14f, Df10, z3,    63.0, 63.0, 63.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df10, z3,    142.0, 142.0, 142.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df10, z3,    197.0, 197.0, 197.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df10, z3,    217.0, 217.0, 217.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df10, z3,    217.0, 217.0, 217.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df10, z3,    228.0, 228.0, 228.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df10, z3,    243.0, 243.0, 243.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df10, z3,    242.0, 242.0, 242.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df10, z3,    239.0, 239.0, 239.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df10, z3,    243.0, 243.0, 243.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df10, z3,    231.0, 231.0, 231.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df10, z3,    217.0, 217.0, 217.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df10, z3,    217.0, 217.0, 217.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df10, z3,    197.0, 197.0, 197.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df10, z3,    142.0, 142.0, 142.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df10, z3,    63.0, 63.0, 63.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df11 = y3 - 0.04f;
        draw(x3-0.14f, Df11, z3,    47.0, 47.0, 47.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df11, z3,    120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df11, z3,    202.0, 202.0, 202.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df11, z3,    217.0, 217.0, 217.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df11, z3,    219.0, 219.0, 219.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df11, z3,    237.0, 237.0, 237.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df11, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df11, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df11, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df11, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df11, z3,    226.0, 226.0, 226.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df11, z3,    230.0, 230.0, 230.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df11, z3,    236.0, 236.0, 236.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df11, z3,    197.0, 197.0, 197.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df11, z3,    120.0, 120.0, 120.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df11, z3,    48.0, 48.0, 48.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df12 = y3 - 0.06f;
        draw(x3-0.14f, Df12, z3,    49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df12, z3,    172.0, 172.0, 172.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df12, z3,    217.0, 217.0, 217.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df12, z3,    230.0, 230.0, 230.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df12, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df12, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df12, z3,    255.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df12, z3,    204.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df12, z3,    255.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df12, z3,    204.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df12, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df12, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df12, z3,    229.0, 229.0, 229.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df12, z3,    213.0, 213.0, 213.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df12, z3,    166.0, 166.0, 166.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df12, z3,    49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df13 = y3 - 0.08f;
        draw(x3-0.14f, Df13, z3,    45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df13, z3,    196.0, 196.0, 196.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df13, z3,    299.0, 299.0, 299.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df13, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df13, z3,    205.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df13, z3,    205.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df13, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df13, z3,    201.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df13, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df13, z3,    253.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df13, z3,    207.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df13, z3,    207.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df13, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df13, z3,    241.0, 241.0, 241.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df13, z3,    175.0, 175.0, 175.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df13, z3,    45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df14 = y3 - 0.1f;
        draw(x3-0.14f, Df14, z3,    49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df14, z3,    222.0, 222.0, 222.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df14, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df14, z3,    251.0, 0.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df14, z3,    251.0, 161.0, 3.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df14, z3,    251.0, 161.0, 3.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df14, z3,    251.0, 161.0, 3.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df14, z3,    251.0, 2.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df14, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df14, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df14, z3,    253.0, 2.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df14, z3,    253.0, 2.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df14, z3,    253.0, 2.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df14, z3,    242.0, 242.0, 242.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df14, z3,    167.0, 167.0, 167.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df14, z3,    49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df15 = y3 - 0.12f;
        draw(x3-0.14f, Df15, z3,    49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df15, z3,    222.0, 222.0, 222.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df15, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df15, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df15, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df15, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df15, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df15, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df15, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df15, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df15, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df15, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df15, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df15, z3,    240.0, 240.0, 240.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df15, z3,    175.0, 175.0, 175.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df15, z3,    45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);

        float Df16 = y3 - 0.14f;
        draw(x3-0.14f, Df16, z3,    49.0, 49.0, 49.0,       uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.12f, Df16, z3,    222.0, 222.0, 222.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.10f, Df16, z3,    135.0, 67.0, 66.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.08f, Df16, z3,    253.0, 1.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.06f, Df16, z3,    253.0, 169.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.04f, Df16, z3,    253.0, 1.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3-0.02f, Df16, z3,    253.0, 169.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.00f, Df16, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.02f, Df16, z3,    253.0, 1.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.04f, Df16, z3,    253.0, 169.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.06f, Df16, z3,    253.0, 252.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.08f, Df16, z3,    253.0, 161.0, 0.0,      uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.10f, Df16, z3,    253.0, 1.0, 0.0,        uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.12f, Df16, z3,    240.0, 240.0, 240.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.14f, Df16, z3,    175.0, 175.0, 175.0,    uniformModel,uniformView,uniformProjection,uniformColor);
        draw(x3+0.16f, Df16, z3,    45.0, 45.0, 45.0,       uniformModel,uniformView,uniformProjection,uniformColor);
}

int main()
{
    mainWindow = Window(WIDTH, HEIGHT);
    mainWindow.initialise();

    CreateObject();
    CreateShaders();

    GLuint uniformModel = 0, uniformView = 0, uniformProjection = 0, uniformColor = 0;
    auto currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long lastTime = currentTime;
    long elapsTime;

    glfwSetKeyCallback(mainWindow.getWindow(), KeyboardHandler);

    glm::vec3 positions[] = {
        glm::vec3( 0.2f,  0.1f,  0.1f),
        glm::vec3( 2.0f,  5.0f, -1.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -1.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-0.4f,  0.4f, -1.5f)
        };
    

    //Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        elapsTime = currentTime - lastTime;

        lastTime = currentTime;

        //Get + Handle user input events
        glfwPollEvents();

        Update(elapsTime);

        //Clear window
            float radius = 1.0f;
            float RGB1  = tan(glfwGetTime()/triOffset/100) * radius;
            float RGB2   = tan(glfwGetTime()/triOffset/100) * radius;
        glClearColor(RGB1 + 0.2, RGB2  + 0.5, RGB1+RGB2 +  0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw here
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformColor = shaderList[0].GetColorLocation();
        
        glm::mat4 model (1.0f);

        // camera/view transformation
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        //meat control
        float x = XOffset;
        float y = YOffset-0.1f;
        float z = -0.5f + ZOffset;

        //cookmeat control
        float x2 = XOffset;
        float y2 = YOffset;
        float z2 = -0.5f - ZOffset;


        //furnace control
        float x3 = 0.0f;
        float y3 = 0.0f;
        float z3 = -0.499f + ZOffset;

        

        furnace(0.0f, 0.0f, -3.5f, uniformModel,uniformView,uniformProjection,uniformColor);
        
        if(switchLR)
        {
            float radius = 1.0f;
            float camX   = tan(triOffset2) * radius;
            float camZ   = tan(triOffset2) * radius;
            view = glm::lookAt(glm::vec3(camX , 0.0f , camZ ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
            
            for (size_t i = 0; i < 11; i++)
            {
                meat(positions[i].x+x , positions[i].y+y , positions[i].z ,uniformModel,uniformView,uniformProjection,uniformColor);
            }
        }else
        {
            float radius = 1.0f;
            float camX   = tan(triOffset2 + 1.5f) * radius;
            float camZ   = tan(triOffset2 + 1.5f) * radius;
            view = glm::lookAt(glm::vec3(camX , 0.0f , camZ ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

            for (size_t i = 0; i < 11; i++)
            {
                cockmeat(positions[i].x+x , positions[i].y+y , positions[i].z ,uniformModel,uniformView,uniformProjection,uniformColor);
            }
        }
        
        
        glUseProgram(0);
        //end draw

        mainWindow.swapBuffers();
    }

    return 0;
}


