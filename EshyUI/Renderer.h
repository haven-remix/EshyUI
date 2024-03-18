
#pragma once

#include "Util.h"

#include "glm/glm.hpp"

#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <vector>

class euiRenderer
{
public:

	static void InitRenderer(GLFWwindow* Window);
	static euiRenderer* GetRenderer();

	euiRenderer(GLFWwindow* _Window);
	void BeginLoop();

	void AddToRenderQueue(class euiEntity* Entity);
	void RemoveFromRenderQueue(class euiEntity* Entity);

	void SetBackgroundColor(glm::vec4 Color) {BackgroundColor = Color;}
	void Draw(class euiEntity* Entity);

	void UpdateScreenSize(int Width, int Height);
	void OnScreenSizeChanged(GLFWwindow* window, int Width, int Height);

	void InformBindTexture(class euiTexture* Texture, uint Slot);
	int GetFirstUnboundTextureSlot();

	const glm::mat4 CreateMVPMatrix(const euiEntity* Entity) const;

	GLFWwindow* GetWindow() {return Window;}
	int GetWindowWidth() const {return WindowWidth;}
	int GetWindowHeight() const {return WindowHeight;}
	std::map<uint, class euiTexture*> GetTextureBindingInfo() {return TextureBindingInfo;}

private:

	GLFWwindow* Window;
	int WindowWidth;
	int WindowHeight;
	glm::vec4 BackgroundColor;

	glm::mat4 ProjectionMatrix;
	std::map<uint, class euiTexture*> TextureBindingInfo;

	std::vector<class euiEntity*> RenderQueue;

	void Loop();
};

