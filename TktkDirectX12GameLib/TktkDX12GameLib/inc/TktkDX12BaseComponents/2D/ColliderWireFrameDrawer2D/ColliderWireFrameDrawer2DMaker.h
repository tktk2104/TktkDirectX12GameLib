#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	// �uColliderWireFrameDrawer2D�v�̃C���X�^���X���쐬����N���X
	class ColliderWireFrameDrawer2DMaker
	{
	private:  /* �v���C�x�[�g�R���X�g���N�^�B */

		ColliderWireFrameDrawer2DMaker() = default;
		ColliderWireFrameDrawer2DMaker(const ColliderWireFrameDrawer2DMaker & other) = default;
		ColliderWireFrameDrawer2DMaker& operator = (const ColliderWireFrameDrawer2DMaker & other) = default;

	public:

		// �쐬�J�n
		static ColliderWireFrameDrawer2DMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static ColliderWireFrameDrawer2DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ColliderWireFrameDrawer2D> create();

		// �`��D��x��ݒ肷��
		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		// ���̐F��ݒ肷��
		ColliderWireFrameDrawer2DMaker& lineColor(const tktkMath::Color& value);

	private:

		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr				m_user			{ };
		std::vector<int>			m_targetState	{ };
		float						m_drawPriority	{ 0.0f };
		tktkMath::Color				m_lineColor		{ tktkMath::Color_v::white };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline ColliderWireFrameDrawer2DMaker& ColliderWireFrameDrawer2DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// �쐬�J�n�������s��
		auto& result = makeStart(user);

		// �������q���X�g��z��ɕϊ�
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// �Ώۂ̃X�e�[�g�̊K�w�����̃��������m��
		result.m_targetState.reserve(targetStateArray.size());

		// �Ώۂ̃X�e�[�g�̊K�w��ݒ肷��
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// ���g�̎Q�Ƃ�Ԃ�
		return result;
	}
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
