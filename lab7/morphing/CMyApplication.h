#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../libgl/GLApplication.h"
#include "../libgl/Shaders.h"
#include "CSurface.h"
#include "../libgl/pch.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(char const* title, int width, int height);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;

private:
	void InitShaders();
	CSurface m_surface;
	CProgram m_program;
};