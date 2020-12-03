#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		// コンポーネントを作成する
		return m_user->createComponent<MeshAnimator>(m_initMotionHandle, m_initFrame, m_isLoop, m_motionSpeedRate, m_animFramePerSec);
	}

	MeshAnimatorMaker& MeshAnimatorMaker::isLoop(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isLoop = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::motionSpeedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_motionSpeedRate = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_initMotionHandle = DX12GameManager::getMotionHandle(value);
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initFrame(float value)
	{
		// 値を設定して自身の参照を返す
		m_initFrame = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::animFramePerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_animFramePerSec = value;
		return *this;
	}
}