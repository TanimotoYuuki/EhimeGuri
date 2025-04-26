#include "stdafx.h"
#include "StageClear.h"
#include "ClearPoint.h"
#include "Player.h" 

namespace
{
	Vector3 SCALE = Vector3(5.0f, 5.0f, 5.0f);
}

ClearPoint::ClearPoint()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/GoalPole.tkm");
	m_player = FindGO<Player>("player");
}

ClearPoint::~ClearPoint()
{
	

}

void ClearPoint::Update()
{
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(position);
	m_modelRender.Update();

	Vector3 diff;
	diff.x = position.x - m_player->m_position.x;
	if (diff.Length() < 20.0f)
	{
		NewGO<StageClear>(0);
		DeleteGO(this);
	}
	
}

void ClearPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}