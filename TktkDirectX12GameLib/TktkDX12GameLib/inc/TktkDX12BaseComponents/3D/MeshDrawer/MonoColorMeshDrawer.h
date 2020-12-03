#ifndef MONO_COLOR_MESH_DRAWER_H_
#define MONO_COLOR_MESH_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>

namespace tktk
{
	/* class member */
	class Transform3D;
	class MeshAnimator;

	// 単色描画コンポーネント
	// 【必須コンポーネント：Transform3D】
	class MonoColorMeshDrawer
		: public ComponentBase
	{
	public:

		MonoColorMeshDrawer(
			size_t						meshHandle,
			size_t						skeletonHandle,
			const tktkMath::Color&		albedoColor,
			const tktkMath::Vector3&	basePosition,
			const tktkMath::Vector3&	baseScale,
			const tktkMath::Quaternion& baseRotation
		);

	public:

		void start();
		void afterCollide();

	private:

		size_t m_meshHandle;
		size_t m_skeletonHandle;
		tktkMath::Color				m_albedoColor;
		tktkMath::Vector3			m_basePosition;
		tktkMath::Vector3			m_baseScale;
		tktkMath::Quaternion		m_baseRotation;
		ComponentPtr<Transform3D>	m_transform{ };
		ComponentPtr<MeshAnimator>	m_animator{ };
	};
}
#endif // !MONO_COLOR_MESH_DRAWER_H_