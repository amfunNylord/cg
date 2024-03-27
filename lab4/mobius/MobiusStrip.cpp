#include "pch.h"
#include "MobiusStrip.h"
#include <numbers>

void MobiusStrip::Draw(void) const
{
	glClearColor(255, 255, 255, 255);
	glClear(GL_COLOR_BUFFER_BIT);

	float x = 0, y = 0, z = 0;

	double u = 0, v = 0;
	for (v = -1; v <= 1; v += 0.005)
	{
		glBegin(GL_LINE_STRIP);

		for (u = 0; u < (2 * std::numbers::pi) + 0.01; u += 0.005)
		{
			x = float((1 + v / 2 * cos(u / 2)) * cos(u));
			y = float((1 + v / 2 * cos(u / 2)) * sin(u));
			z = float(v / 2 * sin(u / 2));

			glColor3f(x, y, z);
			glVertex3f(x / 1.5f, y / 1.5f, z / 1.5f);
		}

		glEnd();
	}

	glFlush();
}