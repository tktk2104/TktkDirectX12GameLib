#ifndef CUR_STATE_TYPE_LIST_H_
#define CUR_STATE_TYPE_LIST_H_

/* std::unordered_set */
#include <unordered_set>

/* baseClass */
#include "../../ComponentBase.h"

/* class member */
#include "Structs/StateTypeCarrier.h"

namespace tktk
{
	// ���g�̃X�e�[�g���Ǘ�����R���|�[�l���g
	class CurStateTypeList
		: public ComponentBase
	{
	public:

		CurStateTypeList() = default;

	public:

		// �X�e�[�g��L���ɂ���
		void stateEnable(StateTypeCarrier stateType);

		// �X�e�[�g�𖳌��ɂ���
		void stateDisable(StateTypeCarrier stateType);

		// �S�ẴX�e�[�g�𖳌��ɂ���
		void clearState();

		// �����̃X�e�[�g�������Ă��邩�H
		bool contain(StateTypeCarrier stateType) const;

	private:

		// ���݂̃X�e�[�g�̃��X�g
		std::unordered_set<StateTypeCarrier> m_stateTypeList;
	};
}
#endif // !CUR_STATE_TYPE_LIST_H_