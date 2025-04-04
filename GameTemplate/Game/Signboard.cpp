#include "stdafx.h"
#include "Signboard.h"

namespace
{
	Vector3 SCALE = Vector3(3.0f, 3.0f, 3.0f);
}

Signboard::Signboard()
{

}
Signboard::~Signboard()
{

}

bool Signboard::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/ŠÅ”Â.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_Rot.AddRotationDegY(365.0f);
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_Rot);
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_modelRender.Update();
	return true;
}

void Signboard::Update()
{
	
}

void Signboard::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}