#ifndef BASIC_MESH_DRAWER_MAKER_H_
#define BASIC_MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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

		// ��{�̃X�P�[����ݒ肷��
		BasicMeshDrawerMaker& baseScale(const tktkMath::Vector3& value);

		// ��{�̉�]��ݒ肷��
		BasicMeshDrawerMaker& baseRotation(const tktkMath::Quaternion& value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BasicMeshDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p���郁�b�V���n���h����ݒ肷��
		BasicMeshDrawerMaker& meshHandle(size_t value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BasicMeshDrawerMaker& meshId(ResourceIdCarrier value);

		// �g�p����X�P���g���̃��\�[�X�n���h����ݒ肷��
		BasicMeshDrawerMaker& skeletonHandle(size_t value);

		// �g�p����X�P���g���̃��\�[�XID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BasicMeshDrawerMaker& skeletonId(ResourceIdCarrier value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BasicMeshDrawerMaker& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BasicMeshDrawerMaker& cameraId(ResourceIdCarrier value);

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BasicMeshDrawerMaker& shadowMapCameraHandle(size_t value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BasicMeshDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		BasicMeshDrawerMaker& lightHandle(size_t value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		BasicMeshDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_baseScale			{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion				m_baseRotation		{ tktkMath::Quaternion_v::identity };
		BasicMeshDrawerUseResourceHandles	m_useResourceHandles{  };
	};
}
#endif // !BASIC_MESH_DRAWER_MAKER_H_