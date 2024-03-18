
#include "EshyUI.h"
#include "Renderer.h"
#include "Entity.h"

#include <vector>

static float StartingLocationX = 5.0f;
static float StartingLocationY = 5.0f;
static float BackgroundWidth = 40.0f;
static float BackgroundHeight = 40.0f;
static float ImageWidth = 30.0f;
static float ImageHeight = 30.0f;
static float Padding = 5.0f;
static float InternalPadding = 10.0f;

struct Icon
{
	euiSolidEntity* Background;
	euiImageEntity* Image;
};

static void NotifyPointerEnter(euiEntity* Entity)
{

}

static void NotifyPointerExit(euiEntity* Entity)
{

}

static void NotifyPointerPressed(euiEntity* Entity)
{

}

static void NotifyPointerUnpressed(euiEntity* Entity)
{

}

static Icon AddIcon(int Index, const std::string& ImagePath)
{
	euiSolidEntity* Background = new euiSolidEntity(StartingLocationX + (BackgroundWidth * Index) + (Padding * Index), StartingLocationY, BackgroundWidth, BackgroundHeight, EUI_ANCHOR_LEFT_BOTTOM);
	euiImageEntity* Image = new euiImageEntity(StartingLocationX + (BackgroundWidth * Index) + (Padding * Index) + (InternalPadding / 2), StartingLocationY + (InternalPadding / 2.0f), ImageWidth, ImageHeight, EUI_ANCHOR_LEFT_BOTTOM, ImagePath);

	Background->SetNormalColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	Background->SetHoveredColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Background->SetPressedColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));

	Background->NotifyPointerEnterCallback = &NotifyPointerEnter;
	Background->NotifyPointerExitCallback = &NotifyPointerExit;
	Background->NotifyPointerPressedCallback = &NotifyPointerPressed;
	Background->NotifyPointerUnpressedCallback = &NotifyPointerUnpressed;

	return { Background, Image };
}


int main()
{
	GLFWwindow* window = InitEshyUI("Sandbox", 1024, 720.0f, false);
	euiRenderer::InitRenderer(window);

	std::vector<Icon> Icons;
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image1.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image2.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image3.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image4.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image5.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image1.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image2.png"));
	Icons.push_back(AddIcon((int)Icons.size(), "./Resources/image3.png"));

	euiRenderer::GetRenderer()->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	euiRenderer::GetRenderer()->BeginLoop();

	Shutdown();
	return 0;
}