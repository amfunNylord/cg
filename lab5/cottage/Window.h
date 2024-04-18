#pragma once

#include "BaseWindow.h"
#include "Cottage.h"
#include "Environment.h"
#include "TextureLoader.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, char const* title);

	~Window() noexcept;

private:
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	// ������� ������ ������ ������ ���������
	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnKey(int key, int scancode, int action, int mods) override;

	void OnRunStart() override;
	void SetupLight();
	void SetupTextures();

	void Draw(int width, int height) override;

	void SetupCameraMatrix() const;

	void SetupFog();

	// ���������� �� ������ �� ����� ��������
	static constexpr double DISTANCE_TO_ORIGIN = 12;

	TextureLoader m_textureLoader;

	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, -DISTANCE_TO_ORIGIN, 10.0 },
		glm::dvec3{ 0.0, 0.0, 0.0 },
		glm::dvec3{ 0.0, 0.0, 1.0 });

	bool m_fogEnabled = false;

	Cottage m_cottage;
	Environment m_environment;

	Texture m_groundTexture;

	Texture m_wallTexture;
	Texture m_windowTexture;
	Texture m_door;
	Texture m_garageDoorTexture;
	Texture m_roofTexture;
};
