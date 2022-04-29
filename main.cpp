#include"Maths.h"
#include<iostream>

# define M_PI 3.14159265358979323846


Quad quad;
Quad static_quad;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	quad.key_callback(window, key, scancode, action, mods);
	if (Math::CheckProjections(quad, static_quad)) {
		quad.GoBack();
	}
	else {

	}
}

int main(void)
{
	static_quad.SetQuad(0.8, 0, 0.4, 0.2);
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	quad.SetQuad(0, 0, 0.4, 0.6);

	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		quad.BuildSquare();
		static_quad.BuildSquare();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}