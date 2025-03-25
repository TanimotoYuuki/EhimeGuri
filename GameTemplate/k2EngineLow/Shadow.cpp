#include "k2EngineLowPreCompile.h"
#include "Shadow.h"

namespace nsK2EngineLow
{
	void Shadow::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMap.Create(
			1024,
			1024,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void Shadow::Execute(RenderContext& rc, std::vector<IRenderer*>& ro)
	{
		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_shadowMap);
		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_shadowMap);

		for (auto& renderObj : ro)
		{
			renderObj->OnRenderShadowMap(rc, g_renderingEngine->GetLightCamera());
		}

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);
	}
}