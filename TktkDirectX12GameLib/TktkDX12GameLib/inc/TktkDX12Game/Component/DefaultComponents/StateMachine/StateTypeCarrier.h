#ifndef STATE_TYPE_CARRIER_H_
#define STATE_TYPE_CARRIER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// �X�e�[�g�̎�ނ�ێ�����\����
	struct StateTypeCarrier
	{
	public:

		StateTypeCarrier() = default;

		// �Öٕϊ����������߂ɂ킴�Ɓuexplicit�v���O���Ă���
		template <class StateType, IsSignedInt32<StateType> = nullptr>
		StateTypeCarrier(StateType tag) : type(static_cast<int>(tag)) {}

		// �s���Ȍ^��StateType�Ƃ��Ĉ������Ƃ���
		template <class StateType, IsNotSignedInt32<StateType> = nullptr>
		StateTypeCarrier(StateType tag) { static_assert(false, "StateType Fraud Type"); }

	public:

		// �����̃X�e�[�g�̎�ނƎ��g�̃X�e�[�g�̎�ނ������������ʂ���
		template <class StateType, IsSignedInt32<StateType> = nullptr>
		bool isSame(StateType other) { return type == static_cast<int>(other); }

		// �s���Ȍ^���r����
		template <class StateType, IsNotSignedInt32<StateType> = nullptr>
		bool isSame(StateType other) { static_assert(false, "StateType Fraud Type"); }

	public:

		bool operator==(const StateTypeCarrier& other) const { return type == other.type; }
		bool operator!=(const StateTypeCarrier& other) const { return type != other.type; }

	public:

		int type{};
	};
}

// �uStateTypeCarrier�v���n�b�V���ɑΉ�������
template<>
struct std::hash<tktk::StateTypeCarrier>
{
	size_t operator()(const tktk::StateTypeCarrier& data) const { return std::hash<int>()(data.type); }
};
#endif // !STATE_TYPE_CARRIER_H_
