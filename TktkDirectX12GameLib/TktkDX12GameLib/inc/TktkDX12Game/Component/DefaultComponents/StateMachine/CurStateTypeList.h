#ifndef CUR_STATE_TYPE_LIST_H_
#define CUR_STATE_TYPE_LIST_H_

#include <forward_list>
#include "../../ComponentBase.h"

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
		void stateEnable(int stateType);

		// �X�e�[�g�𖳌��ɂ���
		void stateDisable(int stateType);

		// �S�ẴX�e�[�g�𖳌��ɂ���
		void clearState();

		// �����̃X�e�[�g�������Ă��邩�H
		bool contain(int stateType) const;

	private:

		// ���݂̃X�e�[�g�̃��X�g
		std::forward_list<int> m_stateTypeList;
	};
}
#endif // !CUR_STATE_TYPE_LIST_H_