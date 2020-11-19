#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>

namespace tktk
{
	/* class member */
	class Transform3D;
	class MeshAnimator;

	// メッシュ描画コンポーネント
	// 【必須コンポーネント：Transform3D】
	class MeshDrawer
		: public ComponentBase
	{
	public:

		MeshDrawer(
			size_t						meshHandle,
			size_t						skeletonHandle,
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
		tktkMath::Vector3			m_basePosition;
		tktkMath::Vector3			m_baseScale;
		tktkMath::Quaternion		m_baseRotation;
		ComponentPtr<Transform3D>	m_transform		{ };
		ComponentPtr<MeshAnimator>	m_animator		{ };
	};
}
#endif // !MESH_DRAWER_H_