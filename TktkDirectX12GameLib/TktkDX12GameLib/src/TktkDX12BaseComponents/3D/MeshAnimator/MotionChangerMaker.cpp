#include "TktkDX12BaseComponents/3D/MeshAnimator/MotionChangerMaker.h"

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

	MotionChangerMaker& MotionChangerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = MotionChangerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<MotionChanger> MotionChangerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<MotionChanger>(m_initMotionHandle, m_isLoop, m_lerpTimeSec);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<MotionChanger>(m_initMotionHandle, m_isLoop, m_lerpTimeSec);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	MotionChangerMaker& MotionChangerMaker::isLoop(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isLoop = value;
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