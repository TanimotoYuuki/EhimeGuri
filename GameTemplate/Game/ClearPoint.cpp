#include "stdafx.h"
#include "StageClear.h"
#include "ClearPoint.h"
#include "Player.h" 

namespace
{
	Vector3 SCALE = Vector3(10.0f, 10.0f, 10.0f);
}

ClearPoint::ClearPoint()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/íÜêj.tkm");
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

	Vector3 diff = m_player->m_position - position;
	if (diff.Length() < 50.0f)
	{
		m_player->clearCount += 1;
		DeleteGO(this);
	}
	
}

void ClearPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}