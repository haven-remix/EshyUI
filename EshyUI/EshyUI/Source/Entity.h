
#pragma once

#include "glm/glm.hpp"

#include <string>

class euiEntity
{
public:

	euiEntity(float x, float y, float Width, float Height);

	virtual void Draw(class euiRenderer& Renderer);

	void SetPosition(float x, float y);
	void SetSize(float Width, float Height);

	class euiVertexArray* GetVertexArray() {return VertexArray;}
	class euiVertexBuffer* GetVertexBuffer() {return VertexBuffer;}
	class euiVertexBufferLayout* GetLayout() {return Layout;}
	class euiIndexBuffer* GetIndexBuffer() {return IndexBuffer;}
	class euiShader* GetShader() {return Shader;}

protected:

	float x;
	float y;
	float Width;
	float Height;

	class euiVertexArray* VertexArray;
	class euiVertexBuffer* VertexBuffer;
	class euiVertexBufferLayout* Layout;
	class euiIndexBuffer* IndexBuffer;
	class euiShader* Shader;
};

class euiSolidEntity : public euiEntity
{
public:

	euiSolidEntity(float x, float y, float Width, float Height, const glm::vec4& Color);

	void SetColor(const glm::vec4& Color);
	void SetColor(float r, float g, float b, float a);

private:

	glm::vec4 Color;
};

class euiImageEntity : public euiEntity
{
public:

	euiImageEntity(float x, float y, float Width, float Height, euiRenderer* Renderer, const std::string& ImagePath);

	virtual void Draw(class euiRenderer& Renderer) override;

private:

	class euiTexture* Texture;
};