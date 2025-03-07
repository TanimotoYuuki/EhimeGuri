#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"
namespace nsK2EngineLow
{
	void SceneLight::Init()
	{
		//�f�B���N�V�������C�g�̕���
		m_light.directionLight.direction.x = 1.0f;
		m_light.directionLight.direction.y = -1.0f;
		m_light.directionLight.direction.z = -1.0f;

		//���K��
		m_light.directionLight.direction.Normalize();

		//�f�B���N�V�������C�g�̃J���[
		m_light.directionLight.color.x = 0.5f;
		m_light.directionLight.color.y = 0.5f;
		m_light.directionLight.color.z = 0.5f;

		//����
		m_light.ambientLight.x = 0.3f;
		m_light.ambientLight.y = 0.3f;
		m_light.ambientLight.z = 0.3f;
		m_light.eyePos = g_camera3D->GetPosition();

		//�������C�g�̒n�ʐF
		m_light.hemLight.groundColor = Vector3(0.1f, 0.1f, 0.1f);
		//�������C�g�̓V���F
		m_light.hemLight.skyColor = Vector3(0.05f, 0.1f, 0.2f);
		//�������C�g�̒n�ʂ̖@��
		m_light.hemLight.groundNormal = Vector3(0.0f, 1.0f, 0.0f);
	}
}