#include "k2EngineLowPreCompile.h"
#include "BackGroundRender.h"

namespace nsK2EngineLow
{
	void BackGroundRender::Init(const char* filePath)
	{
		SpriteInitData spriteInitData;
		spriteInitData.m_ddsFilePath[0] = filePath;
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_width = FRAME_BUFFER_W;
		spriteInitData.m_height = FRAME_BUFFER_H;

		spriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
		m_sprite.Init(spriteInitData);
	}

	void BackGroundRender::Update()
	{
		m_sprite.Update(Vector3::Zero, Quaternion::Identity, Vector3::One, Sprite::DEFAULT_PIVOT);
	}

	void BackGroundRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}
}