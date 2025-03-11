#pragma once

class BackGround : public IGameObject
{
	BackGround();
	~BackGround();

	bool Start();
	void Update();
	void Render(RenderContext & rc);
	
	ModelRender m_modelRender;


};

