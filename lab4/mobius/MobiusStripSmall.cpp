#include "pch.h"
#include "MobiusStripSmall.h"
#include <numbers>

void MobiusStripSmall::Draw(const float& angle) 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	float x = 0, y = 0, z = 0;
	float r, g, b;

	double u = 0, v = 0;
	for (v = -1; v <= 1; v += 0.05)
	{
		glBegin(GL_QUAD_STRIP);

		for (u = 0; u < (2 * std::numbers::pi) + 0.05; u += 0.05)
		{
			x = float((1 + v / 2 * cos(u / 2)) * cos(u));
			y = float((1 + v / 2 * cos(u / 2)) * sin(u));
			z = float(v / 2 * sin(u / 2));

			r = (x + 1) / 2;
			g = (y + 1) / 2; 
			b = (z + 1) / 2; 

			glColor3f(r, g, b); 
			glVertex3f(x / 3.0f, y / 3.0f, z / 3.0f);

			x = float((1 + (v + 0.05) / 2 * cos(u / 2)) * cos(u));
			y = float((1 + (v + 0.05) / 2 * cos(u / 2)) * sin(u));
			z = float((v + 0.05) / 2 * sin(u / 2));

			r = (x + 1) / 2; 
			g = (y + 1) / 2; 
			b = (z + 1) / 2; 

			glColor3f(r, g, b);
			glVertex3f(x / 3.0f, y / 3.0f, z / 3.0f);
		}

		glEnd();
	}
	glFlush();
}
