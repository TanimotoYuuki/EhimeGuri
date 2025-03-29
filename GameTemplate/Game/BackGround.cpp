#include "stdafx.h"
#include "BackGround.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(10.0f, 10.0f, 10.0f);
}

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	m_backGroundRender.Init("Assets/modelData/Stage/Assets/Stage1.tkm");
	m_backGroundRender.SetScale(BACKGROUND_SCALE);
	m_backGroundRender.Update();
	//ìñÇΩÇËîªíËÇçÏê¨
	m_physicsSraricObject.CreateFromModel(m_backGroundRender.GetModel(), m_backGroundRender.GetModel().GetWorldMatrix());
	return true;
}

void BackGround::Update()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_backGroundRender.Draw(rc);
}