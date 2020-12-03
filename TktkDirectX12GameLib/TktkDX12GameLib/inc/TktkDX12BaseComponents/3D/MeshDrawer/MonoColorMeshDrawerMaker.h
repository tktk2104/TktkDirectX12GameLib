#ifndef MONO_COLOR_MESH_DRAWER_MAKER_H_
#define MONO_COLOR_MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "MonoColorMeshDrawer.h"

namespace tktk
{
	class MonoColorMeshDrawerMaker
	{
	private:

		MonoColorMeshDrawerMaker() = default;
		MonoColorMeshDrawerMaker(const MonoColorMeshDrawerMaker& other) = default;
		MonoColorMeshDrawerMaker& operator = (const MonoColorMeshDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static MonoColorMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<MonoColorMeshDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �����̃��b�V���n���h����ݒ肷��
		MonoColorMeshDrawerMaker& setBoxMesh();

		// �����̃��b�V�����C���[�t���[���n���h����ݒ肷��
		MonoColorMeshDrawerMaker& setBoxMeshWireFrame();

		// ���̃��b�V���n���h����ݒ肷��
		MonoColorMeshDrawerMaker& setSphereMesh();

		// ���̃��b�V�����C���[�t���[���n���h����ݒ肷��
		MonoColorMeshDrawerMaker& setSphereMeshWireFrame();

		// �g�p���郁�b�V���n���h����ݒ肷��
		MonoColorMeshDrawerMaker& meshHandle(size_t value);

		// �g�p���郁�b�V��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		MonoColorMeshDrawerMaker& meshId(ResourceIdCarrier value);

		// �g�p����X�P���g���n���h����ݒ肷��
		MonoColorMeshDrawerMaker& skeletonHandle(size_t value);

		// �g�p����X�P���g��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		MonoColorMeshDrawerMaker& skeletonId(ResourceIdCarrier value);

		// �A���x�h�J���[��ݒ肷��
		MonoColorMeshDrawerMaker& albedoColor(const tktkMath::Color& value);

		// ��{�̍��W��ݒ肷��
		MonoColorMeshDrawerMaker& basePosition(const tktkMath::Vector3 & value);

		// ��{�̃X�P�[����ݒ肷��
		MonoColorMeshDrawerMaker& baseScale(const tktkMath::Vector3 & value);

		// ��{�̉�]��ݒ肷��
		MonoColorMeshDrawerMaker& baseRotation(const tktkMath::Quaternion & value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MonoColorMeshDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user				{  };
		size_t					m_meshHandle		{  };
		size_t					m_skeletonHandle	{  };
		tktkMath::Color			m_albedoColor		{ tktkMath::Color_v::white };
		tktkMath::Vector3		m_basePosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_baseScale			{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation		{ tktkMath::Quaternion_v::identity };
	};
}
#endif // !MONO_COLOR_MESH_DRAWER_MAKER_H_