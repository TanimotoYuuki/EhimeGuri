#include "stdafx.h"
#include "Towel.h"

namespace
{
	Vector3 SCALE = Vector3{ 3.0f,2.0f,3.0f };
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

void Towel::Update()
{
	m_modelRender.SetScale(SCALE);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Towel::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}