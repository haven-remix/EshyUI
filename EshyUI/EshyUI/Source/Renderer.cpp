
#include <GL/glew.h>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Entity.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

euiRenderer::euiRenderer(GLFWwindow* _Window)
	: Window(_Window)
{
	int Width;
	int Height;
	glfwGetWindowSize(_Window, &Width, &Height);

	UpdateScreenSize((float)Width, (float)Height);
}

void euiRenderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void euiRenderer::Draw(const euiVertexArray& va, const euiIndexBuffer& ib, euiShader& shader)
{
	shader.Bind();
	shader.SetUniformMat4f("u_mvp", GetProjectionMatrix());
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void euiRenderer::Draw(euiEntity* Entity, euiTexture* Texture)
{
	Entity->GetShader()->Bind();
	Entity->GetShader()->SetUniformMat4f("u_mvp", GetProjectionMatrix());
	Entity->GetVertexArray()->Bind();
	Entity->GetIndexBuffer()->Bind();

	if (Texture)
	{
		int Slot = Texture->Bind(this);
		Entity->GetShader()->SetUniform1i("u_texture", Slot);
	}

	glDrawElements(GL_TRIANGLES, Entity->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void euiRenderer::UpdateScreenSize(float Width, float Height)
{
	ProjectionMatrix = glm::ortho(0.0f, Width, 0.0f, Height, -1.0f, 1.0f);
	glfwSetWindowSize(Window, (int)Width, (int)Height);
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

			if (last < MaxTextureSlots - 1)
				return last + 1;
		}
	}
	else
		return 0;

	return -1;
}
