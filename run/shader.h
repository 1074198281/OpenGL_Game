#pragma once
#pragma comment(lib, "opengl32.lib")
#define GLEW_STATIC

//#include "../../OpenGL/glad/include/glad/glad.h"
#include "../../OpenGL/include/glew/include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/GLFW/glfw3native.h"
#include "../../OpenGL/OpenGL_VS2019/openGL/include/openGL/glut.h"
#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/glm.hpp"
#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/gtc/type_ptr.hpp"
#ifndef SHADER_H
#define SHADER_H

#include "string"

class CShader
{
	public:
		//state
		GLuint ID;
		//Constructor
		CShader(){ }
		//Compiles the current shader as active
		CShader& Use();
		//Compiles the shader from given source code
		void Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

        // Utility functions
        void    SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
        void    SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);
        void    SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
        void    SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
        void    SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
        void    SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
        void    SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
        void    SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
        void    SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);
public:
    // Checks if compilation or linking failed and if so, print the error logs
    void    checkCompileErrors(GLuint object, std::string type);

};


#endif