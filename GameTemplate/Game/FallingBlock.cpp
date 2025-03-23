#include "stdafx.h"
#include "FallingBlock.h"

namespace
{
	Vector3 FALLINGBLOCK_SCALE = Vector3(5.0f, 10.0f, 3.0f);
}

FallingBlock::FallingBlock()
{
	m_modelRender.Init("Assets/modelData/Stage/Assets/ë´èÍÉuÉçÉbÉN.tkm");
	
}

FallingBlock::~FallingBlock()
{

}

bool FallingBlock::Start()
{
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

void FallingBlock::Move()
{
	if (charactercontroller.IsOnGround())
	{
		f_position.y -= 10.0f;
	}

	
}

void FallingBlock::Update()
{
	Move();
	m_modelRender.SetPosition(f_position);
	m_modelRender.SetScale(FALLINGBLOCK_SCALE);
	m_modelRender.Update();
}

void FallingBlock::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}