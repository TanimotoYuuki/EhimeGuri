#include "stdafx.h"
#include "Needle.h"
#include "Player.h"
#include "GameOver.h"
#include "Fade.h"

namespace
{
	Vector3	NEEDLE_SCALE = Vector3(5.0f, 5.0f, 10.0f);// オブジェクトの大きさ。
	Vector3 COLLISION_HEIGHT = Vector3(50.0f, 50.0f, 0.0f);// コリジョンの高さ。
	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);// コリジョンの大きさ。
}

Needle::Needle()
{
	

}
Needle::~Needle()
{

}
bool Needle::Start()
{
	//モデルのファイルパス
	m_modelRender.Init("Assets/modelData/Stage/Assets/Needle.tkm");
	m_modelRender.SetScale(NEEDLE_SCALE);
	m_modelRender.Update();
	m_player = FindGO<Player>("player");

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	//コリジョンを動く床に設置
	m_collisionObject->CreateBox
	(
		m_needlePosition + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_modelRender.SetPosition(m_needlePosition);

	m_collisionObject->SetIsEnableAutoDelete(false);
	firstposition = m_needlePosition;
	
	m_fade = FindGO<Fade>("fade");
	return true;
}

// 更新作業。
void Needle::Update()
{
	DisplayModel();
	m_modelRender.Update();
	m_collisionObject->SetPosition(m_needlePosition + COLLISION_HEIGHT);
}


void Needle::DisplayModel()
{
	Vector3 diff = m_player->m_position - m_needlePosition;
	if (diff.Length() <= 50.0f)
	{
		if (m_gameOverFlag != true)
		{
			flag == false;
			m_gameOver = NewGO<GameOver>(0, "gameover");
			DeleteGO(m_fade);
			m_gameOverFlag = true;
		}
	}
}

void Needle::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}    