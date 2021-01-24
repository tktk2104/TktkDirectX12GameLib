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

	// コンポーネントクラスの「awake」関数実行クラス
	struct ComponentAwakeFuncVTable
	{
		void(*awake)(const ComponentBasePtr&);
	};

	// コンポーネントクラスの「start」関数実行クラス
	struct ComponentStartFuncVTable
	{
		bool(*hasStartFunc)();

		void(*start)(const ComponentBasePtr&);
	};

	// コンポーネントクラスの「draw」関数実行クラス
	struct ComponentDrawFuncVTable
	{
		bool(*hasDrawFunc)();

		void(*draw)(const ComponentBasePtr&);
	};

	// コンポーネントクラスの衝突関数実行クラス
	struct ComponentCollisionFuncVTable
	{
		bool(*hasCollideFunc)();

		bool(*isCollide)(const ComponentBasePtr&, const ComponentBasePtr&);
	};

	// コンポーネントクラスのゲームオブジェクト関数実行クラス
	struct ComponentGameObjectFuncVTable
	{
		void(*handleMessage)		(const ComponentBasePtr&, MessageTypeCarrier, const MessageAttachment&);
		void(*afterChangeParent)	(const ComponentBasePtr&, const GameObjectPtr&);
		void(*onCollisionEnter)		(const ComponentBasePtr&, const GameObjectPtr&);
		void(*onCollisionStay)		(const ComponentBasePtr&, const GameObjectPtr&);
		void(*onCollisionExit)		(const ComponentBasePtr&, const GameObjectPtr&);
	};

	// コンポーネントの関数実行クラスの集合体
	struct ComponentVTableBundle
	{
		// テンプレートクラスが「awake」関数を持っていたら実行する関数のポインタを保持する構造体
		ComponentAwakeFuncVTable*		awakeFuncVTable;

		// テンプレートクラスが「start」関数を持っていたら実行する関数のポインタを保持する構造体
		ComponentStartFuncVTable*		startFuncVTable;

		// テンプレートクラスが「draw」関数を持っていたら実行する関数のポインタを保持する構造体
		ComponentDrawFuncVTable*		drawFuncVTable;

		// テンプレートクラスが衝突関数を持っていたら実行する関数のポインタを保持する構造体
		ComponentCollisionFuncVTable*	collisionFuncVTable;

		// テンプレートクラスがゲームオブジェクト関数を持っていたら実行する関数のポインタを保持する構造体
		ComponentGameObjectFuncVTable*	componentGameObjectFuncVTable;
	};

	// 「ComponentVTable」を作るために必要な静的関数ポインタ
	template <class ComponentType>
	struct ComponentVTableInitializer
	{
		// テンプレートクラスが「awake」関数を持っていたら実行する関数のポインタを保持する構造体
		static ComponentAwakeFuncVTable		m_awakeFuncVTable;

		// テンプレートクラスが「start」関数を持っていたら実行する関数のポインタを保持する構造体
		static ComponentStartFuncVTable		m_startFuncVTable;
		
		// テンプレートクラスが「draw」関数を持っていたら実行する関数のポインタを保持する構造体
		static ComponentDrawFuncVTable		m_drawFuncVTable;
		
		// テンプレートクラスが衝突関数を持っていたら実行する関数のポインタを保持する構造体
		static ComponentCollisionFuncVTable m_collisionFuncVTable;
		
		// テンプレートクラスがゲームオブジェクト関数を持っていたら実行する関数のポインタを保持する構造体
		static ComponentGameObjectFuncVTable m_componentGameObjectFuncVTable;

		// コンポーネントの関数実行クラスの集合体
		static ComponentVTableBundle		m_componentVTableBundle;

		// 引数のポインタの指す実態が「start」を持っているか？
		static bool hasStartFunc()		{ return has_start_checker<ComponentType*, void>::value; }

		// 引数のポインタの指す実態が「draw」を持っているか？
		static bool hasDrawFunc()		{ return has_draw_checker<ComponentType*, void>::value; }

		// 引数のポインタの指す実態が「isCollide」を持っているか？
		static bool hasCollideFunc()	{ return has_isCollide_checker<ComponentType*, bool, const ComponentBasePtr&>::value; }

		// 引数のポインタの指す実態が「awake」関数を持っていたら実行する
		static void awake(const ComponentBasePtr& runPtr)																		{ awake_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>()); }

		// 引数のポインタの指す実態が「start」関数を持っていたら実行する
		static void start(const ComponentBasePtr& runPtr)																		{ start_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>()); }

		// 引数のポインタの指す実態が「draw」関数を持っていたら実行する
		static void draw(const ComponentBasePtr& runPtr)																		{ draw_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>()); }

		// 引数のポインタの指す実態が「isCollide」を持っていたら実行する
		static bool isCollide(const ComponentBasePtr& self, const ComponentBasePtr& other)										{ return isCollide_runner<bool, const ComponentBasePtr&>::checkAndRun(self.castPtr<ComponentType>(), false, other); }
	
		// 引数のポインタの指す実態が「handleMessage」を持っていたら実行する
		static void handleMessage(const ComponentBasePtr& self, MessageTypeCarrier type, const MessageAttachment& attachment)	{ handleMessage_runner<void, MessageTypeCarrier, const MessageAttachment&>::checkAndRun(self.castPtr<ComponentType>(), type, attachment); }

		// 引数のポインタの指す実態が「afterChangeParent」を持っていたら実行する
		static void afterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent)							{ afterChangeParent_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), beforParent); }

		// 引数のポインタの指す実態が「onCollisionEnter」を持っていたら実行する
		static void onCollisionEnter(const ComponentBasePtr& self, const GameObjectPtr& other)									{ onCollisionEnter_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other); }

		// 引数のポインタの指す実態が「onCollisionStay」を持っていたら実行する
		static void onCollisionStay(const ComponentBasePtr& self, const GameObjectPtr& other)									{ onCollisionStay_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other); }

		// 引数のポインタの指す実態が「onCollisionExit」を持っていたら実行する
		static void onCollisionExit(const ComponentBasePtr& self, const GameObjectPtr& other)									{ onCollisionExit_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other); }
	};

	// テンプレートクラスが「start」関数を持っていたら実行する関数のポインタを保持する構造体
	template<class ComponentType>
	ComponentAwakeFuncVTable ComponentVTableInitializer<ComponentType>::m_awakeFuncVTable =
	{
		 &ComponentVTableInitializer<ComponentType>::awake
	};

	// テンプレートクラスが「start」関数を持っていたら実行する関数のポインタを保持する構造体
	template<class ComponentType>
	ComponentStartFuncVTable ComponentVTableInitializer<ComponentType>::m_startFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::hasStartFunc,
		&ComponentVTableInitializer<ComponentType>::start
	};

	// テンプレートクラスが「draw」関数を持っていたら実行する関数のポインタを保持する構造体
	template<class ComponentType>
	ComponentDrawFuncVTable ComponentVTableInitializer<ComponentType>::m_drawFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::hasDrawFunc,
		&ComponentVTableInitializer<ComponentType>::draw
	};

	// テンプレートクラスが衝突関数を持っていたら実行する関数のポインタを保持する構造体
	template<class ComponentType>
	ComponentCollisionFuncVTable ComponentVTableInitializer<ComponentType>::m_collisionFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::hasCollideFunc,
		&ComponentVTableInitializer<ComponentType>::isCollide
	};

	// テンプレートクラスがゲームオブジェクト関数を持っていたら実行する関数のポインタを保持する構造体
	template<class ComponentType>
	ComponentGameObjectFuncVTable ComponentVTableInitializer<ComponentType>::m_componentGameObjectFuncVTable =
	{
		&ComponentVTableInitializer<ComponentType>::handleMessage,
		&ComponentVTableInitializer<ComponentType>::afterChangeParent,
		&ComponentVTableInitializer<ComponentType>::onCollisionEnter,
		&ComponentVTableInitializer<ComponentType>::onCollisionStay,
		&ComponentVTableInitializer<ComponentType>::onCollisionExit
	};

	// コンポーネントの関数実行クラスの集合体
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