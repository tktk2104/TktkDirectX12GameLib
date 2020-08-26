#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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
		
		// �g�p����|�X�g�G�t�F�N�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template<class IdType, is_idType<IdType> = nullptr>
		PostEffectDrawerMaker& postEffectMaterialId(IdType value);

	private: /* �e��id�w��n�̊֐��̎��� */

		PostEffectDrawerMaker& postEffectMaterialIdImpl(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static PostEffectDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user							{  };
		float			m_drawPriority					{ 0.0f };
		unsigned int	m_useRtvDescriptorHeapHandle	{  }; // �������p�����[�^�̓o�b�N�o�b�t�@�[
		unsigned int	m_postEffectMaterialId			{ 0U };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PostEffectDrawerMaker& postEffectMaterialId(IdType value) { static_assert(false, "PostEffectMaterialId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p����|�X�g�G�t�F�N�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, is_idType<IdType>>
	inline PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialId(IdType value)
	{
		return postEffectMaterialIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !POST_EFFECT_DRAWER_MAKER_H_