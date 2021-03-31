// Dependencies
#include <glew.h>
#include <glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Library Includes
#include <iostream>

// header files
#include "Shader.h"
#include "Utility.h"
#include "SceneManager.h"
#include "Camera.h"

// functions
void initialSetup();
void update();
void render();

// global variables
GLFWwindow* windowMain = nullptr;
int windWidth = 1200;
int windHeight = 800;
//GLuint fixedTriangleProgram;
SceneManager manager;


int main()
{
	// set up the initial elements of the project
	initialSetup();

	// main loop
	while (glfwWindowShouldClose(windowMain) == false)
	{
		// render all the objects
		render();

		// update all objets and run the project
		update();
	}

	// ensure correct shutdown of GLFW
	glfwTerminate();
	return(0);
}

// initializing GLFW and setting the version to 4.6 with only core funtionality avalibility
void initialSetup()
{
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#ifndef _DEBUG  /*for release*/
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, false);
#else           /*for debug*/
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	//int count;
	//GLFWmonitor** monitors = glfwGetMonitors(&count);

	// create an GLFW controlled context window
	windowMain = glfwCreateWindow(windWidth, windHeight, "Summative 1", NULL, NULL);
	if (windowMain == NULL)
	{
		std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
		system("pause");

		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(windowMain);

	// initializing GLEW to populate OpenGl function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize properl. Terminating Program." << std::endl;
		system("pause");

		glfwTerminate();
		return;
	}

	// set the colour of the window when the buffer is cleared
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red

	// maps the range of the size to NDC (-1 -> 1)
	glViewport(0, 0, static_cast<GLsizei>(windWidth), static_cast<GLsizei>(windHeight));

	// enable OpenGL debug context if context allows for debug context
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
		glDebugMessageCallback(Utility::MessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	// setup time stuff
	Utility::m_prevTime = static_cast<float>(glfwGetTime());

	// set up camera stuff
	Camera::initialise(static_cast<float>(windWidth), static_cast<float>(windHeight));

	// ensure loaded images display the right way
	stbi_set_flip_vertically_on_load(true);

	// set up all the scene objects
	manager.initialize();
}

// update all objects and run the process
void update()
{
	glfwPollEvents();

	Utility::manageTime(static_cast<float>(glfwGetTime())); // updating delta time
	manager.update(); // updating all the scene objects
}

// render all objects
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	manager.render(); // rendering all the scene objects

	glfwSwapBuffers(windowMain);
}


