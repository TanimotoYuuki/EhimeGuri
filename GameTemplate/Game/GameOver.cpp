#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Title.h"

GameOver::GameOver()
{
	InitSprite();
	m_player = FindGO<Player>("player");
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	m_player->m_gameoverFlag = true;
	//if (g_pad[0]->IsPress(enButtonA))
	//{
	//	NewGO<Title>(0);
	//	DeleteGO(this);
	//}
}

void GameOver::Render(RenderContext& rc)
{
	//ゲームオーバーUI
	m_gameOver.Draw(rc);

	//コンティニューUI
	m_continue.Draw(rc);

	//タイトルへ戻るUI
	m_returnTitle.Draw(rc);

	//AボタンUI
	m_aButton.Draw(rc);

	//決定UI
	m_decision.Draw(rc);
}

void GameOver::InitSprite()
{
	//ゲームオーバーUI
	m_gameOver.Init("Assets/gameover/text/gameover.dds", 1024, 128);
	m_gameOver.SetPosition(m_gameOverPosition);
	m_gameOver.Update();

	//コンティニューUI
	m_continue.Init("Assets/gameover/text/continue.dds", 1024, 128);
	m_continue.SetPosition(Vector3(-200.0f, -200.0f, 0.0f));
	m_continue.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_continue.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_continue.Update();

	//タイトルへ戻るUI
	m_returnTitle.Init("Assets/gameover/text/returntitle.dds", 1024, 128);
	m_returnTitle.SetPosition(Vector3(200.0f, -200.0f, 0.0f));
	m_returnTitle.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_returnTitle.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_returnTitle.Update();

	//AボタンUI
	m_aButton.Init("Assets/gameover/gamepad/abutton.dds", 512, 512);
	m_aButton.SetPosition(Vector3(Vector3(525.0f, -345.0f, 0.0f)));
	m_aButton.SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_aButton.Update();

	//決定UI
	m_decision.Init("Assets/gameover/text/decision.dds", 1024, 128);
	m_decision.SetPosition(Vector3(600.0f, -345.0f, 0.0f));
	m_decision.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	m_decision.Update();
}