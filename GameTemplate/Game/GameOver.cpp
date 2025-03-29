#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Title.h"

GameOver::GameOver()
{
	m_spriteRender.Init("Assets/Sprite/GameOver.DDS", 1920, 1080);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsPress(enButtonA))
	{
		NewGO<Title>(0);
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}