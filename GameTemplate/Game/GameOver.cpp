#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Title.h"

GameOver::GameOver()
{
	m_spriteRender.Init("Assets/Sprite/GameOver.DDS", 1920.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//タイトル画面を表示する
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}