#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow
{
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isShadowCaster,
		bool isShadowReceiver,
		AlphaBlendMode alphaBlendMode)
	{
		InitSkeleton(filePath);
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		if (isShadowCaster)
		{
			InitShadowCasterDrawing(filePath, enModelUpAxis, alphaBlendMode);
		}
		InitModel(filePath, enModelUpAxis, isShadowReceiver, alphaBlendMode);
	}

	void ModelRender::IniTranslucent(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isShadowCaster,
		bool isShadowReceiver,
		AlphaBlendMode alphaBlendMode)
	{
		InitSkeleton(filePath);
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		if (isShadowCaster)
		{
			InitShadowCasterDrawing(filePath, enModelUpAxis, alphaBlendMode);
		}
		InitModel(filePath, enModelUpAxis, isShadowReceiver, alphaBlendMode);
	}

	void ModelRender::InitSkyCube(ModelInitData& initData)
	{
		m_model.Init(initData);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(m_skeleton,
				m_animationClips,
				m_numAnimationClips);
		}
	}

	void ModelRender::InitShadowCasterDrawing(const char* filePath, EnModelUpAxis enModelUpAxis, AlphaBlendMode alphaBlendMode)
	{
		ModelInitData shadowInitData;
		shadowInitData.m_tkmFilePath = filePath;
		shadowInitData.m_fxFilePath = "Assets/shader/shadowMap.fx";
		shadowInitData.m_vsEntryPointFunc = "VSMain";
		shadowInitData.m_psEntryPointFunc = "PSShadowCaster";
		
		if (m_animationClips != nullptr)
		{
			shadowInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			shadowInitData.m_skeleton = &m_skeleton;
		}
		shadowInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		shadowInitData.m_modelUpAxis = enModelUpAxis;
		shadowInitData.m_alphaBlendMode = alphaBlendMode;

		m_shadowModel.Init(shadowInitData);
	}

	void ModelRender::InitModel(const char* filePath, EnModelUpAxis enModelUpAxis, bool isShadowReceiver,AlphaBlendMode alphaBlendMode)
	{
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = filePath;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		modelInitData.m_vsEntryPointFunc = "VSMain";

		if (isShadowReceiver)
		{
			modelInitData.m_psEntryPointFunc = "PSShadowReceiverMain";
			modelInitData.m_expandShaderResoruceView[0] = &(g_renderingEngine->GetShadow().GetRenderTargetTexture());
		}
		else
		{
			modelInitData.m_psEntryPointFunc = "PSNormalMain";
		}

		if (m_animationClips != nullptr)
		{
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			modelInitData.m_skeleton = &m_skeleton;
		}

		modelInitData.m_modelUpAxis = enModelUpAxis;
		modelInitData.m_alphaBlendMode = alphaBlendMode;

		modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLight();
		modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLight());

		m_model.Init(modelInitData);
	}

	void ModelRender::Update()
	{
		//スケルトンを更新
		m_skeleton.Update(m_model.GetWorldMatrix());

		//モデルの更新
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//アニメーションを進める
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		//m_model.Draw(rc, 1, m_alpha);
		g_renderingEngine->AddRenderObject(this);
	}

	void ModelRender::OnRenderShadowMap(RenderContext& rc, Camera& ca)
	{
		if (m_shadowModel.IsInited())
		{
			m_shadowModel.Draw(rc, ca ,1, m_alpha);
		}
	}

	void ModelRender::OnRenderModel(RenderContext& rc)
	{
		if (m_model.IsInited())
		{
			m_model.Draw(rc, 1, m_alpha);
		}
	}
}