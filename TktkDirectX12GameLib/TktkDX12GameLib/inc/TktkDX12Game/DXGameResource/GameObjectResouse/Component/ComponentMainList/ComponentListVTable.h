#ifndef COMPONENT_LIST_VTABLE_H_
#define COMPONENT_LIST_VTABLE_H_

/* std::shared_ptr */
#include <memory>

/* std::forward_list */
#include <forward_list>

/* update_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>

/* afterCollide_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterCollideChecker.h>

/* onEnable_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnEnableChecker.h>

/* onDisable_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDisableChecker.h>

/* onDestroy_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>

/* funcUseType */
#include "../ComponentBase.h"

namespace tktk
{	
	// ���g���Ǘ�����R���|�[�l���g�̌^�����B�����邽�߂̊֐��|�C���^
	struct ComponentListVTable
	{
		void(*update)		(const std::forward_list<std::shared_ptr<ComponentBase>>&);
		void(*afterCollide)	(const std::forward_list<std::shared_ptr<ComponentBase>>&);
		void(*onEnable)		(const std::shared_ptr<ComponentBase>&);
		void(*onDisable)	(const std::shared_ptr<ComponentBase>&);
		void(*onDestroy)	(const std::shared_ptr<ComponentBase>&);
	};

	// ���g���Ǘ�����R���|�[�l���g�̌^�����B�����邽�߂̊֐��̎��Ԃ����݂��鏊
	template <class ComponentType>
	struct ComponentListVTableInitializer
	{
		// ���g���Ǘ�����R���|�[�l���g�̌^�����B�����邽�߂̊֐��|�C���^
		static ComponentListVTable m_componentListVTable;

		// �������X�g�̃|�C���^�̎w�����Ԃ��uupdate�v�֐��������Ă�����S�Ă̗v�f�ł�������s����
		static void update(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
		{
			for (const auto& node : mainList)
			{
				if (!node->isActive() || node->isDead()) continue;
				update_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(node));
			}
		}

		// �������X�g�̃|�C���^�̎w�����Ԃ��uafterCollide�v�֐��������Ă�����S�Ă̗v�f�ł�������s����
		static void afterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
		{
			for (const auto& node : mainList)
			{
				if (!node->isActive() || node->isDead()) continue;
				afterCollide_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(node));
			}
		}

		// �uonEnable()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
		static void onEnable(const std::shared_ptr<ComponentBase>& runPtr)	{ onEnable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr)); }

		// �uonDisable()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
		static void onDisable(const std::shared_ptr<ComponentBase>& runPtr) { onDisable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr)); }

		// �uonDestroy()�v�֐��������Ă�����Ăԏ������s���ׂ̊֐�
		static void onDestroy(const std::shared_ptr<ComponentBase>& runPtr) { onDestroy_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr)); }
	};

	// ���g���Ǘ�����R���|�[�l���g�̌^�����B�����邽�߂̊֐��|�C���^
	template<class ComponentType>
	ComponentListVTable ComponentListVTableInitializer<ComponentType>::m_componentListVTable =
	{
		&ComponentListVTableInitializer<ComponentType>::update,
		&ComponentListVTableInitializer<ComponentType>::afterCollide,
		&ComponentListVTableInitializer<ComponentType>::onEnable,
		&ComponentListVTableInitializer<ComponentType>::onDisable,
		&ComponentListVTableInitializer<ComponentType>::onDestroy
	};
}
#endif // !COMPONENT_LIST_VTABLE_H_