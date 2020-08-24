#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "../ComponentBasePtr.h"

namespace tktk
{
	// �R���|�[�l���g�̕`��֐����ĂԂ��߂̃N���X
	class ComponentDrawFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentDrawFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// �`�揈�����s��
		void runDrawFunc() const;

		// �R���|�[�l���g�����S���Ă��邩���擾����
		bool isDead() const;

	private:

		struct VTable
		{
			void(*runDraw)	(const ComponentBasePtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// �udraw�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
			static void runDraw(const ComponentBasePtr& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType>
	inline ComponentDrawFuncRunner::ComponentDrawFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentDrawFuncRunner::VTable ComponentDrawFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentDrawFuncRunner::VTableInitializer<ComponentType>::runDraw,
	};

	// �udraw�v�֐��������Ă�����Ăԏ���
	template<class ComponentType>
	inline void ComponentDrawFuncRunner::VTableInitializer<ComponentType>::runDraw(const ComponentBasePtr& runPtr)
	{
		draw_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>());
	}
}
#endif // !COMPONENT_DRAW_RUNNER_H_