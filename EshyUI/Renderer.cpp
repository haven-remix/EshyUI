
#include <GL/glew.h>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Entity.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <algorithm>
#include <ranges>
#include <thread>

static euiRenderer* renderer = nullptr;

void euiRenderer::InitRenderer(GLFWwindow* Window)
{
	assert(!renderer);
	renderer = new euiRenderer(Window);
}

euiRenderer* euiRenderer::GetRenderer()
{
	assert(renderer);
	return renderer;
}


static void OnScreenSizeChangedCallback(GLFWwindow* window, int Width, int Height)
{
	renderer->OnScreenSizeChanged(window, Width, Height);
}


euiRenderer::euiRenderer(GLFWwindow* _Window)
	: Window(_Window)
{
	int Width;
	int Height;
	glfwGetWindowSize(_Window, &Width, &Height);
	UpdateScreenSize(Width, Height);

	glfwSetFramebufferSizeCallback(Window, OnScreenSizeChangedCallback);
}

void euiRenderer::BeginLoop()
{
	glfwMakeContextCurrent(Window);

	while (!glfwWindowShouldClose(Window))
		Loop();
}

void euiRenderer::Loop()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);

	double PointerXPos;
	double PointerYPos;
	glfwGetCursorPos(Window, &PointerXPos, &PointerYPos);
	PointerYPos = GetWindowHeight() - PointerYPos;

	const int bLeftButtonPressedState = glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT);

	for (euiEntity* EntityToRender : RenderQueue)
	{
		EntityToRender->CheckPointerStatus(PointerXPos, PointerYPos, bLeftButtonPressedState);
		EntityToRender->Draw(this);
	}

	glfwSwapBuffers(Window);
	glfwPollEvents();
}


const glm::mat4 euiRenderer::CreateMVPMatrix(const euiEntity* Entity) const
{
	return ProjectionMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(Entity->GetX(), Entity->GetY(), 0.0f));
}

void euiRenderer::AddToRenderQueue(euiEntity* Entity)
{
	RenderQueue.push_back(Entity);
}

void euiRenderer::RemoveFromRenderQueue(euiEntity* Entity)
{
	if (auto it = std::ranges::find(RenderQueue, Entity); it != RenderQueue.end())
		RenderQueue.erase(it);
}

void euiRenderer::Draw(euiEntity* Entity)
{
	glDrawElements(GL_TRIANGLES, Entity->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}


void euiRenderer::UpdateScreenSize(int Width, int Height)
{
	WindowWidth = Width;
	WindowHeight = Height;
	ProjectionMatrix = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, -1.0f, 1.0f);
	glfwSetWindowSize(Window, Width, Height);
	glViewport(0, 0, Width, Height);
}

void euiRenderer::OnScreenSizeChanged(GLFWwindow* window, int Width, int Height)
{
	UpdateScreenSize(Width, Height);
	Loop();
}

void euiRenderer::InformBindTexture(euiTexture* Texture, uint Slot)
{
	TextureBindingInfo.emplace(Slot, Texture);
}

int euiRenderer::GetFirstUnboundTextureSlot()
{
	int MaxTextureSlots;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextureSlots);

	if (TextureBindingInfo.size() > 0)
	{
		uint first = TextureBindingInfo.begin()->first;

		if (first > 0)
			return first - 1;
		else
		{
			uint last = TextureBindingInfo.rbegin()->first;

			if (last < (uint)MaxTextureSlots - 1)
				return last + 1;
		}
	}
	else
		return 0;

	return -1;
}
