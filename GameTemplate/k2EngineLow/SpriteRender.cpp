#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"

namespace nsK2EngineLow
{
	void SpriteRender::Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData spriteInitData;
		spriteInitData.m_ddsFilePath[0] = filePath;
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_width = w;
		spriteInitData.m_height = h;
		spriteInitData.m_alphaBlendMode = alphaBlendMode;
		m_sprite.Init(spriteInitData);
	}

	void SpriteRender::Update()
	{
		m_sprite.Update(m_position, m_rotation, m_scale);
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		m_sprite.Draw(rc);
	}
}