#include "../libgl/pch.h"
#include "Scene.h"

void Scene::Draw()
{
	float x = 0, y = 0, z = 0;

	float u = 0, v = 0;
	glBegin(GL_TRIANGLE_STRIP);
	for (v = 0; v < 1 + 0.01; v += 0.01)
	{
		for (u = 0; u <= 1; u += 0.01)
		{
			glVertex3f(u, v, z);
			glColor3f(u, v, z);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (u = 0; u <= 1; u += 0.01)
	{
		for (v = 0; v < 1 + 0.01; v += 0.01)
		{
			glVertex3f(u, v, z);
			glColor3f(u, v, z);
		}
	}
	glEnd();
	glFlush();
}