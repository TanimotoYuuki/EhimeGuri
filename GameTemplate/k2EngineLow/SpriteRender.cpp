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

		spriteInitData.m_expandConstantBuffer = &GetSpriteRenderConstantBuffer();
		spriteInitData.m_expandConstantBufferSize = sizeof(GetSpriteRenderConstantBuffer());

		spriteInitData.m_alphaBlendMode = alphaBlendMode;
		m_sprite.Init(spriteInitData);
	}

	void SpriteRender::Update()
	{
		//リニアワイプの描画モードでLinearWipeDrawingMode_None以外選択されていたら
		if (m_spriteRenderConstantBuffer.linearWipeDrawingMode != LinearWipeDrawingMode_None)
		{
			LinearWipeUpdate();
		}

		//画像加工の描画モードでScreenDrawingMode_None以外選択されていたら
		if (m_spriteRenderConstantBuffer.screenDrawingMode != ScreenDrawingMode_None)
		{
			ScreenDrawingUpdate();
		}

		m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		//m_sprite.Draw(rc);
		g_renderingEngine->AddRenderObject(this);
	}
}