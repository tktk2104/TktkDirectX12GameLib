#include "TktkDX12Game/Component/ComponentCollisionFunc/ComponentCollisionFuncRunner.h"

#include <algorithm>
#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentCollisionFuncRunner::updateHitObjectList()
	{
		// 前フレームの衝突判定結果を更新して、現在の衝突判定結果を初期化する
		m_preHitObjectList = std::move(m_curHitObjectList);
		m_curHitObjectList.clear();
	}

	void ComponentCollisionFuncRunner::runCollideFunc(const ComponentCollisionFuncRunner& other)
	{
		// 自身か衝突相手どちらかが死んでいるか、非アクティブ状態になっていたら何もしない
		if (m_selfPtr.isDead() || other.m_selfPtr.isDead() || !m_selfPtr->isActive() || !other.m_selfPtr->isActive()) return;

		// 衝突判定関数を呼ぶ
		if (m_vtablePtr->runIsCollide(m_selfPtr, other.m_selfPtr))
		{
			// 衝突相手の情報を現フレームでの衝突相手リストに追加する
			m_curHitObjectList.push_front({ other.m_vtablePtr, other.m_selfPtr });

			// 前フレームで衝突していたか？
			bool isPreFrameHit = false;

			// 前フレームでの衝突相手リストを巡回する
			for (const auto& preHitObject : m_preHitObjectList)
			{
				// 衝突相手のコンポーネントポインタと巡回中の衝突相手コンポーネントポインタが同じだったら
				if (preHitObject.selfPtr.isSame(other.m_selfPtr))
				{
					// 前フレーム衝突フラグを立てて、ループを終了する
					isPreFrameHit = true;
					break;
				}
			}

			// 前フレームも衝突していたら
			if (isPreFrameHit)
			{
				// 自身のコンポーネントを所持するゲームオブジェクトの衝突中処理を呼ぶ
				m_selfPtr->getGameObject()->runOnCollisionStayAll(other.m_selfPtr->getGameObject());

				// 衝突相手のコンポーネントを所持するゲームオブジェクトの衝突中処理を呼ぶ
				other.m_selfPtr->getGameObject()->runOnCollisionStayAll(m_selfPtr->getGameObject());
			}
			// 前フレームは衝突していなかったら
			else
			{
				// 自身のコンポーネントを所持するゲームオブジェクトの衝突開始処理を呼ぶ
				m_selfPtr->getGameObject()->runOnCollisionEnterAll(other.m_selfPtr->getGameObject());

				// 衝突相手のコンポーネントを所持するゲームオブジェクトの衝突開始処理を呼ぶ
				other.m_selfPtr->getGameObject()->runOnCollisionEnterAll(m_selfPtr->getGameObject());
			}
		}
		// 衝突していなかったら
		else
		{
			// 前フレームで衝突していたか？
			bool preFrameHit = false;

			// 前フレームでの衝突相手リストを巡回する
			for (const auto& node : m_preHitObjectList)
			{
				// 衝突相手のコンポーネントポインタと巡回中の衝突相手コンポーネントポインタが同じだったら
				if (node.selfPtr.isSame(other.m_selfPtr))
				{
					// 前フレーム衝突フラグを立てて、ループを終了する
					preFrameHit = true;
					break;
				}
			}

			// 前フレームで衝突していたら
			if (preFrameHit)
			{
				// 自身のコンポーネントを所持するゲームオブジェクトの衝突終了処理を呼ぶ
				m_selfPtr->getGameObject()->runOnCollisionExitAll(other.m_selfPtr->getGameObject());

				// 衝突相手のコンポーネントを所持するゲームオブジェクトの衝突終了処理を呼ぶ
				other.m_selfPtr->getGameObject()->runOnCollisionExitAll(m_selfPtr->getGameObject());
			}
		}
	}

	bool ComponentCollisionFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}

	ComponentCollisionFuncRunner::HitObject::HitObject(VTable* vtablePtr, ComponentBasePtr selfPtr)
		: vtablePtr(vtablePtr)
		, selfPtr(selfPtr) {}
}