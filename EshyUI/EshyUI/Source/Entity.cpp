
#include "Entity.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

euiEntity::euiEntity(float _x, float _y, float _Width, float _Height)
	: x(_x)
	, y(_y)
	, Width(_Width)
	, Height(_Height)
	, VertexArray(nullptr)
	, VertexBuffer(nullptr)
	, IndexBuffer(nullptr)
	, Layout(nullptr)
	, Shader(nullptr)
{}

void euiEntity::Draw(euiRenderer& Renderer)
{
	//Renderer.Draw(this);
	Renderer.Draw(*VertexArray, *IndexBuffer, *Shader);
}

void euiEntity::SetPosition(float NewX, float NewY)
{
	x = NewX;
	y = NewY;
}

void euiEntity::SetSize(float NewWidth, float NewHeight)
{
	Width = NewWidth;
	Height = NewHeight;
}


euiSolidEntity::euiSolidEntity(float _x, float _y, float _Width, float _Height, const glm::vec4& _Color)
	: euiEntity(_x, _y, _Width, _Height)
	, Color(_Color)
{
	float positions[] = {
		 _x,		  _y,			//Bottom left
		 _x + _Width, _y,			//Bottom right
		 _x + _Width, _y + _Height, //Top right
		 _x,		  _y + _Height, //Top left
	};

	uint indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer = new euiVertexBuffer(positions, 4 * 2 * sizeof(float));

	Layout = new euiVertexBufferLayout();
	Layout->push<float>(2);

	VertexArray = new euiVertexArray();
	VertexArray->AddBuffer(*VertexBuffer, *Layout);

	IndexBuffer = new euiIndexBuffer(indicies, 6);
	IndexBuffer->InitializeIndexBuffer(indicies, 6);

	Shader = new euiShader("Resources\\solid.vshader", "Resources\\solid.fshader");
	Shader->Bind();
	Shader->SetUniform4f("u_color", _Color.r, _Color.g, _Color.b, _Color.a);

	VertexArray->Unbind();
	Shader->Unbind();
	VertexBuffer->Unbind();
	IndexBuffer->Unbind();
}

void euiSolidEntity::SetColor(const glm::vec4& _Color)
{
	Color = _Color;
}

void euiSolidEntity::SetColor(float r, float g, float b, float a)
{
	Color = glm::vec4(r, g, b, a);
}


euiImageEntity::euiImageEntity(float _x, float _y, float _Width, float _Height, euiRenderer* Renderer, const std::string& ImagePath)
	: euiEntity(_x, _y, _Width, _Height)
	, Texture(nullptr)
{
	float positions[] = {
		 _x,		  _y,			0.0f, 0.0f,   //Bottom left
		 _x + _Width, _y,			1.0f, 0.0f,   //Bottom right
		 _x + _Width, _y + _Height, 1.0f, 1.0f,   //Top right
		 _x,		  _y + _Height, 0.0f, 1.0f    //Top left
	};

	uint indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer = new euiVertexBuffer(positions, 4 * 4 * sizeof(float));

	Layout = new euiVertexBufferLayout();
	Layout->push<float>(2);
	Layout->push<float>(2);

	VertexArray = new euiVertexArray();
	VertexArray->AddBuffer(*VertexBuffer, *Layout);

	IndexBuffer = new euiIndexBuffer(indicies, 6);
	IndexBuffer->InitializeIndexBuffer(indicies, 6);

	Shader = new euiShader("Resources\\image.vshader", "Resources\\image.fshader");
	Shader->Bind();

	Texture = new euiTexture(ImagePath);
	Texture->Bind(Renderer);
	Shader->SetUniform1i("u_texture", Texture->GetSlot());

	VertexArray->Unbind();
	Shader->Unbind();
	VertexBuffer->Unbind();
	IndexBuffer->Unbind();
}

void euiImageEntity::Draw(class euiRenderer& Renderer)
{
	Renderer.Draw(this, Texture);
}