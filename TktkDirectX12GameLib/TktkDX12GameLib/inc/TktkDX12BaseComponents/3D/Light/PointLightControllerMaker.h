#ifndef POINT_LIGHT_CONTROLLER_MAKER_H_
#define POINT_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "PointLightController.h"

namespace tktk
{
	// �uPointLightController�v�����w���p�[�N���X
	class PointLightControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		PointLightControllerMaker() = default;
		PointLightControllerMaker(const PointLightControllerMaker& other) = default;
		PointLightControllerMaker& operator = (const PointLightControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static PointLightControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<PointLightController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉�����C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		PointLightControllerMaker& initLightHandle(unsigned int value);

		// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		PointLightControllerMaker& initLightId(IdType value) { return initLightIdImpl(static_cast<int>(value)); }

		// ����������ݒ肷��
		PointLightControllerMaker& initAmbient(const tktkMath::Color& value);

		// �����g�U���ˌ���ݒ肷��
		PointLightControllerMaker& initDiffuse(const tktkMath::Color& value);

		// �������ʔ��ˌ���ݒ肷��
		PointLightControllerMaker& initSpeqular(const tktkMath::Color& value);

	private: /* �e��id�w��n�̊֐��̎��� */

		PointLightControllerMaker& initLightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static PointLightControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user				{  };
		unsigned int	m_initLightHandle	{ 0U };
		tktkMath::Color	m_initAmbient		{ 0.1f, 1.0f };
		tktkMath::Color	m_initDiffuse		{ 1.0f, 1.0f };
		tktkMath::Color	m_initSpeqular		{ 1.0f, 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PointLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !POINT_LIGHT_CONTROLLER_MAKER_H_