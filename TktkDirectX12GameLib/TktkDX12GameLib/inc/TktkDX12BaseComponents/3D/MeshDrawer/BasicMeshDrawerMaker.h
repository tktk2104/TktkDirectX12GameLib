#ifndef BASIC_MESH_DRAWER_MAKER_H_
#define BASIC_MESH_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicMeshDrawer.h"

namespace tktk
{
	// �uBasicMeshDrawer�v�����w���p�[�N���X
	class BasicMeshDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BasicMeshDrawerMaker() = default;
		BasicMeshDrawerMaker(const BasicMeshDrawerMaker& other) = default;
		BasicMeshDrawerMaker& operator = (const BasicMeshDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static BasicMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BasicMeshDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BasicMeshDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		BasicMeshDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p���郁�b�V���n���h����ݒ肷��
		BasicMeshDrawerMaker& meshHandle(unsigned int value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& meshId(IdType value) { return meshIdImpl(static_cast<int>(value)); }

		// �g�p����X�P���g���̃��\�[�X�n���h����ݒ肷��
		BasicMeshDrawerMaker& skeletonHandle(unsigned int value);

		// �g�p����X�P���g���̃��\�[�XID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& skeletonId(IdType value) { return skeletonIdImpl(static_cast<int>(value)); }

		// �g�p����J�����n���h����ݒ肷��
		BasicMeshDrawerMaker& cameraHandle(unsigned int value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		BasicMeshDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// �g�p���郉�C�g�n���h����ݒ肷��
		BasicMeshDrawerMaker& lightHandle(unsigned int value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		BasicMeshDrawerMaker& meshIdImpl(int value);
		BasicMeshDrawerMaker& skeletonIdImpl(int value);
		BasicMeshDrawerMaker& cameraIdImpl(int value);
		BasicMeshDrawerMaker& shadowMapCameraIdImpl(int value);
		BasicMeshDrawerMaker& lightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };	
		BasicMeshDrawerUseResourceHandles	m_useResourceHandles{  }; // ���uRtvDescriptorHeap�v�̏����p�����[�^�̓o�b�N�o�b�t�@�[

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& skeletonId(IdType value) { static_assert(false, "SkeletonId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !BASIC_MESH_DRAWER_MAKER_H_