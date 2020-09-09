#ifndef BOX_MESH_DRAWER_MAKER_H_
#define BOX_MESH_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshDrawer.h"

namespace tktk
{
	// �uBoxMeshDrawer�v�����w���p�[�N���X
	class BoxMeshDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BoxMeshDrawerMaker() = default;
		BoxMeshDrawerMaker(const BoxMeshDrawerMaker& other) = default;
		BoxMeshDrawerMaker& operator = (const BoxMeshDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static BoxMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BoxMeshDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BoxMeshDrawerMaker& drawPriority(float value);

		// �����̂̑傫����ݒ肷��
		BoxMeshDrawerMaker& boxSize(const tktkMath::Vector3& value);

		// ���[�J�����W��ݒ肷��
		BoxMeshDrawerMaker& localPosition(const tktkMath::Vector3 & value);

		// �`��F��ݒ肷��
		BoxMeshDrawerMaker& albedoColor(const tktkMath::Color & value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BoxMeshDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BoxMeshDrawerMaker& cameraHandle(unsigned int value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BoxMeshDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		BoxMeshDrawerMaker& lightHandle(unsigned int value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		BoxMeshDrawerMaker& cameraIdImpl(int value);
		BoxMeshDrawerMaker& shadowMapCameraIdImpl(int value);
		BoxMeshDrawerMaker& lightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BoxMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_boxSize			{ tktkMath::Vector3_v::one };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		BoxMeshDrawerUseResourceHandles		m_useResourceHandles{  };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !BOX_MESH_DRAWER_MAKER_H_