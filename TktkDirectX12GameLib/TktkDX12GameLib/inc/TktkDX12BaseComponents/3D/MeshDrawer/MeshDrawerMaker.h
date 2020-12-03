#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	private:

		MeshDrawerMaker() = default;
		MeshDrawerMaker(const MeshDrawerMaker& other) = default;
		MeshDrawerMaker& operator = (const MeshDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static MeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<MeshDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���郁�b�V���n���h����ݒ肷��
		MeshDrawerMaker& meshHandle(size_t value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		MeshDrawerMaker& meshId(ResourceIdCarrier value);

		// �g�p����X�P���g���n���h����ݒ肷��
		MeshDrawerMaker& skeletonHandle(size_t value);

		// �g�p����X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		MeshDrawerMaker& skeletonId(ResourceIdCarrier value);

		// ��{�̍��W��ݒ肷��
		MeshDrawerMaker& basePosition(const tktkMath::Vector3 & value);

		// ��{�̃X�P�[����ݒ肷��
		MeshDrawerMaker& baseScale(const tktkMath::Vector3 & value);

		// ��{�̉�]��ݒ肷��
		MeshDrawerMaker& baseRotation(const tktkMath::Quaternion & value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user			{  };
		size_t					m_meshHandle	{  };
		size_t					m_skeletonHandle{  };
		tktkMath::Vector3		m_basePosition	{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_baseScale		{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation	{ tktkMath::Quaternion_v::identity };
	};
}
#endif // !MESH_DRAWER_MAKER_H_