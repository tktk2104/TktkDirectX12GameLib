#ifndef SHADOW_MAP_CAMERA_CONTROLLER_MAKER_H_
#define SHADOW_MAP_CAMERA_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "ShadowMapCameraController.h"

namespace tktk
{
	// �uShadowMapCameraController�v�����w���p�[�N���X
	class ShadowMapCameraControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		ShadowMapCameraControllerMaker() = default;
		ShadowMapCameraControllerMaker(const ShadowMapCameraControllerMaker& other) = default;
		ShadowMapCameraControllerMaker& operator = (const ShadowMapCameraControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static ShadowMapCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ShadowMapCameraController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉���J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		ShadowMapCameraControllerMaker& initCameraHandle(size_t value);

		// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		ShadowMapCameraControllerMaker& initCameraId(ResourceIdCarrier value);

		// �J�����̌�������̃^�O��ݒ肷��
		ShadowMapCameraControllerMaker& targetTag(GameObjectTagCarrier value);

		// �J�����p�x��ݒ肷��
		ShadowMapCameraControllerMaker& direction(const tktkMath::Vector3& value);

		// �����J�������͈͂�ݒ肷��
		ShadowMapCameraControllerMaker& initCameraWidth(float value);

		// �����J�����c�͈͂�ݒ肷��
		ShadowMapCameraControllerMaker& initCameraHeight(float value);

		// �����߃N���b�v�l��ݒ肷��
		ShadowMapCameraControllerMaker& initCameraNear(float value);

		// �������N���b�v�l��ݒ肷��
		ShadowMapCameraControllerMaker& initCameraFar(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static ShadowMapCameraControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user				{  };
		size_t					m_initCameraHandle	{ 0U };
		GameObjectTagCarrier	m_targetTag			{ -1 };
		tktkMath::Vector3		m_direction			{ tktkMath::Vector3_v::forwardLH };
		float					m_initCameraWidth	{ 100.0f };
		float					m_initCameraHeight	{ 100.0f };
		float					m_initCameraNear	{ 1.0f };
		float					m_initCameraFar		{ 100.0f };
	};
}
#endif // !SHADOW_MAP_CAMERA_CONTROLLER_MAKER_H_