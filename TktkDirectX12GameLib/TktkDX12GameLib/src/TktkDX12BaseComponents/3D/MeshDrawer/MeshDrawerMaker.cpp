#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MeshDrawerMaker MeshDrawerMaker::m_self;

	MeshDrawerMaker& MeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = MeshDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<MeshDrawer> MeshDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<MeshDrawer>(m_meshHandle, m_skeletonHandle, m_basePosition, m_baseScale, m_baseRotation);
	}

	MeshDrawerMaker& MeshDrawerMaker::meshHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::meshId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::skeletonHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::skeletonId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::basePosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_basePosition = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::baseScale(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_baseScale = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// 値を設定して自身の参照を返す
		m_baseRotation = value;
		return *this;
	}
}