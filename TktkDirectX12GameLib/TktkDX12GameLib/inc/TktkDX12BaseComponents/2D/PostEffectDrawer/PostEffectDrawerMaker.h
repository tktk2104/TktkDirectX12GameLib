#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "PostEffectDrawer.h"

namespace tktk
{
	// �uPostEffectDrawer�v�����w���p�[�N���X
	class PostEffectDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		PostEffectDrawerMaker() = default;
		PostEffectDrawerMaker(const PostEffectDrawerMaker& other) = default;
		PostEffectDrawerMaker& operator = (const PostEffectDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static PostEffectDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<PostEffectDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		PostEffectDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		PostEffectDrawerMaker& useRtvDescriptorHeapId(unsigned int value);
		
		// �g�p����|�X�g�G�t�F�N�g�}�e���A���n���h����ݒ肷��
		PostEffectDrawerMaker& postEffectMaterialHandle(unsigned int value);

		// �g�p����|�X�g�G�t�F�N�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		PostEffectDrawerMaker& postEffectMaterialId(ResourceIdCarrier value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static PostEffectDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user							{  };
		float				m_drawPriority					{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle	{  }; // �������p�����[�^�̓o�b�N�o�b�t�@�[
		size_t				m_postEffectMaterialHandle		{ 0U };
	};
}
#endif // !POST_EFFECT_DRAWER_MAKER_H_