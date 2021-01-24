#ifndef COMPONENT_V_TABLE_H_
#define COMPONENT_V_TABLE_H_

/* awake_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAwakeChecker.h>

/* start_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>

/* draw_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>

/* isCollide_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>

/* handleMessage_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasHandleMessageChecker.h>

/* afterChangeParent_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>

/* onCollisionEnter_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>

/* onCollisionStay_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>

/* onCollisionExit_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>

/* funcUseType */
#include "ComponentBasePtr.h"
#include "../../../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	class MessageAttachment;
	class GameObjectPtr;

	// �R���|�[�l���g�N���X�́uawake�v�֐����s�N���X
	struct ComponentAwakeFuncVTable
	{
		void(*awake)(const ComponentBasePtr&);
	};

	// �R���|�[�l���g�N���X�́ustart�v�֐����s�N���X
	struct ComponentStartFuncVTable
	{
		bool(*hasStartFunc)();

		void(*start)(const ComponentBasePtr&);
	};

	// �R���|�[�l���g�N���X�́udraw�v�֐����s�N���X
	struct ComponentDrawFuncVTable
	{
		bool(*hasDrawFunc)();

		void(*draw)(const ComponentBasePtr&);
	};

	// �R���|�[�l���g�N���X�̏Փˊ֐����s�N���X
	struct ComponentCollisionFuncVTable
	{
		bool(*hasCollideFunc)();

		bool(*isCollide)(const ComponentBasePtr&, const ComponentBasePtr&);
	};

	// �R���|�[�l���g�N���X�̃Q�[���I�u�W�F�N�g�֐����s�N���X
	struct ComponentGameObjectFuncVTable
	{
		void(*handleMessage)		(const ComponentBasePtr&, MessageTypeCarrier, const MessageAttachment&);
		void(*afterChangeParent)	(const ComponentBasePtr&, const GameObjectPtr&);
		void(*onCollisionEnter)		(const ComponentBasePtr&, const GameObjectPtr&);
		void(*onCollisionStay)		(const ComponentBasePtr&, const GameObjectPtr&);
		void(*onCollisionExit)		(const ComponentBasePtr&, const GameObjectPtr&);
	};

	// �R���|�[�l���g�̊֐����s�N���X�̏W����
	struct ComponentVTableBundle
	{
		// �e���v���[�g�N���X���uawake�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		ComponentAwakeFuncVTable*		awakeFuncVTable;

		// �e���v���[�g�N���X���ustart�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		ComponentStartFuncVTable*		startFuncVTable;

		// �e���v���[�g�N���X���udraw�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		ComponentDrawFuncVTable*		drawFuncVTable;

		// �e���v���[�g�N���X���Փˊ֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		ComponentCollisionFuncVTable*	collisionFuncVTable;

		// �e���v���[�g�N���X���Q�[���I�u�W�F�N�g�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		ComponentGameObjectFuncVTable*	componentGameObjectFuncVTable;
	};

	// �uComponentVTable�v����邽�߂ɕK�v�ȐÓI�֐��|�C���^
	template <class ComponentType>
	struct ComponentVTableInitializer
	{
		// �e���v���[�g�N���X���uawake�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		static ComponentAwakeFuncVTable		m_awakeFuncVTable;

		// �e���v���[�g�N���X���ustart�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		static ComponentStartFuncVTable		m_startFuncVTable;
		
		// �e���v���[�g�N���X���udraw�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		static ComponentDrawFuncVTable		m_drawFuncVTable;
		
		// �e���v���[�g�N���X���Փˊ֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		static ComponentCollisionFuncVTable m_collisionFuncVTable;
		
		// �e���v���[�g�N���X���Q�[���I�u�W�F�N�g�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		static ComponentGameObjectFuncVTable m_componentGameObjectFuncVTable;

		// �R���|�[�l���g�̊֐����s�N���X�̏W����
		static ComponentVTableBundle		m_componentVTableBundle;

		// �����̃|�C���^�̎w�����Ԃ��ustart�v�������Ă��邩�H
		static bool hasStartFunc()		{ return has_start_checker<ComponentType*, void>::value; }

		// �����̃|�C���^�̎w�����Ԃ��udraw�v�������Ă��邩�H
		static bool hasDrawFunc()		{ return has_draw_checker<ComponentType*, void>::value; }

		// �����̃|�C���^�̎w�����Ԃ��uisCollide�v�������Ă��邩�H
		static bool hasCollideFunc()	{ return has_isCollide_checker<ComponentType*, bool, const ComponentBasePtr&>::value; }

		// �����̃|�C���^�̎w�����Ԃ��uawake�v�֐��������Ă�������s����
		static void awake(const ComponentBasePtr& runPtr)																		{ awake_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>()); }

		// �����̃|�C���^�̎w�����Ԃ��ustart�v�֐��������Ă�������s����
		static void start(const ComponentBasePtr& runPtr)																		{ start_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>()); }

		// �����̃|�C���^�̎w�����Ԃ��udraw�v�֐��������Ă�������s����
		static void draw(const ComponentBasePtr& runPtr)																		{ draw_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>()); }

		// �����̃|�C���^�̎w�����Ԃ��uisCollide�v�������Ă�������s����
		static bool isCollide(const ComponentBasePtr& self, const ComponentBasePtr& other)										{ return isCollide_runner<bool, const ComponentBasePtr&>::checkAndRun(self.castPtr<ComponentType>(), false, other); }
	
		// �����̃|�C���^�̎w�����Ԃ��uhandleMessage�v�������Ă�������s����
		static void handleMessage(const ComponentBasePtr& self, MessageTypeCarrier type, const MessageAttachment& attachment)	{ handleMessage_runner<void, MessageTypeCarrier, const MessageAttachment&>::checkAndRun(self.castPtr<ComponentType>(), type, attachment); }

		// �����̃|�C���^�̎w�����Ԃ��uafterChangeParent�v�������Ă�������s����
		static void afterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent)							{ afterChangeParent_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), beforParent); }

		// �����̃|�C���^�̎w�����Ԃ��uonCollisionEnter�v�������Ă�������s����
		static void onCollisionEnter(const ComponentBasePtr& self, const GameObjectPtr& other)									{ onCollisionEnter_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other); }

		// �����̃|�C���^�̎w�����Ԃ��uonCollisionStay�v�������Ă�������s����
		static void onCollisionStay(const ComponentBasePtr& self, const GameObjectPtr& other)									{ onCollisionStay_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other); }

		// �����̃|�C���^�̎w�����Ԃ��uonCollisionExit�v�������Ă�������s����
		static void onCollisionExit(const ComponentBasePtr& self, const GameObjectPtr& other)									{ onCollisionExit_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other); }
	};

	// �e���v���[�g�N���X���ustart�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
	template<class ComponentType>
	ComponentAwakeFuncVTable ComponentVTableInitializer<ComponentType>::m_awakeFuncVTable =
	{
		 &ComponentVTableInitializer<ComponentType>::awake
	};

	// �e���v���[�g�N���X���ustart�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
	template<class ComponentType>
	ComponentStartFuncVTable ComponentVTableInitializer<ComponentType>::m_startFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::hasStartFunc,
		&ComponentVTableInitializer<ComponentType>::start
	};

	// �e���v���[�g�N���X���udraw�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
	template<class ComponentType>
	ComponentDrawFuncVTable ComponentVTableInitializer<ComponentType>::m_drawFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::hasDrawFunc,
		&ComponentVTableInitializer<ComponentType>::draw
	};

	// �e���v���[�g�N���X���Փˊ֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
	template<class ComponentType>
	ComponentCollisionFuncVTable ComponentVTableInitializer<ComponentType>::m_collisionFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::hasCollideFunc,
		&ComponentVTableInitializer<ComponentType>::isCollide
	};

	// �e���v���[�g�N���X���Q�[���I�u�W�F�N�g�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
	template<class ComponentType>
	ComponentGameObjectFuncVTable ComponentVTableInitializer<ComponentType>::m_componentGameObjectFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::handleMessage,
		&ComponentVTableInitializer<ComponentType>::afterChangeParent,
		&ComponentVTableInitializer<ComponentType>::onCollisionEnter,
		&ComponentVTableInitializer<ComponentType>::onCollisionStay,
		&ComponentVTableInitializer<ComponentType>::onCollisionExit
	};

	// �R���|�[�l���g�̊֐����s�N���X�̏W����
	template<class ComponentType>
	ComponentVTableBundle ComponentVTableInitializer<ComponentType>::m_componentVTableBundle =
	{
		&ComponentVTableInitializer<ComponentType>::m_awakeFuncVTable,
		&ComponentVTableInitializer<ComponentType>::m_startFuncVTable,
		&ComponentVTableInitializer<ComponentType>::m_drawFuncVTable,
		&ComponentVTableInitializer<ComponentType>::m_collisionFuncVTable,
		&ComponentVTableInitializer<ComponentType>::m_componentGameObjectFuncVTable
	};
}
#endif // !COMPONENT_V_TABLE_H_