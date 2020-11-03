#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimatorMaker.h"

namespace tktk
{
	MeshAnimatorMaker MeshAnimatorMaker::m_self;

	MeshAnimatorMaker& MeshAnimatorMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = MeshAnimatorMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = MeshAnimatorMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<MeshAnimator> MeshAnimatorMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<MeshAnimator>(m_initMotionHandle, m_isLoop, m_animFramePerSec);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<MeshAnimator>(m_initMotionHandle, m_isLoop, m_animFramePerSec);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::isLoop(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isLoop = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::animFramePerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_animFramePerSec = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = DX12GameManager::getMotionHandle(value);
		return *this;
	}
}