#include "stdafx.h"
#include "Needle.h"
#include "Player.h"
#include "GameOver.h"

namespace
{
	Vector3	NEEDLE_SCALE = Vector3(5.0f, 5.0f, 10.0f);
	Vector3 COLLISION_HEIGHT = Vector3(50.0f, 50.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);
}

Needle::Needle()
{
	

}
Needle::~Needle()
{
	
}
bool Needle::Start()
{
	//Needleモデルのファイルパス
	m_modelRender.Init("Assets/modelData/Stage/Assets/針.tkm");
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

	return true;
}

void Needle::DisplayModel()
{
	Vector3 diff = m_player->m_position - m_needlePosition;
	if (diff.Length() <= 100.0f)
	{
		flag == false;
		m_gameOver = NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}
}

void Needle::Update()
{
	DisplayModel();
	m_modelRender.Update();
	m_collisionObject->SetPosition(m_needlePosition + COLLISION_HEIGHT);	
}

void Needle::Render(RenderContext& rc)
{
	if (flag == false)
	{
		m_modelRender.Draw(rc);
	}

//	m_modelRender.Draw(rc);
}    