#include "stdafx.h"
#include "Needle.h"
#include "Player.h"

Needle::Needle()
{
	//Needleモデルのファイルパス
	m_modelRender.Init("Assets/modelData/Stage/Asssets/針.tkm");
}
Needle::~Needle()
{
	
}

void Needle::Update()
{
	m_modelRender.SetPosition(m_needlePosition);
	m_modelRender.Update();

	//NeedleとPlayerの距離を計算する
	Vector3 diff = m_player->m_position - m_needlePosition;

	//PlayerとNeedleの距離が100以下なら
	if (diff.Length() <= 100.0f)
	{
		//カウントを1にする(GameOver)
		m_player->m_needleCount = 1;
		//Needleモデルの削除
		DeleteGO(this);
	}
}

void Needle::Render(RenderContext& rc)
{
	//Needleモデルの描画
	m_modelRender.Draw(rc);
}