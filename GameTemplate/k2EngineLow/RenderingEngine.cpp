#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	void RenderingEngine::Init()
	{
		InitMainRenderTarget();

		Init2DSprite();

		//InitMonochromeRenderTarget();

		InitCopyMainRenderTargetToFrameBuffer();

		m_bloom.Init(m_mainRenderTarget);

		m_shadow.Init();

		m_sceneLight.Init();
	}

	void RenderingEngine::InitMainRenderTarget()
	{
		float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void RenderingEngine::Init2DSprite()
	{
		float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };
		m_2DRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			clearColor
		);

		//最終合成用のスプライトを初期化する
		SpriteInitData spriteInitData;
		//テクスチャは2Dレンダリングターゲット
		spriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		//解像度はメインレンダリングターゲットの幅と高さ
		spriteInitData.m_width = m_mainRenderTarget.GetWidth();
		spriteInitData.m_height = m_mainRenderTarget.GetHeight();
		//2D用のシェーダーを使用する
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSMain";
		//上書き
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//レンダリングターゲットのフォーマット
		spriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();

		m_2DSprite.Init(spriteInitData);

		//テクスチャはメインレンダリングターゲット
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		//解像度は2Dレンダリングターゲットの幅と高さ
		spriteInitData.m_width = m_2DRenderTarget.GetWidth();
		spriteInitData.m_height = m_2DRenderTarget.GetHeight();
		//2D用のシェーダーを使用する
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//上書き
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//レンダリングターゲットのフォーマット
		spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();

		m_mainSprite.Init(spriteInitData);
	}

	void RenderingEngine::InitMonochromeRenderTarget()
	{
		float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_monochromeRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//最終合成用のスプライトを初期化する
		SpriteInitData spriteInitData;
		//テクスチャはモノクロ用のレンダリングターゲット
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		//解像度はモノクロ用のレンダリングターゲットの幅と高さ
		spriteInitData.m_width = m_monochromeRenderTarget.GetWidth();
		spriteInitData.m_height = m_monochromeRenderTarget.GetHeight();
		//ポストエフェクト用のシェーダーを使用する
		spriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		//上書き
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//レンダリングターゲットのフォーマット
		spriteInitData.m_colorBufferFormat[0] = m_monochromeRenderTarget.GetColorBufferFormat();

		m_monochromeSprite.Init(spriteInitData);
	}

	void RenderingEngine::InitCopyMainRenderTargetToFrameBuffer()
	{
		SpriteInitData spriteInitData;

		//テクスチャはメインレンダリングターゲット
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		//解像度はメインレンダリングターゲットの幅と高さ
		spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
		//2D用のシェーダーを使用する
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		
		m_copyToFrameBufferSprite.Init(spriteInitData);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		m_sceneLight.LightCameraUpdate();

		m_shadow.Execute(rc, m_renderObjects);

		ModelDraw(rc);

		m_bloom.Execute(rc, m_mainRenderTarget);

		SpriteFontDraw(rc);

		//OnMonochromeRendering(rc);

		CopyMainRenderTargetToFrameBuffer(rc);

		m_renderObjects.clear();
	}

	void RenderingEngine::ModelDraw(RenderContext& rc)
	{
		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_mainRenderTarget);

		for (auto renderObj : m_renderObjects)
		{
			renderObj->OnRenderModel(rc);
		}

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::SpriteFontDraw(RenderContext& rc)
	{
		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_2DRenderTarget);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_2DRenderTarget);
		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_2DRenderTarget);

		m_mainSprite.Draw(rc);

		for (auto renderObj : m_renderObjects)
		{
			renderObj->OnRender2D(rc);
		}

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_2DRenderTarget);

		//ターゲットをメインに戻す
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);

		m_2DSprite.Draw(rc);

		//メインレンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::OnMonochromeRendering(RenderContext& rc)
	{
		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);

		m_monochromeSprite.Draw(rc);

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

		m_copyToFrameBufferSprite.Draw(rc);
	}
}