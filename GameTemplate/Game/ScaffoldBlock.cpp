#include "stdafx.h"
#include "ScaffoldBlock.h"

namespace
{
	Vector3 SCAFFOLDBLOOK_SCALE = Vector3(10.0f, 8.0f, 10.0f);
}

ScaffoldBlock::ScaffoldBlock()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/キノコの足場ブロック.tkm");
	
}

ScaffoldBlock::~ScaffoldBlock()
{

}

bool ScaffoldBlock::Start()
{
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

void ScaffoldBlock::Update()
{
	m_modelRender.Update();
	m_modelRender.SetScale(SCAFFOLDBLOOK_SCALE);
	m_modelRender.SetPosition(m_position);
	m_Rot.SetRotationDegY(90.0f);
	m_modelRender.SetRotation(m_Rot);


	
}

void ScaffoldBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}