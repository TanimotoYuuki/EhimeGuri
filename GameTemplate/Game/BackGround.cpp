#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{

}

BackGround ::~BackGround()
{

}

bool BackGround::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/Stage1.tkm");
	m_scale = { 10.0f,10.0f,10.0f };
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),m_modelRender.GetModel().GetWorldMatrix());
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void BackGround::Update()
{
	m_modelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}