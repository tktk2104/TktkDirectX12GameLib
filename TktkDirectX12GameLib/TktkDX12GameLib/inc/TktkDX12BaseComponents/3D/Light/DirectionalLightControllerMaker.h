#ifndef DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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
		DirectionalLightControllerMaker& initLightHandle(unsigned int value);

		// ����������ݒ肷��
		DirectionalLightControllerMaker& initDirection(const tktkMath::Vector3& value);

		// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		DirectionalLightControllerMaker& initLightId(IdType value) { return initLightIdImpl(static_cast<int>(value)); }

		// ����������ݒ肷��
		DirectionalLightControllerMaker& initAmbient(const tktkMath::Color & value);

		// �����g�U���ˌ���ݒ肷��
		DirectionalLightControllerMaker& initDiffuse(const tktkMath::Color & value);

		// �������ʔ��ˌ���ݒ肷��
		DirectionalLightControllerMaker& initSpeqular(const tktkMath::Color & value);

	private: /* �e��id�w��n�̊֐��̎��� */

		DirectionalLightControllerMaker& initLightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static DirectionalLightControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		unsigned int		m_initLightHandle	{ 0U };
		tktkMath::Vector3	m_initDirection		{ 1.0f, -1.0f, 1.0f };
		tktkMath::Color		m_initAmbient		{ 0.25f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 0.25f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 0.25f, 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		DirectionalLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_