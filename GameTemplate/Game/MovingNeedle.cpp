#include "stdafx.h"
#include "Config.h"
#include "MovingNeedle.h"
#include "Player.h"
#include "GameOver.h"
#include "Fade.h"

namespace
{
	const Vector3 NEEDLE_SCALE(5.0f, 5.0f, 10.0f);// オブジェクトの大きさ。
    const Vector3 COLLISION_HEIGHT(50.0f, 50.0f, 0.0f);// コリジョンの高さ。
    const Vector3 COLLISION_SIZE(365.0f, 5.0f, 225.0f);// コリジョンの大きさ。
}

MovingNeedle::MovingNeedle()
{
	

}
MovingNeedle::~MovingNeedle()
{

}
bool MovingNeedle::Start()
{
	m_modelRender.Init("Assets/modelData/MovingNeedele/MovingNeedle.tkm");


	m_modelRender.SetScale(NEEDLE_SCALE);
	m_modelRender.Update();
	m_player = FindGO<Player>("player");

	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");


	//コリジョンを動く床に設置。
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
void MovingNeedle::Update()
{
	DisplayModel();
	m_modelRender.Update();
	m_collisionObject->SetPosition(m_needlePosition + COLLISION_HEIGHT);
}

// モデルを破棄する。
void MovingNeedle::DisplayModel()
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

// 描画処理。
void MovingNeedle::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}    