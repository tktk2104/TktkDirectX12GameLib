#include "TktkDX12BaseComponents/3D/MeshAnimator/MotionChangerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MotionChangerMaker MotionChangerMaker::m_self;

	MotionChangerMaker& MotionChangerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = MotionChangerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<MotionChanger> MotionChangerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<MotionChanger>(m_initMotionHandle, m_isLoop, m_motionSpeedRate, m_lerpTimeSec);
	}

	MotionChangerMaker& MotionChangerMaker::isLoop(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isLoop = value;
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::motionSpeedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_motionSpeedRate = value;
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::initMotionHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = value;
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::initMotionId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = DX12GameManager::getMotionHandle(value);
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::lerpTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_lerpTimeSec = value;
		return *this;
	}
}