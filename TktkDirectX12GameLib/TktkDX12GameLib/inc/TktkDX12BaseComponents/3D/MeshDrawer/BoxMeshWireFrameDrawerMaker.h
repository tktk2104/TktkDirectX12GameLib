#ifndef BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshWireFrameDrawer.h"

namespace tktk
{
	// �uBoxMeshWireFrameDrawer�v�����w���p�[�N���X
	class BoxMeshWireFrameDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BoxMeshWireFrameDrawerMaker() = default;
		BoxMeshWireFrameDrawerMaker(const BoxMeshWireFrameDrawerMaker& other) = default;
		BoxMeshWireFrameDrawerMaker& operator = (const BoxMeshWireFrameDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static BoxMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static BoxMeshWireFrameDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BoxMeshWireFrameDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BoxMeshWireFrameDrawerMaker& drawPriority(float value);

		// �����̂̑傫����ݒ肷��
		BoxMeshWireFrameDrawerMaker& boxSize(const tktkMath::Vector3 & value);

		// ���[�J�����W��ݒ肷��
		BoxMeshWireFrameDrawerMaker& localPosition(const tktkMath::Vector3 & value);

		// �`��F��ݒ肷��
		BoxMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BoxMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BoxMeshWireFrameDrawerMaker& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BoxMeshWireFrameDrawerMaker& cameraId(ResourceIdCarrier value);

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BoxMeshWireFrameDrawerMaker& shadowMapCameraHandle(size_t value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		BoxMeshWireFrameDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		BoxMeshWireFrameDrawerMaker& lightHandle(size_t value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		BoxMeshWireFrameDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BoxMeshWireFrameDrawerMaker m_self;

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
#endif // !BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_