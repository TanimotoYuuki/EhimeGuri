#include "stdafx.h"
#include "Block.h"
#include "BackGround.h"
#include "ClearPoint.h"
#include "Enemy.h"
#include "FallingBlock.h"
#include "Game.h"
#include "GameOver.h"
#include "GameCamera.h"
#include "HS_FallingBlock.h"
#include "Needle.h"
#include "MovingFloor.h"
#include "Player.h"
#include "Scaffold.h"
#include "ScaffoldBlock.h"
#include "StageClear.h"
#include "S_MovingFloor.h"
#include "TransparentBlock.h"
#include "Title.h"
#include "Towel.h"
#include "Fade.h"

namespace
{
	Vector3 TRANSPARENTBLOCK_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	Vector3	NEEDLE_SCALE = Vector3(10.0f, 10.0f, 10.0f);
	const int ENEMY_NUM = 5;
}

//�w�i
////�w�i�̊֐�
//void Game::InitSky()
//{
//	DeleteGO(m_SkyCube);
//	SkyCube* m_SkyCube = NewGO<SkyCube>(0, "skycube");
//	m_SkyCube->SetType(enSkyCubeType_NightToon);
//	m_SkyCube->SetLuminance(1.0f);
//	m_SkyCube->SetScale(100000.0f);
//
//
//	// �����̌v�Z�̂��߂�IBL�e�N�X�`����Z�b�g����B
//	g_renderingEngine->SetAmbientByIBLTexture(m_SkyCube->GetTextureFilePath(), 1.0f);
//	// �������̉e����������₷���悤�ɁA�f�B���N�V�������C�g�̓I�t�ɁB
//	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
//}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	for (int i = 0; i < ENEMY_NUM; i++) {
		DeleteGO(m_enemyList[i]);
	}
	DeleteGO(m_transparentBlock);
	DeleteGO(m_transparentBlock1);
	DeleteGO(m_transparentBlock2);
	DeleteGO(m_transparentBlock3);
	DeleteGO(m_transparentBlock4);
	DeleteGO(m_transparentBlock5);
	DeleteGO(m_transparentBlock6);
	DeleteGO(m_transparentBlock7);
	DeleteGO(m_transparentBlock8);
	DeleteGO(m_transparentBlock9);
	DeleteGO(m_transparentBlock10);
	DeleteGO(m_transparentBlock11);
	DeleteGO(m_fallingBlock);
	DeleteGO(m_fallingBlock1);
	DeleteGO(m_fallingBlock2);
	DeleteGO(m_scaffoldBlock);
	DeleteGO(m_needle);
	DeleteGO(m_needle1);
	DeleteGO(m_movingFloor1);
	DeleteGO(m_movingFloor2);
	DeleteGO(m_block);
	DeleteGO(m_scaffold);
	DeleteGO(m_scaffold1);
	DeleteGO(m_towel);
	DeleteGO(m_clearPoint);
}

bool Game::Start()
{
	m_backGround =  NewGO<BackGround>(1, "background");
	m_backGroundRender.Init("Assets/modelData/Stage/Assets/Stage1.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();
	//�����蔻���쐬
	m_physicsStaticObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());
	//�X�e�[�W�Ƀ��C�p�̑�����^����B
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Stage1);


	m_player     =  NewGO<Player>(1, "player");
	m_gameCamera =  NewGO<GameCamera>(2, "gamecamera");
	m_gameCamera->SetTarget(m_player);

	Vector3 enemyPosList[ENEMY_NUM] = {
		{3200.0f,94.0f,0.0f},
		{600.0f,94.0f,0.0f},
		{4800.0f,94.0f,0.0f},
		{5400.0f,94.0f,0.0f},
		{12300.0f,200.0f,0.0f}
	};

	for (int i = 0; i < ENEMY_NUM; i++) {
		m_enemyList[i] = NewGO<Enemy>(0, "enemy");
		m_enemyList[i]->m_position = enemyPosList[i];
		m_enemyList[i]->firstposition = enemyPosList[i];
	}

	m_mappuRender.Init("Assets/modelData/mappu.DDS", 350.0f, 40.0f);
	m_mappuRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	m_gennzaitiRender.Init("Assets/modelData/gennzaiti.DDS", 50.0f, 50.0f);
	m_gennzaitiRender.SetPosition(Vector3(260.0f, 430.0f, 0.0f));

	m_sutaminaMaxrender.Init("Assets/modelData/sutaminamax.DDS", 350.0f, 40.0f);
	m_sutaminaMaxrender.SetPosition(Vector3(-175.0f, 300.0f, 0.0f));
	m_sutaminaMaxrender.SetPivot(Vector2(0.0f, 0.5f));
	m_sutamina0render.Init("Assets/modelData/sutamina0.DDS", 350.0f, 40.0f);
	m_sutamina0render.SetPosition(Vector3(0.0f, 300.0f, 0.0f));

	m_taorukuroRender.Init("Assets/modelData/taorukuro.DDS", 100.0f, 100.0f);
	m_taorukuroRender.SetPosition(Vector3(-750.0f, 400.0f, 0.0f));
	m_taorutoriRender.Init("Assets/modelData/taorutori.DDS", 100.0f, 100.0f);
	m_taorutoriRender.SetPosition(Vector3(-750.0f, 400.0f, 0.0f));

	TransparentBlock_NewGO();
	FallingBlock_NewGO();
	ScaffoldBlock_NewGO();
	Needle_NewGO();
	MovingFloor_NewGO();
	Block_NewGO();
	//Signboard_NewGO();
	Scaffold_NewGO();
	Item_NewGO();
	ClearPoint_NewGO();
	HS_fallingBlock_NewGO();
	S_MovingFloor_NewGO();
	Fade_NewGO();

	m_modelRender.Update();
//	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}


//�����u���b�N
void Game::TransparentBlock_NewGO()
{
	//㩗p�̍��W
	m_transparentBlock3 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock3->m_position = { 4700.0f, 270.0f, 0.0f };
	m_transparentBlock3->m_firstposition = m_transparentBlock3->m_position;

	m_transparentBlock4 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock4->m_position = { 4800.0f, 270.0f, 0.0f };
	m_transparentBlock4->m_firstposition = m_transparentBlock4->m_position;

	m_transparentBlock5 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock5->m_position = { 4900.0f, 270.0f, 0.0f };
	m_transparentBlock5->m_firstposition = m_transparentBlock5->m_position;

	m_transparentBlock6 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock6->m_position = { 5000.0f, 270.0f, 0.0f };
	m_transparentBlock6->m_firstposition = m_transparentBlock6->m_position;

	m_transparentBlock7 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock7->m_position = { 5100.0f, 270.0f, 0.0f };
	m_transparentBlock7->m_firstposition = m_transparentBlock7->m_position;

	m_transparentBlock8 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock8->m_position = { 5200.0f, 270.0f, 0.0f };
	m_transparentBlock8->m_firstposition = m_transparentBlock8->m_position;

	m_transparentBlock9 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock9->m_position = { 5300.0f, 270.0f, 0.0f };
	m_transparentBlock9->m_firstposition = m_transparentBlock9->m_position;

	//�ړ��p
	/*m_transparentBlock10 = NewGO<TransparentBlock>(1, "transparentblock");
	m_transparentBlock10->m_position = { 10300.0f, 200.0f, 0.0f };
	m_transparentBlock10->m_firstposition = m_transparentBlock10->m_position;*/

	m_modelRender.SetPosition(m_position);
}

//�����鏰
void Game::FallingBlock_NewGO()
{
	m_fallingBlock = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock->m_position = { 7400.0f, 360.0f, 0.0f };
	m_fallingBlock->m_firstposition = m_fallingBlock->m_position;

	m_fallingBlock1 = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock1->m_position = { 8000.0f, 400.0f, 0.0f };
	m_fallingBlock1->m_firstposition = m_fallingBlock1->m_position;

	m_fallingBlock2 = NewGO<FallingBlock>(0, "fallingblock");
	m_fallingBlock2->m_position = { 8600.0f, 400.0f, 0.0f };
	m_fallingBlock2->m_firstposition = m_fallingBlock2->m_position;

	m_modelRender.SetPosition(m_position);
}

//T�^����u���b�N
void Game::ScaffoldBlock_NewGO()
{
	m_scaffoldBlock = NewGO<ScaffoldBlock>(0, "scaffoldblock");
	m_scaffoldBlock->m_position = { 6650.0f, 125.0f, 0.0f };
	m_scaffoldBlock->m_firstposition = m_scaffoldBlock->m_position;
	m_modelRender.SetPosition(m_position);
}

//�j
void Game::Needle_NewGO()
{
	m_needle1 = NewGO<Needle>(0, "needle");
	m_needle1->m_needlePosition = { 15800.0f, 400.0f, 0.0f };
	m_needle1->firstposition = m_needle1->m_needlePosition;

	m_modelRender.SetPosition(m_position);
}

//������(�ʏ푬�x)
void Game::MovingFloor_NewGO()
{
	
	m_movingFloor1 = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor1->SetPosition(Vector3{ 11000.0f, 180.0f, 200.0f });

	m_movingFloor2 = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor2->SetPosition(Vector3{ 12000.0f, 200.0f, 200.0f });

	m_modelRender.SetPosition(m_position);
}

//�u���b�N
void Game::Block_NewGO()
{
	/*m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 11000.0f, 900.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;*/


	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 1000.0f, 300.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;

	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 12300.0f, 300.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;

	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 14000.0f, 600.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;

	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 15000.0f, 600.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;

	m_block = NewGO<Block>(0, "block");
	m_block->m_position = { 3200.0f, 300.0f, 0.0f };
	m_block->m_firstposition = m_block->m_position;
	m_modelRender.SetPosition(m_position);

}

//����u���b�N
void Game::Scaffold_NewGO()
{
	//x �c 13300	
	m_scaffold1 = NewGO<Scaffold>(0, "scaffold");
	m_scaffold1->m_position = { 12950.0f, 200.0f, 200.0f };
	m_scaffold1->m_firstposition = m_scaffold1->m_position;
	m_modelRender.SetPosition(m_position);
}

//�A�C�e��
void Game::Item_NewGO()
{
   m_towel = NewGO<Towel>(0,"towel");
   m_towel->m_position = { 10500.0f, 250.0f, 0.0f };
   m_modelRender.SetPosition(m_position);
}

//�N���A�|�C���g
void Game::ClearPoint_NewGO()
{
	m_clearPoint = NewGO<ClearPoint>(0, "clearpoint");
	m_clearPoint->position = { 17500.0f, 700.0f, 0.0f };
	m_modelRender.SetPosition(m_position);
}

//������(�x)
void Game::S_MovingFloor_NewGO()
{
	m_s_MovingFloor = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor->m_position = { 13700.0f, 100.0f, 200.0f };
	m_s_MovingFloor->m_firstPosition = m_s_MovingFloor->m_position;

	m_s_MovingFloor = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor->m_position = { 14300.0f, 200.0f, 200.0f };

	m_s_MovingFloor3 = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor3->m_position = { 14900.0f, 200.0f, 200.0f };

	m_s_MovingFloor4 = NewGO<S_MovingFloor>(0, "s_movingfloor");
	m_s_MovingFloor4->m_position = { 15500.0f, 200.0f, 200.0f };

	m_modelRender.SetPosition(m_position);
}

//�����鏰(��)
void Game::HS_fallingBlock_NewGO()
{
	m_HS_FallingBlock = NewGO<HS_FallingBlock>(0, "hs_fallingblock");
	m_HS_FallingBlock->m_position = { 17500.0f,1000.0f, 200.0f };
	m_HS_FallingBlock->m_firstposition = m_HS_FallingBlock->m_position;
	m_modelRender.SetPosition(m_position);
}

void Game::Fade_NewGO()
{
	NewGO<Fade>(0, "fade");
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeTransition(enFadeState_FadeIn);
}

void Game::Update()
{
	////���l�m�F�p�B
	//wchar_t wcsbuf[256];
	//swprintf_s(wcsbuf, 256, L"�c�莞��%d�b", (int)(m_player->m_playernowsutamina));
	////�\������e�L�X�g��ݒ�B
	//m_fontRender.SetText(wcsbuf);
	////�t�H���g�̈ʒu��ݒ�B
	//m_fontRender.SetPosition(Vector3(-160.0f, 500.0f, 0.0f));
	////�t�H���g�̑傫����ݒ�B
	//m_fontRender.SetScale(1.2f);
	////�t�H���g�̐F��ݒ�B
	//m_fontRender.SetColor(g_vec4Yellow);  
	
	//�e�X�g�p
	//m_fontRender.SetText(L"�J�E���g�̏㏸");
	//m_fontRender.SetPosition(Vector3(-160.0f, 500.0f, 0.0f));
	//m_fontRender.SetScale(1.2f);
	//////�t�H���g�̐F��ݒ�B
	//m_fontRender.SetColor(g_vec4Yellow);

	//�j�ɓ������ăQ�[���I�[�o�[�ɂȂ����珈�����Ȃ�
	if (m_needle1->m_gameOverFlag == true)
	{
		return;
	}

	if (m_timer <= 0.0f) {
		if (m_gameOverFlag != true)
		{
			NewGO<GameOver>(0, "gameover");
			DeleteGO(m_fade);
			m_gameOverFlag = true;
		}
		return;
		//DeleteGO(this);
		//DeleteGO(m_player);
		//DeleteGO(m_backGround);;
		//DeleteGO(m_transparentBlock);
		//DeleteGO(m_transparentBlock1);
		//DeleteGO(m_transparentBlock2);
		//DeleteGO(m_transparentBlock3);
		//DeleteGO(m_transparentBlock4);
		//DeleteGO(m_transparentBlock5);
		//DeleteGO(m_transparentBlock6);
		//DeleteGO(m_transparentBlock7);
		//DeleteGO(m_transparentBlock8);
		//DeleteGO(m_transparentBlock9);
		//DeleteGO(m_transparentBlock10);
		//DeleteGO(m_transparentBlock11);
		//DeleteGO(m_fallingBlock);
		//DeleteGO(m_fallingBlock1);
		//DeleteGO(m_fallingBlock2);
		//DeleteGO(m_scaffoldBlock);
		//DeleteGO(m_needle);
		//DeleteGO(m_needle1);
		//DeleteGO(m_movingFloor1);
		//DeleteGO(m_movingFloor2);
		//DeleteGO(m_block);
		//DeleteGO(m_signboard);
		//DeleteGO(m_scaffold);
		//DeleteGO(m_scaffold1);
		//DeleteGO(m_towel);
		//for (int i = 0; i < ENEMY_NUM; i++) {
		//	DeleteGO(m_enemyList[i]);
		//}
		//m_player = nullptr;
		//m_movingFloor = nullptr;
		//m_fallingBlock = nullptr;
		//m_gameCamera->SetTarget(nullptr);
	}

	
	int MaxSuta = m_player->m_playermaxsutamina;
	int nowSuta = m_player->m_playernowsutamina;
	float nokori = (float)nowSuta / (float)MaxSuta;
	Vector3 heri = { 1.0f,1.0,1.0f };
	heri.x *= nokori;
	m_sutaminaMaxrender.SetScale(heri);

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"�c��%.1f�b", float(m_timer));
	m_timerRender.SetText(wcsbuf);
	m_timerRender.SetPosition(Vector3(0.0f, 500.0f, 0.0f));
	m_timerRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_timerRender.SetScale(1.0f);

	m_timer -= g_gameTime->GetFrameDeltaTime();

	m_sutaminaMaxrender.Update();
	m_sutamina0render.Update();

	m_mappuRender.Update();
	m_gennzaitiRender.Update();
	m_gennzaitiRender.SetPosition(Vector3(260.0f + m_player->m_position.x / 60, 430.0f, 0.0f));

	m_taorukuroRender.Update();
	m_taorutoriRender.Update();
	
}

void Game::Render(RenderContext& rc)
{
	
	//m_backGroundRender.Draw(rc);
	m_modelRender.Draw(rc);
	//�X�^�~�i���R�O�O�ȉ��̂Ƃ��ɃQ�[�W��o��
	if (m_player->m_gameoverFlag != true)
	{
		if (m_player->m_playernowsutamina < 300) {
			m_sutamina0render.Draw(rc);
			m_sutaminaMaxrender.Draw(rc);
		}
		m_fontRender.Draw(rc);
		m_timerRender.Draw(rc);
		m_mappuRender.Draw(rc);
		m_gennzaitiRender.Draw(rc);
		if (m_player->taoruCount == 0) {
			m_taorukuroRender.Draw(rc);
		}
		else if (m_player->taoruCount == 1) {
			m_taorutoriRender.Draw(rc);
		}
	}
}
