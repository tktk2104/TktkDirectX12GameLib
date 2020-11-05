#ifndef BASIC_MESH_SHADOW_MAP_WRITER_H_
#define BASIC_MESH_SHADOW_MAP_WRITER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 通常メッシュのシャドウマップ書き込みコンポーネント
	// 【必須コンポーネント：Transform3D】
	class BasicMeshShadowMapWriter
		: public ComponentBase
	{
	public:

		BasicMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, size_t meshHandle, size_t skeletonHandle, size_t cameraHandle);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// 座標変換用の定数バッファの更新
		void updateTransformCbuffer() const;

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_createUploadBoneMatrixCbufferHandle{ 0U };
		tktkMath::Vector3			m_baseScale		{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion		m_baseRotation	{ tktkMath::Quaternion_v::identity };
		size_t						m_meshHandle;
		size_t						m_skeletonHandle;
		size_t						m_cameraHandle;
		ComponentPtr<Transform3D>	m_transform		{ };
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_H_