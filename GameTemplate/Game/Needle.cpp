#include "stdafx.h"
#include "Needle.h"
#include "Player.h"

namespace
{
	Vector3	NEEDLE_SCALE = Vector3(5.0f, 5.0f, 5.0f);
}

Needle::Needle()
{
	//Needleモデルのファイルパス
	m_modelRender.Init("Assets/modelData/Stage/Assets/針.tkm");
	m_player = FindGO<Player>("player");

}
Needle::~Needle()
{
	
}

void Needle::Update()
{
	m_modelRender.SetPosition(m_needlePosition);
	m_modelRender.SetScale(NEEDLE_SCALE);
	m_modelRender.Update();
	
	Vector3 diff = m_player->m_position - m_needlePosition;
	if (diff.Length() <= 100.0f)
	{
		m_needleFlag = false;
		m_player->NeedleCount += 1;
		DeleteGO(this);
	}
}

void Needle::Render(RenderContext& rc)
{
	if (m_needleFlag == false)
	{
		//Needleモデルの描画
		m_modelRender.Draw(rc);
	}
	
}