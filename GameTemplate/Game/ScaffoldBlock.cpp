#include "stdafx.h"
#include "ScaffoldBlock.h"

namespace
{
	Vector3 SCALE = Vector3(10.0f, 10.0f, 10.0f);

}


ScaffoldBlock::ScaffoldBlock()
{

}

ScaffoldBlock::~ScaffoldBlock()
{

}

bool ScaffoldBlock::Start()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/キノコの足場ブロック.tkm");
	
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_modelRender.Update();
	return true;
}

void ScaffoldBlock::Update()
{
	m_Rot.SetRotationDegY(90.0f);
	m_modelRender.SetRotation(m_Rot);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
}

void ScaffoldBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}