#include "stdafx.h"
#include "Towel.h"

namespace
{
	Vector3 SCALE = Vector3{ 2.0f,2.0f,3.0f };
}

Towel::Towel()
{

}

Towel::~Towel()
{

}

bool Towel::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/ƒ^ƒIƒ‹.tkm");
	
	m_modelRender.Update();
	return true;
}

void Towel::Rotation()
{
	m_Rot.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(m_Rot);
}

void Towel::Update()
{
	Rotation();
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Towel::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}