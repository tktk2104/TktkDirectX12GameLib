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

	ComponentPtr<MeshAnimator> MeshAnimatorMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<MeshAnimator>(m_initMotionHandle, m_isLoop);
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

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = DX12GameManager::getMotionHandle(value);
		return *this;
	}
}