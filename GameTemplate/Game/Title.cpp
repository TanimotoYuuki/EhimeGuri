#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	m_spriteRender.Init("Assets/Sprite/Title.DDS", 1920, 1080);
}

Title::~Title()
{

}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}