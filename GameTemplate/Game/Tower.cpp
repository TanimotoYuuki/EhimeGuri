#include "stdafx.h"
#include "Tower.h"
#include "Config.h"

bool Tower::Start()
{

	m_modelRender.Init("Assets/modelData/Tower/Tower.tkm");


	m_modelRender.Update();
	return true;
}

void Tower::Update()
{
	m_modelRender.Update();
}

void Tower::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}