#ifndef COMPONENT_START_RUNNER_H_
#define COMPONENT_START_RUNNER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "../ComponentBasePtr.h"

namespace tktk
{
	// �R���|�[�l���g�́ustart�v�֐����ĂԂ��߂̃N���X
	class ComponentStartFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentStartFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// �ustart�v�֐����Ă�
		void runStart();

		// �R���|�[�l���g�̎��S�t���O���擾����
		bool isDead() const;

	private:

		struct VTable
		{
			void(*runStart)(const ComponentBasePtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// �ustart�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
			static void runStart(const ComponentBasePtr& runPtr);

			static VTable m_vtable;
		};

	private:

		bool				m_afterRun{ false };
		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType>
	inline ComponentStartFuncRunner::ComponentStartFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentStartFuncRunner::VTable ComponentStartFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentStartFuncRunner::VTableInitializer<ComponentType>::runStart
	};

	// �ustart()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
	template<class ComponentType>
	inline void ComponentStartFuncRunner::VTableInitializer<ComponentType>::runStart(const ComponentBasePtr& runPtr)
	{
		start_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>());
	}
}
#endif // !COMPONENT_START_RUNNER_H_