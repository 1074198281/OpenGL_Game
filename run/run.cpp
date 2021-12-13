//#define GLEW_STATIC
//#include "include/openGL/glad.h"
#include "resource_manager.h"
#include "game.h"
#include "texture.h"
#include "shader.h"


#include "../../OpenGL/include/glew/include/GL/glew.h"
#include "../../OpenGL/include/GLFW/glfw3.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

CGame Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "breakout", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();    //call it once to catch glewinit() bug, all other errors are now from our application

	glfwSetKeyCallback(window, key_callback);

	//OpenGL configuration

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//initialize game
	Breakout.Init();

	//deltatime  variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	//start game within menu state
	Breakout.State = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		//calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();			//?

		//deltatime = 0.001f
		//mmanager user input
		Breakout.ProcessInput(deltaTime);

		//update gamme state
		Breakout.Update(deltaTime);

		//render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();

		glfwSwapBuffers(window);
	}

	//delta all resources as loaded using the resource manager
	CResourceManager::Clear();
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int code)
{
	//when a user presses the escape key, we set WindowShouldClose property to true closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key > 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			Breakout.Keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE)
		{
			Breakout.Keys[key] = GL_FALSE;
		}
	}
}
