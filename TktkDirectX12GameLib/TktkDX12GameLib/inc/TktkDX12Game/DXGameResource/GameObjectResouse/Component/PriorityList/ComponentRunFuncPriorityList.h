#ifndef COMPONENT_RUN_FUNC_PRIORITY_LIST_H_
#define COMPONENT_RUN_FUNC_PRIORITY_LIST_H_

/* std::unordered_map */
#include <unordered_map>

/* std::type_index */
#include <typeindex>

namespace tktk
{
	// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x���Ǘ�����N���X
	class ComponentRunFuncPriorityList
	{
	public:

		// �����̌^�̃R���|�[�l���g�̍X�V�D��x��ݒ肷��
		void addPriority(std::type_index type, float priority);

		// �����̌^�̃R���|�[�l���g�̍X�V�D��x���擾����
		// �o�^����Ă��Ȃ��^�̏ꍇ�A�uBasePriority�v���Ԃ�
		float getPriority(std::type_index type) const;

	private:

		static constexpr float BasePriority{ 0.0f };

	private:

		std::unordered_map<std::type_index, float> m_updatePriorityMap;
	};
}
#endif // !COMPONENT_RUN_FUNC_PRIORITY_LIST_H_