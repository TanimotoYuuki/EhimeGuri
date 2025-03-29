#pragma once
class Player;
class Title;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	void Update();
	void Render(RenderContext& rc);
	int NeedleCount = 0;
	ModelRender	 m_modelRender;
	SpriteRender m_spriteRender;
	Vector3	     m_position;
	GameOver   * m_gameOver;
	Player	   * m_player;
};

