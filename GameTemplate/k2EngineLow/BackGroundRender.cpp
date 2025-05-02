#include "k2EngineLowPreCompile.h"
#include "BackGroundRender.h"

namespace nsK2EngineLow
{
	void BackGroundRender::Init(const char* filePath, const float w, const float h, bool isScroll)
	{
		SpriteInitData spriteInitData;
		spriteInitData.m_ddsFilePath[0] = filePath;
		spriteInitData.m_fxFilePath = "Assets/shader/backGround.fx";
		spriteInitData.m_width = w;
		spriteInitData.m_height = h;

		spriteInitData.m_expandConstantBuffer = &GetBackGroundRenderConstantBuffer();
		spriteInitData.m_expandConstantBufferSize = sizeof(GetBackGroundRenderConstantBuffer());

		spriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		m_backGroundConstantBuffer.scrollFlag = isScroll;
		if (m_backGroundConstantBuffer.scrollFlag == true)
		{
			if (w > FRAME_BUFFER_W)
			{
				m_backGroundConstantBuffer.screenEdgeCorrection = w / FRAME_BUFFER_W - 1;
			}
		}

		m_sprite.Init(spriteInitData);
	}

	void BackGroundRender::Update()
	{
		if (m_backGroundConstantBuffer.scrollFlag == true)
		{
			UpdateBackGroundScroll();
		}

		m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
	}

	void BackGroundRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}
}