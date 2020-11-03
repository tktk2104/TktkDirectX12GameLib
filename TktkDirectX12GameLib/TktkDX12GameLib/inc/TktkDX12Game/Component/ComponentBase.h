#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include "ComponentPtr.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/GameObjectPtr.h"

namespace tktk
{
	/*
	コンポーネントの基底クラス
	<PolymorphismFunc>

	void awake();				// 生成直後（コンストラクタが呼ばれた後）に呼ばれる
	void start();				// 生成した次のフレームの最初に呼ばれる
	void onEnable();			// 非アクティブからアクティブ状態に移行した時に呼ばれる
	void onDisable();			// アクティブから非アクティブ状態に移行した時に呼ばれる
	void onDestroy();			// 削除フラグが立った瞬間（デストラクタが呼ばれる前）に呼ばれる
	void update();				// 毎フレーム呼ばれる

	void afterChangeParent	(const tktk::GameObjectPtr& beforParent);	// 子要素が変更された後に呼ばれる
	void onCollisionEnter	(const tktk::GameObjectPtr& other);			// 衝突開始時に呼ばれる
	void onCollisionStay	(const tktk::GameObjectPtr& other);			// 衝突中に呼ばれる
	void onCollisionExit	(const tktk::GameObjectPtr& other);			// 衝突終了時に呼ばれる

	void handleMessage		(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);	// メッセージを受け取った時に呼ばれる
	*/
	class ComponentBase
	{
	public:

		ComponentBase(float drawPriority = 0.0f, const int collisionGroup = 0);
		virtual ~ComponentBase();

	public:

		// 描画優先度を取得する（値が小さいほど先に呼ばれる）
		float getDrawPriority() const;

		// 衝突判定グループを取得する
		int getCollisionGroup() const;

		// アクティブフラグを設定する
		void setActive(bool activeFlag);

		// 自身を殺す
		void destroy();

		// アクティブフラグを取得する
		bool isActive() const;

		// 死亡フラグを取得する
		bool isDead() const;

		// アクティブフラグの変更判定
		bool activeChangeCheck();

	public:

		// 自身の所持オブジェクトを取得する
		const GameObjectPtr& getGameObject() const;

		// 自身の所持オブジェクトが持っているテンプレート引数の型のコンポーネントを取得する
		// ※取得できなかった場合はnullptrを返す
		// ※複数該当コンポーネントがあった場合、最初に見つけた１つを取得する
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		// 自身の所持オブジェクトが持っているテンプレート引数の型のコンポーネントを全て取得する
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

	public:

		// 自身を所持するオブジェクトを設定する
		void setUser(const GameObjectPtr& user);

	private:

		const float		m_drawPriority;
		const int		m_collisionGroup;
		bool			m_isActive			{ true };
		bool			m_nextFrameActive	{ true };
		bool			m_isDead			{ false };
		GameObjectPtr	m_user				{ };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 自身の所持オブジェクトが持っているテンプレート引数の型のコンポーネントを取得する
	// ※取得できなかった場合はnullptrを返す
	// ※複数該当コンポーネントがあった場合、最初に見つけた１つを取得する
	template<class ComponentType>
	inline ComponentPtr<ComponentType> ComponentBase::getComponent() const
	{
		if (m_user.expired()) return ComponentPtr<ComponentType>();
		return m_user->getComponent<ComponentType>();
	}

	// 自身の所持オブジェクトが持っているテンプレート引数の型のコンポーネントを全て取得する
	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> ComponentBase::getComponents() const
	{
		if (m_user.expired()) return std::forward_list<ComponentPtr<ComponentType>>();
		return m_user->getComponents<ComponentType>();
	}
}
#endif // !COMPONENT_BASE_H_