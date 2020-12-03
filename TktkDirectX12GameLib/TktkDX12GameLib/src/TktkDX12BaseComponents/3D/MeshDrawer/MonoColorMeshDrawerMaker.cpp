#include "TktkDX12BaseComponents/3D/MeshDrawer/MonoColorMeshDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MonoColorMeshDrawerMaker MonoColorMeshDrawerMaker::m_self;

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = MonoColorMeshDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<MonoColorMeshDrawer> MonoColorMeshDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<MonoColorMeshDrawer>(m_meshHandle, m_skeletonHandle, m_albedoColor, m_basePosition, m_baseScale, m_baseRotation);
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setBoxMesh()
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::Box);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setBoxMeshWireFrame()
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::BoxWireFrame);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setSphereMesh()
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::Sphere);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setSphereMeshWireFrame()
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::SphereWireFrame);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::meshHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::meshId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::skeletonHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::skeletonId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_albedoColor = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::basePosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_basePosition = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::baseScale(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_baseScale = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// 値を設定して自身の参照を返す
		m_baseRotation = value;
		return *this;
	}
}