#pragma once
#include "Game.h"

class Player;
class Game;
class GameOver;
class Title : public IGameObject
{
public:
	Title();
	~Title();

	void Update();
	void Render(RenderContext& rc);


private:
	SpriteRender  m_spriteRender;
	
};

