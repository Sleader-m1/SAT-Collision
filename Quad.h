#pragma once
#include<cmath>
#include <GLFW\glfw3.h>
#include<vector>

# define M_PI 3.14159265358979323846

class Quad {
	double angle_of_rotation = 0;
	double posX, posY;
	double width, heigth;
	double angle_from_beginning;
	int last_move;
public:
	Quad() {
		posX = posY = 0;
		width = heigth = 0.5;
		angle_from_beginning = atan(width / heigth);
	}
	Quad(double x_position, double y_position, double Width, double  Heigth) :posX(x_position), posY(y_position), width(Width), heigth(Heigth) {
		angle_from_beginning = atan(width / heigth);
	}

	void SetQuad(double x_position, double y_position, double Width, double  Heigth) {
		posX = x_position;
		posY = y_position;
		width = Width;
		heigth = Heigth;
		angle_from_beginning = atan(width / heigth);
	}

	void BuildSquare() {
		double diag = std::sqrt(width * width / 4 + heigth * heigth / 4);
		glBegin(GL_QUADS);
		glVertex2f(diag * sin(angle_from_beginning - angle_of_rotation) + posX, diag * cos(angle_from_beginning - angle_of_rotation) + posY);
		glVertex2f(diag * -sin(angle_from_beginning + angle_of_rotation) + posX, diag * cos(angle_from_beginning + angle_of_rotation) + posY);
		glVertex2f(diag * -sin(M_PI - (angle_from_beginning - angle_of_rotation)) + posX, diag * cos(M_PI - (angle_from_beginning - angle_of_rotation)) + posY);
		glVertex2f(diag * sin(M_PI - (angle_from_beginning + angle_of_rotation)) + posX, diag * cos(M_PI - (angle_from_beginning + angle_of_rotation)) + posY);
		glEnd();
	}

	std::vector<std::pair<double, double>> GetCoordsOfVertexes() {
		double diag = std::sqrt(width * width / 4 + heigth * heigth / 4);
		return std::vector<std::pair<double, double>> {
			std::make_pair(diag* sin(angle_from_beginning - angle_of_rotation) + posX, diag* cos(angle_from_beginning - angle_of_rotation) + posY),
				std::make_pair(diag * -sin(angle_from_beginning + angle_of_rotation) + posX, diag* cos(angle_from_beginning + angle_of_rotation) + posY),
				std::make_pair(diag * -sin(M_PI - (angle_from_beginning - angle_of_rotation)) + posX, diag* cos(M_PI - (angle_from_beginning - angle_of_rotation)) + posY),
				std::make_pair(diag* sin(M_PI - (angle_from_beginning + angle_of_rotation)) + posX, diag* cos(M_PI - (angle_from_beginning + angle_of_rotation)) + posY)
		};
	}

	void RotateLeft() {
		angle_of_rotation += 0.05;
	}

	void RotateRight() {
		angle_of_rotation -= 0.05;
	}

	void MoveUp() {
		posY += 0.01;
	}

	void MoveDown() {
		posY -= 0.01;
	}

	void MoveLeft() {
		posX -= 0.01;
	}

	void MoveRight() {
		posX += 0.01;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		else if (key == GLFW_KEY_Q)
			RotateLeft();
		else if (key == GLFW_KEY_E)
			RotateRight();
		else if (key == GLFW_KEY_W) {
			MoveUp();
		}
		else if (key == GLFW_KEY_S) {
			MoveDown();
		}
		else if (key == GLFW_KEY_A) {
			MoveLeft();
		}
		else if (key == GLFW_KEY_D) {
			MoveRight();
		}
		last_move = key;
	}

	void GoBack() {
		if (last_move == GLFW_KEY_Q)
			RotateRight();
		else if (last_move == GLFW_KEY_E)
			RotateLeft();
		else if (last_move == GLFW_KEY_W)
				MoveDown();
		else if (last_move == GLFW_KEY_S)
				MoveUp();
		else if (last_move == GLFW_KEY_A)
				MoveRight();
		else if (last_move == GLFW_KEY_D)
				MoveLeft();
	}
};
