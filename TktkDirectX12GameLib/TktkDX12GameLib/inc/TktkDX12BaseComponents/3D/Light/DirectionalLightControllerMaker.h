#ifndef DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "DirectionalLightController.h"

namespace tktk
{
	class DirectionalLightControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		DirectionalLightControllerMaker() = default;
		DirectionalLightControllerMaker(const DirectionalLightControllerMaker& other) = default;
		DirectionalLightControllerMaker& operator = (const DirectionalLightControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static DirectionalLightControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<DirectionalLightController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉�����C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		DirectionalLightControllerMaker& initLightHandle(size_t value);

		// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		DirectionalLightControllerMaker& initLightId(ResourceIdCarrier value);

		// ����������ݒ肷��
		DirectionalLightControllerMaker& initAmbient(const tktkMath::Color & value);

		// �����g�U���ˌ���ݒ肷��
		DirectionalLightControllerMaker& initDiffuse(const tktkMath::Color & value);

		// �������ʔ��ˌ���ݒ肷��
		DirectionalLightControllerMaker& initSpeqular(const tktkMath::Color & value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static DirectionalLightControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		size_t				m_initLightHandle	{ 0U };
		tktkMath::Color		m_initAmbient		{ 0.1f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 1.0f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 1.0f, 1.0f };
	};
}
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_