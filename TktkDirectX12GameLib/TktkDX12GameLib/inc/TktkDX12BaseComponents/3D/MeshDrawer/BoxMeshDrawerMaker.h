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


		// �X�e�[�g���w�肵�A�쐬���J�n����
		static BoxMeshDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

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
		BoxMeshDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BoxMeshDrawerMaker& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BoxMeshDrawerMaker& cameraId(ResourceIdCarrier value);

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BoxMeshDrawerMaker& shadowMapCameraHandle(size_t value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BoxMeshDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		BoxMeshDrawerMaker& lightHandle(size_t value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		BoxMeshDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BoxMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr						m_user				{  };
		StateTypeHierarchy					m_targetState		{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_boxSize			{ tktkMath::Vector3_v::one };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		BoxMeshDrawerUseResourceHandles		m_useResourceHandles{  };
	};
}
#endif // !BOX_MESH_DRAWER_MAKER_H_