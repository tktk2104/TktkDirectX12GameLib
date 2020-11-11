#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include "MeshAnimator.h"

namespace tktk
{
	// �uMeshAnimator�v�����w���p�[�N���X
	class MeshAnimatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// �쐬�J�n
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<MeshAnimator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// ���[�V���������[�v�����邩��ݒ肷��
		MeshAnimatorMaker& isLoop(bool value);

		// ���[�V�����̍Đ����x�{����ݒ肷��
		MeshAnimatorMaker& motionSpeedRate(float value);

		// �g�p���鏉�����[�V�����n���h����ݒ肷��
		MeshAnimatorMaker& initMotionHandle(size_t value);

		// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		MeshAnimatorMaker& initMotionId(ResourceIdCarrier value);

		// �P�b�Ԃɉ��t���[�����̃A�j���[�V�������Đ����邩��ݒ肷��
		MeshAnimatorMaker& animFramePerSec(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MeshAnimatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		bool				m_isLoop			{ true };
		float				m_motionSpeedRate	{ 1.0f };
		size_t				m_initMotionHandle	{ 0U };
		float				m_animFramePerSec	{ 60.0f };
	};
}
#endif // !MESH_ANIMATOR_MAKER_H_
