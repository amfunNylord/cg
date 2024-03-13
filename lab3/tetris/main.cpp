#include <GLFW/glfw3.h>
#include "TimeFunctions.h"
#include "View.h"
#include "Field.h"

Field field;
View view(field);

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		if (field.IsNoWallLeft())
		{
			field.MovingPieceByUser(LEFT_DIRECTION);
			view.DrawUI(field);
		}
	}
	else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		if (field.IsNoWallRight())
		{
			field.MovingPieceByUser(RIGHT_DIRECTION);
			view.DrawUI(field);
		}
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		if (field.IsNoWallDown())
		{
			field.MovingPieceByUser(DOWN_DIRECTION);
			view.DrawUI(field);
		}
	}
	else if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		if (field.IsPossibleRotate())
		{
			field.RotatePiece();
			view.DrawUI(field);
		}
	}
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		field.Pause();
	}
	else if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		field.Unpause();
	}
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Tetris", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, WINDOW_SIZE, WINDOW_SIZE);

		if (!field.IsPaused())
		{
			if (field.IsNeededNewPiece())
			{
				field.AddPiece(field.GetCurrentPiece());
			}
			else
			{
				if (field.IsNoWallDown())
				{
					field.MovingPieceByGame();
				}
				else
				{
					if (field.IsNeededClearLines())
					{
						field.ClearLines();
					}
					if (field.IsFull())
					{
						field.Pause();
						field.Clear();
						field.ResetScore();
						field.ResetLevel();
						field.ResetLinesLeft();
						field.ResetSpeed();

					}

					field.SetCurrentPiece();
					field.AddPiece(field.GetCurrentPiece());
					field.SetNextPiece();
				}
			}
		}

		view.DrawUI(field);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		WaitTime(field.GetSpeed());
	}

	glfwTerminate();
	return 0;
}
