#ifndef BASIC_MESH_DRAWER_H_
#define BASIC_MESH_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>
#include "BasicMeshDrawerUseResourceHandles.h"

namespace tktk
{
	/* class member */
	class Transform3D;
	class MeshAnimator;

	// メッシュ描画コンポーネント
	// 【必須コンポーネント：Transform3D】
	class BasicMeshDrawer
		: public ComponentBase
	{
	public:

		BasicMeshDrawer(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, const BasicMeshDrawerUseResourceHandles& useResourceHandles);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// 座標変換用の定数バッファの更新
		void updateTransformCbuffer() const;

		// シャドウマップ用の定数バッファの更新
		void updateShadowMapCbuffer() const;

	private:

		size_t								m_createUploadTransformCbufferHandle			{ 0U };
		size_t								m_createUploadShadowMapCbufferHandle			{ 0U };
		size_t								m_createUploadBoneMatrixCbufferHandle			{ 0U };
		tktkMath::Vector3					m_baseScale				{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion				m_baseRotation			{ tktkMath::Quaternion_v::identity };
		BasicMeshDrawerUseResourceHandles	m_useResourceHandles	{ };
		ComponentPtr<Transform3D>			m_transform				{ };
		ComponentPtr<MeshAnimator>			m_animator				{ };
	};
}
#endif // !BASIC_MESH_DRAWER_H_