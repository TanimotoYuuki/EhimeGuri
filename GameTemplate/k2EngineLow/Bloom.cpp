#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow
{
	void Bloom::Init(RenderTarget& rt)
	{
		InitLuminnceRenderTarget(rt);

		SetLuminanceSprite(rt);

		InitGaussianBlur();

		SetFinalSprite(rt);
	}

	void Bloom::InitLuminnceRenderTarget(RenderTarget& rt)
	{
		m_luminnceRenderTarget.Create(
			rt.GetWidth(),
			rt.GetHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	void Bloom::SetLuminanceSprite(RenderTarget& rt)
	{
		SpriteInitData luminanceSpriteInitData;
		//輝度抽出用のシェーダーを使用する
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSLuminance";
		//解像度はメインレンダリングターゲットの幅と高さ
		luminanceSpriteInitData.m_width = rt.GetWidth();
		luminanceSpriteInitData.m_height = rt.GetHeight();
		//テクスチャはメインレンダリングターゲット
		luminanceSpriteInitData.m_textures[0] = &rt.GetRenderTargetTexture();
		//レンダリングターゲットのフォーマット
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_luminanceSprite.Init(luminanceSpriteInitData);
	}

	void Bloom::InitGaussianBlur()
	{
		m_gaussianBlur[0].Init(&m_luminnceRenderTarget.GetRenderTargetTexture());
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());
	}

	void Bloom::SetFinalSprite(RenderTarget& rt)
	{
		SpriteInitData finalSpriteInitData;
		//テクスチャはガウシアンブラー
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();
		//解像度はメインレンダリングターゲットの幅と高さ
		finalSpriteInitData.m_width = rt.GetWidth();
		finalSpriteInitData.m_height = rt.GetHeight();
		//2D用のシェーダーを使用する
		finalSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
		//加算描画
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		//レンダリングターゲットのフォーマット
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::Execute(RenderContext& rc, RenderTarget& rt)
	{
		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_luminnceRenderTarget);
		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_luminnceRenderTarget);

		//輝度抽出を行う
		m_luminanceSprite.Draw(rc);

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);

		m_gaussianBlur[0].ExecuteOnGPU(rc, 20);
		m_gaussianBlur[1].ExecuteOnGPU(rc, 20);
		m_gaussianBlur[2].ExecuteOnGPU(rc, 20);
		m_gaussianBlur[3].ExecuteOnGPU(rc, 20);

		//ターゲットをメインに戻す
		rc.WaitUntilToPossibleSetRenderTarget(rt);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(rt);

		//輝度抽出を行う
		m_finalSprite.Draw(rc);

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(rt);
	}
}