#include "../libgl/pch.h"
#include "CMyApplication.h"
#include <iostream>

int main()
{
	CMyApplication application("Morphing", 800, 600);
	try
	{
		if (glewInit() != GLEW_OK)
		{
			throw std::runtime_error("Failed to initialize GLEW");
		}
		application.MainLoop();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
	}
	return 0;
}