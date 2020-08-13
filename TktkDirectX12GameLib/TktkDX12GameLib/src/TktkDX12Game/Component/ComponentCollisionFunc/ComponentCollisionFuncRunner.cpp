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

	void ComponentCollisionFuncRunner::runCollideFunc(ComponentCollisionFuncRunner& other)
	{
		if (m_selfPtr.isDead() || other.m_selfPtr.isDead() || !m_selfPtr->isActive() || !other.m_selfPtr->isActive()) return;

		if (m_vtablePtr->runIsCollide(m_selfPtr, other.m_selfPtr))
		{
			auto curHitObject = HitObject(other.m_vtablePtr, other.m_selfPtr);

			m_curHitObjectList.push_front(curHitObject);

			// 前フレームで衝突していたか判定する
			bool preFrameHit = false;
			for (const auto& node : m_preHitObjectList)
			{
				if (node.m_selfPtr.isSame(other.m_selfPtr))
				{
					preFrameHit = true;
					break;
				}
			}
			if (preFrameHit)
			{
				m_selfPtr->getGameObject()->runOnCollisionStayAll(other.m_selfPtr->getGameObject());
				other.m_selfPtr->getGameObject()->runOnCollisionStayAll(m_selfPtr->getGameObject());
			}
			else
			{
				m_selfPtr->getGameObject()->runOnCollisionEnterAll(other.m_selfPtr->getGameObject());
				other.m_selfPtr->getGameObject()->runOnCollisionEnterAll(m_selfPtr->getGameObject());
			}
		}
		else
		{
			// 前フレームで衝突していたか判定する
			bool preFrameHit = false;
			for (const auto& node : m_preHitObjectList)
			{
				if (node.m_selfPtr.isSame(other.m_selfPtr))
				{
					preFrameHit = true;
					break;
				}
			}
			if (preFrameHit)
			{
				m_selfPtr->getGameObject()->runOnCollisionExitAll(other.m_selfPtr->getGameObject());
				other.m_selfPtr->getGameObject()->runOnCollisionExitAll(m_selfPtr->getGameObject());
			}
		}
	}

	bool ComponentCollisionFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}

	ComponentCollisionFuncRunner::HitObject::HitObject(VTable* vtablePtr, ComponentBasePtr selfPtr)
		: m_vtablePtr(vtablePtr)
		, m_selfPtr(selfPtr) {}
}