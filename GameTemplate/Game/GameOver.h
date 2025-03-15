#pragma once
class Player;
class Title;
class GameOver : public IGameObject
{
	GameOver();
	~GameOver();

	void Update();
	void Render(RenderContext& rc);

	ModelRender	 m_modelRender;
	SpriteRender m_spriteRender;
	Vector3	     m_position;
	Player	   * m_player;
};

